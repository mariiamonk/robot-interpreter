%{
#include "scanner.h"
#include "parser.hpp"
#include <sstream>
#include "ast/genericType.h"
#include "robot/robot.h"
using namespace std;
int line_num = 1;
%}

%option noyywrap c++
%option yyclass="Scanner"
%option caseless

%%

<<EOF>>                     {   yyterminate();  }

"PLEASE"        { return yy::parser::make_PLEASE(); }
"THANKS"        { return yy::parser::make_THANKS(); }

"VAR"           { return yy::parser::make_VAR(); }
"SIZE"          { return yy::parser::make_SIZE(); }

"LOGITIZE"      { return yy::parser::make_LOGITIZE(); }
"DIGITIZE"      { return yy::parser::make_DIGITIZE(); }

"REDUCE"        { return yy::parser::make_REDUCE(); }
"EXTEND"        { return yy::parser::make_EXTEND(); }

"FOR"           { return yy::parser::make_FOR(); }
"BOUNDARY"      { return yy::parser::make_BOUNDARY(); }
"STEP"          { return yy::parser::make_STEP(); }

"SWITCH"        { return yy::parser::make_SWITCH(); }
"ELSE"          { return yy::parser::make_ELSE(); }

"MOVE"          { return yy::parser::make_MOVE(); }
"ROTATE"        { return yy::parser::make_ROTATE(); }
"LEFT"          { return yy::parser::make_LEFT(); }
"RIGHT"         { return yy::parser::make_RIGHT(); }

"GET"           { return yy::parser::make_GET(); }
"ENVIRONMENT"   { return yy::parser::make_ENVIRONMENT(); }
"TASK"          { return yy::parser::make_TASK(); }
"DO"            { return yy::parser::make_DO(); }
"RESULT"        { return yy::parser::make_RESULT(); }
"PRINT"         { return yy::parser::make_PRINT(); }

"AND"           { return yy::parser::make_AND(); }
"OR"            { return yy::parser::make_OR(); }
"NOT"           { return yy::parser::make_NOT(); }

"MXTRUE"        { return yy::parser::make_MXTRUE(); }
"MXFALSE"       { return yy::parser::make_MXFALSE(); }
"MXEQ"          { return yy::parser::make_MXEQ(); }
"MXLT"          { return yy::parser::make_MXLT(); }
"MXGT"          { return yy::parser::make_MXGT(); }
"MXLTE"         { return yy::parser::make_MXLTE(); }
"MXGTE"         { return yy::parser::make_MXGTE(); }

"ELEQ"          { return yy::parser::make_ELEQ(); }
"ELLT"          { return yy::parser::make_ELLT(); }
"ELGT"          { return yy::parser::make_ELGT(); }
"ELLTE"         { return yy::parser::make_ELLTE(); }
"ELGTE"         { return yy::parser::make_ELGTE(); }


[\t\r\v]+                   {}
" "                         {}
\n                          {line_num++;}

"="                         { return yy::parser::make_ASSIGN(); }
"=="                         { return yy::parser::make_DASSIGN(); }
"<="                         { return yy::parser::make_MASSIGN(); }
">="                         { return yy::parser::make_VASSIGN(); }
"!="                         { return yy::parser::make_NASSIGN(); }

"["                         { return yy::parser::make_LBRACKET(); }
"]"                         { return yy::parser::make_RBRACKET(); }
"("                         { return yy::parser::make_LPAREN(); }
")"                         { return yy::parser::make_RPAREN(); }
"{"                         { return yytext[0]; }
"}"                         { return yytext[0]; }
","                         { return yy::parser::make_COMMA(); }
";"                         { return yy::parser::make_SEMICOLON(); }

"+"                         { return yy::parser::make_PLUS(); }
"-"                         { return yy::parser::make_MINUS(); }
"*"                         { return yy::parser::make_MULT(); }
"/"                         { return yy::parser::make_DIV(); }

"TRUE"                      { return yy::parser::make_BOOL(BoolValue::TRUE); }
"FALSE"                     { return yy::parser::make_BOOL(BoolValue::FALSE); }

0[0-7]+                     { return yy::parser::make_NUMBER(strtol(yytext, NULL, 8)); }
0x[0-9a-fA-F]+              { return yy::parser::make_NUMBER(strtol(yytext, NULL, 16)); }
[0-9]+                      { return yy::parser::make_NUMBER(atoi(yytext)); }

[a-zA-Z][a-zA-Z0-9]*        { return yy::parser::make_IDENTIFIER(yytext); }

.                           { cerr << "Illegal character: " << yytext << endl; }

%%