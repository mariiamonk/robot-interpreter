#pragma once
#include "genericType.h"
#include "robot/robot.h"
#include "graphics/graphics.h"
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <functional>

class ASTNode {
public:
    virtual ~ASTNode() = default;
    virtual GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) = 0;
    virtual bool isReturn() const { return false; }
};

class BlockNode : public ASTNode {
    
public:
    std::vector<ASTNode*> statements;
    BlockNode(std::vector<ASTNode*> stmts) : statements(std::move(stmts)) {}
    ~BlockNode() {
        for (auto stmt : statements) delete stmt;
    }
    void addStatement(ASTNode* stmt) { statements.push_back(stmt); }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};

class LiteralNode : public ASTNode {
    GenericValue value;
public:
    LiteralNode(const GenericValue& val) : value(val) {}
    GenericValue eval(Robot&, VariableTable&, Graphics&) override { return value; }
};

class VariableNode : public ASTNode {
    std::string name;
public:
    VariableNode(const std::string& n) : name(n) {}
    const std::string& getName() const { return name; }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};

class ArrayAccessNode : public ASTNode {
    std::string name;
    std::vector<ASTNode*> indices;
public:
    ArrayAccessNode(const std::string& n, std::vector<ASTNode*> idx)
        : name(n), indices(std::move(idx)) {}
    ~ArrayAccessNode() {
        for (auto idx : indices) delete idx;
    }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;

    const std::string& getName() const {
        return name;
    }
    const std::vector<ASTNode*>& getIndices() const {
        return indices;
    }

    GenericValue& evalRef(Robot& robot, VariableTable& vars, Graphics& graphics)
    {
        GenericValue& array = vars.getVariable(name);
        std::vector<int> indicesComputed;

        for (auto indexNode : indices) {
            GenericValue indexVal = indexNode->eval(robot, vars, graphics);
            if (indexVal.type != DataType::INT)
                throw std::runtime_error("Array index must be int");
            indicesComputed.push_back(boost::get<int>(indexVal.value) - 1); // 1-based to 0-based
        }

        GenericValue* current = &array;
        for (size_t i = 0; i < indicesComputed.size(); ++i) {
            if (current->type != DataType::ARRAY)
                throw std::runtime_error("Not an array at dimension " + std::to_string(i + 1));
            current = &current->at(indicesComputed[i]);
        }

        return *current;
    }
};

class AssignmentNode : public ASTNode {
    std::string name;
    std::vector<ASTNode*> indices;
    ASTNode* value;

public:
    AssignmentNode(const std::string& n, ASTNode* val)
        : name(n), value(val) {}

    AssignmentNode(const std::string& n, std::vector<ASTNode*> idx, ASTNode* val)
        : name(n), indices(std::move(idx)), value(val) {}

    bool isArrayAccess() const { return !indices.empty(); }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override {
        GenericValue val = value->eval(robot, vars, graphics);

        if (!isArrayAccess()) {
            if (!vars.exists(name)) {
                vars.addVariable(name, val);
            } else {
                vars.setVariable(name, val);
            }
        } else {
             GenericValue& arrayVal = vars.getVariable(name);

            if (arrayVal.type != DataType::ARRAY) {
                throw std::runtime_error("Переменная '" + name + "' не является массивом");
            }

            std::vector<int> idxs;
            for (ASTNode* idxNode : indices) {
                GenericValue idxVal = idxNode->eval(robot, vars, graphics);
                if (idxVal.type != DataType::INT) {
                    throw std::runtime_error("Индекс массива должен быть целым числом");
                }
                int idx = boost::get<int>(idxVal.value);
                if (idx < 1) {
                    throw std::runtime_error("Индекс массива не может быть меньше 1");
                }
                idxs.push_back(idx - 1); 
            }

            GenericValue* current = &arrayVal;
            for (size_t i = 0; i < idxs.size() - 1; ++i) {
                current = &current->at(idxs[i]);
                if (current->type != DataType::ARRAY) {
                    throw std::runtime_error("Попытка обращения к не-массиву по индексу на шаге " + std::to_string(i));
                }
            }
            current->at(idxs.back()) = val;
        }
        return val;
    }


};

class VarDeclNode : public ASTNode {
    std::string name;
    ASTNode* dimExpr;
    ASTNode* initValue;
public:
    VarDeclNode(const std::string& n, ASTNode* dims, ASTNode* init)
        : name(n), dimExpr(dims), initValue(init) {}
    ~VarDeclNode() {
        delete dimExpr;
        delete initValue;
    }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};

class SizeNode : public ASTNode {
    std::string name;
public:
    SizeNode(const std::string& n) : name(n) {}
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};

class DigitizeNode : public ASTNode {
    ASTNode* operand;
public:
    DigitizeNode(ASTNode* op) : operand(op) {}
    ~DigitizeNode() { delete operand; }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};

class LogitizeNode : public ASTNode {
    ASTNode* operand;
public:
    LogitizeNode(ASTNode* op) : operand(op) {}
    ~LogitizeNode() { delete operand; }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};

class BinaryOpNode : public ASTNode {
    std::string op;
    ASTNode* left;
    ASTNode* right;
public:
    BinaryOpNode(const std::string& o, ASTNode* l, ASTNode* r)
        : op(o), left(l), right(r) {}
    ~BinaryOpNode() {
        delete left;
        delete right;
    }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};

class UnaryOpNode : public ASTNode {
    std::string op;
    ASTNode* operand;
public:
    UnaryOpNode(const std::string& o, ASTNode* op)
        : op(o), operand(op) {}
    ~UnaryOpNode() { delete operand; }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};

class ReduceNode : public ASTNode {
    ASTNode* operand;
    std::vector<ASTNode*> newDims;
public:
    ReduceNode(ASTNode* op, std::vector<ASTNode*> dims)
        : operand(op), newDims(std::move(dims)) {}
    ~ReduceNode() {
        delete operand;
        for (auto dim : newDims) delete dim;
    }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};

class ExtendNode : public ASTNode {
    ASTNode* operand;
    std::vector<ASTNode*> newDims;
public:
    ExtendNode(ASTNode* op, std::vector<ASTNode*> dims)
        : operand(op), newDims(std::move(dims)) {}
    ~ExtendNode() {
        delete operand;
        for (auto dim : newDims) delete dim;
    }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};

class SwitchNode : public ASTNode {
    ASTNode* condition;
    std::vector<ASTNode*> trueBlock;
    std::vector<ASTNode*> falseBlock;
public:
    SwitchNode(ASTNode* cond, std::vector<ASTNode*> tBlock, std::vector<ASTNode*> fBlock = {})
        : condition(cond), trueBlock(std::move(tBlock)), falseBlock(std::move(fBlock)) {}
    ~SwitchNode() {
        delete condition;
        for (auto stmt : trueBlock) delete stmt;
        for (auto stmt : falseBlock) delete stmt;
    }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};

class ForNode : public ASTNode {
    std::string counterVar;
    ASTNode* boundary;
    ASTNode* step;
    std::vector<ASTNode*> body;
public:
    ForNode(const std::string& cv, ASTNode* b, ASTNode* s, std::vector<ASTNode*> bod)
        : counterVar(cv), boundary(b), step(s), body(std::move(bod)) {}
    ~ForNode() {
        delete boundary;
        delete step;
        for (auto stmt : body) delete stmt;
    }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};

class RobotCommandNode : public ASTNode {
public:
    enum Command { MOVE, ROTATE_LEFT, ROTATE_RIGHT, GET_ENVIRONMENT };
private:
    Command cmd;
public:
    RobotCommandNode(Command c) : cmd(c) {}
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};

class ReturnNode : public ASTNode {
    ASTNode* expr;
public:
    ReturnNode(ASTNode* e) : expr(e) {}
    ~ReturnNode() { delete expr; }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
    bool isReturn() const override { return true; }
};

class ReturnValue : public std::exception {
public:
    GenericValue value;
    ReturnValue(const GenericValue& v) : value(v) {}
};

class FunctionNode;

class FunctionTable {
    std::unordered_map<std::string, FunctionNode*> functions;

public:
    static FunctionTable& instance() {
        static FunctionTable inst;
        return inst;
    }

    void addFunction(const std::string& name, FunctionNode* func) {
        functions[name] = func;
    }

    FunctionNode* getFunction(const std::string& name) const {
        auto it = functions.find(name);
        if (it != functions.end()) return it->second;
        return nullptr;
    }
};


class FunctionNode : public ASTNode {
    std::string name;
    std::vector<std::string> paramNames;
    ASTNode* body;
public:
    FunctionNode(const std::string& name, const std::vector<std::string>& params, ASTNode* body)
        : name(name), paramNames(params), body(body) {}

    ~FunctionNode() { delete body; }

    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
    const std::string& getName() const { return name; }
    const std::vector<std::string>& getParamNames() const { return paramNames; }
    ASTNode* getBody() const { return body; }
};

class FunctionCallNode : public ASTNode {
    std::string name;
    std::vector<ASTNode*> args;
public:
    FunctionCallNode(const std::string& name, const std::vector<ASTNode*>& args)
        : name(name), args(args) {}

    ~FunctionCallNode() {
        for (auto arg : args) delete arg;
    }

    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};

class PrintNode : public ASTNode {
    ASTNode* expr;
public:
    PrintNode(ASTNode* e) : expr(e) {}
    ~PrintNode() { delete expr; }
    GenericValue eval(Robot& robot, VariableTable& vars, Graphics& graphics) override;
};