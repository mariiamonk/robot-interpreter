%defines
%define parse.error detailed
%define api.token.constructor
%define api.value.type variant

%language "c++"

%code requires {
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "ast/ast.h"
#include "ast/bases.h"
#include "robot/robot.h"
#include "graphics/graphics.h"

class Scanner;
}

%code {
    #include "scanner.h"

    extern int line_num;

    extern "C" int yyerror(const char *s) { 
        std::cout << s << std::endl;
        return 0;
    };

    void yy::parser::error(const std::string& msg) {
        std::cout << msg  << " at string " << line_num << std::endl;
    };

    static yy::parser::symbol_type yylex(Scanner &scanner) {
        return scanner.ScanToken();
    }

    FunctionTable global_functions;
    VariableTable vars;
    Robot robot;
    Graphics* graphics_ptr = nullptr;
    bool polite_mode = false;
    int polite = 0;
}

%lex-param { Scanner &scanner }
%parse-param { Scanner &scanner }

%token VAR SIZE LOGITIZE DIGITIZE REDUCE EXTEND
%token FOR BOUNDARY STEP SWITCH ELSE
%token MOVE ROTATE LEFT RIGHT GET ENVIRONMENT
%token AND OR NOT
%token PRINT PLEASE THANKS
%token TASK DO RESULT
%token MXTRUE MXFALSE DASSIGN MASSIGN VASSIGN NASSIGN
%token MXEQ MXLT MXGT MXLTE MXGTE
%token ELEQ ELLT ELGT ELLTE ELGTE

%token ASSIGN SEMICOLON
%token LBRACKET RBRACKET LPAREN RPAREN COMMA
%token PLUS MINUS MULT DIV

%token <int> NUMBER
%token <BoolValue> BOOL
%token <std::string> IDENTIFIER

%type <ASTNode*> program function_decl block statement expr
%type <ASTNode*> var_decl array_access size_expr digitize_expr logitize_expr
%type <ASTNode*> reduce_expr extend_expr for_loop switch_stmt robot_cmd
%type <ASTNode*> function_call return_stmt print_stmt assignment
%type <std::vector<ASTNode*>> expr_list dim_list index_list statement_list function_list
%type <std::vector<std::string>> param_list

%left OR
%left AND
%left PLUS MINUS
%left MULT DIV
%right NOT
%left LOGITIZE DIGITIZE
%nonassoc DASSIGN MASSIGN VASSIGN NASSIGN FINDEXIT

%%

program:
    function_list {
        robot.loadMapFromFile("robot/map.txt");
        
        const Environment& env = robot.getEnvironmentC();
        sf::Vector2u mapSize(
            env.walls.empty() ? 0 : env.walls[0].size(),
            env.walls.size()
        );
        
        graphics_ptr = new Graphics(mapSize);
        
        FunctionNode* main_func = FunctionTable::instance().getFunction("FINDEXIT");
        if (main_func) {
            GenericValue result = main_func->eval(robot, vars, *graphics_ptr);
        } else {
            std::cerr << "FINDEXIT function not found!" << std::endl;
        }
        
        delete graphics_ptr;
        graphics_ptr = nullptr;
    }
    ;

function_list:
    /* empty */ { }
    | function_list function_decl { }
    ;

function_decl:
    TASK IDENTIFIER LPAREN param_list RPAREN block {
        FunctionNode* fn = new FunctionNode($2, $4, $6);
        FunctionTable::instance().addFunction($2, fn);
    }
    ;

param_list:
    /* empty */ { $$ = {}; }
    | IDENTIFIER { $$ = {$1}; }
    | param_list COMMA IDENTIFIER { $$ = $1; $$.push_back($3); }
    ;

block:
    '{' statement_list '}' {
        $$ = new BlockNode($2);
    }
    ;

statement_list:
    /* empty */ { $$ = {}; }
    | statement_list statement { 
        $1.push_back($2);
        $$ = $1;
    }
    ;

statement:
    var_decl SEMICOLON { $$ = $1; }
    | print_stmt SEMICOLON { $$ = $1; }
    | for_loop { $$ = $1; }
    | robot_cmd SEMICOLON{$$ = $1;}
    | switch_stmt { $$ = $1; }
    | function_call SEMICOLON { $$ = $1; }
    | return_stmt SEMICOLON { $$ = $1; }
    | PLEASE block THANKS { $$ = $2; polite++;}
    | assignment SEMICOLON { $$ = $1; }   
    ;

assignment:
    IDENTIFIER ASSIGN expr           { $$ = new AssignmentNode($1, $3); }
  | array_access ASSIGN expr        {
                                      auto arr = dynamic_cast<ArrayAccessNode*>($1);
                                      $$ = new AssignmentNode(arr->getName(), arr->getIndices(), $3);
                                  }
;

var_decl:
    VAR IDENTIFIER ASSIGN expr { $$ = new VarDeclNode($2, nullptr, $4); }
    | VAR IDENTIFIER LBRACKET dim_list RBRACKET ASSIGN expr { 
        std::vector<GenericValue> dimValues;
        for (auto d : $4) {
            dimValues.push_back(d->eval(robot, vars, *graphics_ptr));
        }
        $$ = new VarDeclNode($2, new LiteralNode(GenericValue(dimValues)), $7); 
    }
    ;

dim_list:
    expr { $$ = {$1}; }
    | dim_list COMMA expr { $1.push_back($3); $$ = $1; }
    ;

array_access:
    IDENTIFIER LBRACKET index_list RBRACKET { $$ = new ArrayAccessNode($1, $3); }
    ;

index_list:
    expr { $$ = {$1}; }
    | index_list COMMA expr { $1.push_back($3); $$ = $1; }
    ;

size_expr:
    SIZE LPAREN IDENTIFIER RPAREN { $$ = new SizeNode($3); }
    ;

digitize_expr:
    DIGITIZE expr { $$ = new DigitizeNode($2); }
    ;

logitize_expr:
    LOGITIZE expr { $$ = new LogitizeNode($2); }
    ;

reduce_expr:
    REDUCE IDENTIFIER LBRACKET dim_list RBRACKET { $$ = new ReduceNode(new VariableNode($2), $4); }
    ;

extend_expr:
    EXTEND IDENTIFIER LBRACKET dim_list RBRACKET { $$ = new ExtendNode(new VariableNode($2), $4); }
    ;

for_loop:
    FOR IDENTIFIER BOUNDARY expr STEP expr block {
        $$ = new ForNode($2, $4, $6, static_cast<BlockNode*>($7)->statements);
    }
    ;

switch_stmt:
    SWITCH expr block { $$ = new SwitchNode($2, static_cast<BlockNode*>($3)->statements, {}); }
    | SWITCH expr block ELSE block { $$ = new SwitchNode($2, static_cast<BlockNode*>($3)->statements, static_cast<BlockNode*>($5)->statements); }
    ;

robot_cmd:
    MOVE { $$ = new RobotCommandNode(RobotCommandNode::MOVE); }
    | ROTATE LEFT { $$ = new RobotCommandNode(RobotCommandNode::ROTATE_LEFT); }
    | ROTATE RIGHT { $$ = new RobotCommandNode(RobotCommandNode::ROTATE_RIGHT); }
    | GET ENVIRONMENT { $$ = new RobotCommandNode(RobotCommandNode::GET_ENVIRONMENT); }
    ;

function_call:
    DO IDENTIFIER LPAREN expr_list RPAREN { $$ = new FunctionCallNode($2, $4); }
    ;

return_stmt:
    RESULT expr { $$ = new ReturnNode($2); }
    ;

print_stmt:
    PRINT expr { $$ = new PrintNode($2); }
    ;

expr_list:
    /* empty */ { $$ = {}; }
    | expr { $$ = {$1}; }
    | expr_list COMMA expr { $1.push_back($3); $$ = $1; }
    ;

expr:
    NUMBER { $$ = new LiteralNode(GenericValue($1)); }
    | BOOL { $$ = new LiteralNode(GenericValue($1)); }
    | IDENTIFIER { $$ = new VariableNode($1); }
    | array_access { $$ = $1; }
    | size_expr { $$ = $1; }
    | digitize_expr { $$ = $1; }
    | logitize_expr { $$ = $1; }
    | reduce_expr { $$ = $1; }
    | extend_expr { $$ = $1; }
    | expr PLUS expr { $$ = new BinaryOpNode("+", $1, $3); }
    | expr MINUS expr { $$ = new BinaryOpNode("-", $1, $3); }
    | expr MULT expr { $$ = new BinaryOpNode("*", $1, $3); }
    | expr DIV expr { $$ = new BinaryOpNode("/", $1, $3); }
    | expr AND expr { $$ = new BinaryOpNode("AND", $1, $3); }
    | expr OR expr { $$ = new BinaryOpNode("OR", $1, $3); }
    | expr DASSIGN expr { $$ = new BinaryOpNode("==", $1, $3); }
    | expr MASSIGN expr { $$ = new BinaryOpNode("<=", $1, $3); }
    | expr VASSIGN expr { $$ = new BinaryOpNode(">=", $1, $3); }
    | expr NASSIGN expr { $$ = new BinaryOpNode("!=", $1, $3); }
    | NOT expr { $$ = new UnaryOpNode("NOT", $2); }
    | LPAREN expr RPAREN { $$ = $2; }
    | function_call { $$ = $1; }
    | robot_cmd{ $$ = $1; }
    ;

%%