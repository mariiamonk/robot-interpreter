#include "ast.h"
#include <stdexcept>
#include <algorithm>
#include <iostream>

GenericValue BlockNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    for (ASTNode* stmt : statements) {
        GenericValue result = stmt->eval(robot, vars, graphics);
        if (stmt->isReturn()) {
            return result; 
        }
    }
    return GenericValue(); 
}


GenericValue VariableNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    return vars.getVariable(name);
}

GenericValue ArrayAccessNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    GenericValue& array = vars.getVariable(name);

    if (array.type != DataType::ARRAY) {
        robot.selfDestruct();

        sf::Clock clock;
        while (clock.getElapsedTime().asSeconds() < 2.0f) {
            graphics.handleEvents();
            graphics.render(robot);
        }

        throw std::runtime_error(name + " is not an array");
    }

    std::vector<int> indicesComputed;
    for (auto indexNode : indices) {
        GenericValue indexVal = indexNode->eval(robot, vars, graphics);
        if (indexVal.type != DataType::INT) {
            robot.selfDestruct();

            sf::Clock clock;
            while (clock.getElapsedTime().asSeconds() < 2.0f) {
                graphics.handleEvents();
                graphics.render(robot);
            }

            throw std::runtime_error("Array index must be integer");
        }
        indicesComputed.push_back(boost::get<int>(indexVal.value) - 1); // 0-based
    }

    GenericValue* current = &array;
    for (size_t i = 0; i < indicesComputed.size(); ++i) {
        if (current->type != DataType::ARRAY) {
            robot.selfDestruct();

            sf::Clock clock;
            while (clock.getElapsedTime().asSeconds() < 2.0f) {
                graphics.handleEvents();
                graphics.render(robot);
            }
            throw std::runtime_error("Invalid array access at dimension " + std::to_string(i+1));
        }

        auto& currentArr = boost::get<std::vector<GenericValue>>(current->value);
        int idx = indicesComputed[i];

        if (idx < 0 || idx >= static_cast<int>(currentArr.size())) {
            robot.selfDestruct();

            sf::Clock clock;
            while (clock.getElapsedTime().asSeconds() < 2.0f) {
                graphics.handleEvents();
                graphics.render(robot);
            }

            throw std::runtime_error("Index out of bounds at dimension " + std::to_string(i+1));
        }

        current = &currentArr[idx];
    }

    return *current;
}

GenericValue VarDeclNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    GenericValue initVal = initValue->eval(robot, vars, graphics);

    if (dimExpr) {
        GenericValue dimsValue = dimExpr->eval(robot, vars, graphics);

        if (dimsValue.type != DataType::ARRAY) {
            robot.selfDestruct();

            sf::Clock clock;
            while (clock.getElapsedTime().asSeconds() < 2.0f) {
                graphics.handleEvents();
                graphics.render(robot);
            }

            throw std::runtime_error("Dimensions must be an array");
        }

        const auto& dimArray = boost::get<std::vector<GenericValue>>(dimsValue.value);
        std::vector<int> dimensions;

        for (const auto& dim : dimArray) {
            if (dim.type != DataType::INT) {
                robot.selfDestruct();

                sf::Clock clock;
                while (clock.getElapsedTime().asSeconds() < 2.0f) {
                    graphics.handleEvents();
                    graphics.render(robot);
                }

                throw std::runtime_error("Dimension must be an integer");
            }
            int d = boost::get<int>(dim.value);
            if (d <= 0) {
                robot.selfDestruct();

                sf::Clock clock;
                while (clock.getElapsedTime().asSeconds() < 2.0f) {
                    graphics.handleEvents();
                    graphics.render(robot);
                }

                throw std::runtime_error("Dimension size must be positive");
            }
            dimensions.push_back(d);
        }

        GenericValue array = GenericValue::createArray(dimensions, initVal);
        vars.addVariable(name, array);
        return array;
    }

    vars.addVariable(name, initVal);
    return initVal;
}


GenericValue SizeNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    GenericValue var = vars.getVariable(name);
    return var.size();
}

GenericValue DigitizeNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    return operand->eval(robot, vars, graphics).digitize();
}

GenericValue LogitizeNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    return operand->eval(robot, vars, graphics).logitize();
}

GenericValue BinaryOpNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    GenericValue leftVal = left->eval(robot, vars, graphics);
    GenericValue rightVal = right->eval(robot, vars, graphics);
    
    if (op == "+") return leftVal + rightVal;
    if (op == "-") return leftVal - rightVal;
    if (op == "*") return leftVal * rightVal;
    if (op == "/") return leftVal / rightVal;
    if (op == "==") return leftVal == rightVal;
    if (op == "<=") return leftVal <= rightVal;
    if (op == ">=") return leftVal >= rightVal;
    if (op == "!=") return leftVal != rightVal;
    if (op == "AND") return leftVal && rightVal;
    if (op == "OR") return leftVal || rightVal;
    
    robot.selfDestruct();

    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < 2.0f) {
        graphics.handleEvents();
        graphics.render(robot);
    }    

    throw std::runtime_error("Unknown operator: " + op);
}

GenericValue UnaryOpNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    GenericValue val = operand->eval(robot, vars, graphics);
    
    if (op == "NOT") {
        return !val;
    }
    
    robot.selfDestruct();

    sf::Clock clock;
    while (clock.getElapsedTime().asSeconds() < 2.0f) {
        graphics.handleEvents();
        graphics.render(robot);
    }

    throw std::runtime_error("Unknown unary operator: " + op);
}

GenericValue ReduceNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    GenericValue array = operand->eval(robot, vars, graphics);
    
    if (array.type != DataType::ARRAY) {
        robot.selfDestruct();

        sf::Clock clock;
        while (clock.getElapsedTime().asSeconds() < 2.0f) {
            graphics.handleEvents();
            graphics.render(robot);
        }

        throw std::runtime_error("REDUCE can only be applied to arrays");
    }

    std::vector<int> computedDims;
    for (auto dimExpr : newDims) {
        GenericValue dimVal = dimExpr->eval(robot, vars, graphics);
        if (dimVal.type != DataType::INT) {
            robot.selfDestruct();

            sf::Clock clock;
            while (clock.getElapsedTime().asSeconds() < 2.0f) {
                graphics.handleEvents();
                graphics.render(robot);
            }

            throw std::runtime_error("REDUCE dimensions must be integers");
        }
        computedDims.push_back(boost::get<int>(dimVal.value));
    }

    return array.reduce(computedDims);
}

GenericValue ExtendNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    GenericValue array = operand->eval(robot, vars, graphics);
    
    if (array.type != DataType::ARRAY) {
        robot.selfDestruct();

        sf::Clock clock;
        while (clock.getElapsedTime().asSeconds() < 2.0f) {
            graphics.handleEvents();
            graphics.render(robot);
        }

        throw std::runtime_error("EXTEND can only be applied to arrays");
    }

    std::vector<int> computedDims;
    for (auto dimExpr : newDims) {
        GenericValue dimVal = dimExpr->eval(robot, vars, graphics);
        if (dimVal.type != DataType::INT) {
            robot.selfDestruct();

            sf::Clock clock;
            while (clock.getElapsedTime().asSeconds() < 2.0f) {
                graphics.handleEvents();
                graphics.render(robot);
            }

            throw std::runtime_error("EXTEND dimensions must be integers");
        }
        computedDims.push_back(boost::get<int>(dimVal.value));
    }

    return array.extend(computedDims);
}

GenericValue SwitchNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    GenericValue cond = condition->eval(robot, vars, graphics);
    
    if (cond.type != DataType::BOOL) {
        robot.selfDestruct();

        sf::Clock clock;
        while (clock.getElapsedTime().asSeconds() < 2.0f) {
            graphics.handleEvents();
            graphics.render(robot);
        }

        throw std::runtime_error("Switch condition must be boolean");
    }
    
    auto& block = (boost::get<BoolValue>(cond.value) == BoolValue::TRUE) ? trueBlock : falseBlock;
    GenericValue result;
    
    for (auto stmt : block) {
        result = stmt->eval(robot, vars, graphics);
        if (result.getRet()) break;
    }
    
    return result;
}

GenericValue ForNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    GenericValue boundaryVal = boundary->eval(robot, vars, graphics);
    GenericValue stepVal = step->eval(robot, vars, graphics);
    
    if (boundaryVal.type != DataType::INT || stepVal.type != DataType::INT) {
        robot.selfDestruct();

        sf::Clock clock;
        while (clock.getElapsedTime().asSeconds() < 2.0f) {
            graphics.handleEvents();
            graphics.render(robot);
        }

        throw std::runtime_error("FOR boundary and step must be integers");
    }
    
    int bound = boost::get<int>(boundaryVal.value);
    int stepSize = boost::get<int>(stepVal.value);
    
    bool counterExists = vars.exists(counterVar);
    GenericValue originalCounterValue;
    
    if (counterExists) {
        originalCounterValue = vars.getVariable(counterVar);
    }
    else {
        vars.addVariable(counterVar, GenericValue(0));
    }
    
    GenericValue result;
    for (int i = 1; i <= bound; i += stepSize) {
        vars.setVariable(counterVar, GenericValue(i));
        
        for (auto stmt : body) {
            result = stmt->eval(robot, vars, graphics);
            if (result.getRet()) {
                if (counterExists) {
                    vars.setVariable(counterVar, originalCounterValue);
                }
                return result;
            }
            
            if (robot.isDestroyed()) {

                sf::Clock clock;
                while (clock.getElapsedTime().asSeconds() < 2.0f) {
                    graphics.handleEvents();
                    graphics.render(robot);
                }

                throw std::runtime_error("Robot destroyed during FOR loop");
            }
        }
    }
    
    if (counterExists) {
        vars.setVariable(counterVar, originalCounterValue);
    }
    else {
        vars.removeVariable(counterVar);
    }
    
    return GenericValue();
}

GenericValue RobotCommandNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    switch(cmd) {
        case MOVE:
            if(!robot.move()){
                sf::Clock clock;
                while (clock.getElapsedTime().asSeconds() < 2.0f) {
                    graphics.handleEvents();
                    graphics.render(robot);
                }
                throw std::runtime_error("Robot selfDestruct");
            }
            graphics.handleEvents();
            graphics.render(robot);
            return GenericValue(BoolValue::TRUE);
        case ROTATE_LEFT:
            robot.rotateLeft();
            graphics.handleEvents();
            graphics.render(robot);
            return GenericValue(BoolValue::TRUE);
        case ROTATE_RIGHT:
            robot.rotateRight();
            graphics.handleEvents();
            graphics.render(robot);
            return GenericValue(BoolValue::TRUE);
        case GET_ENVIRONMENT:
            return robot.getEnvironment();
    }
    return GenericValue(BoolValue::UNDEF);
}

GenericValue ReturnNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    return expr->eval(robot, vars, graphics);
}

GenericValue FunctionNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    VariableTable localVars;
    for (const auto& var : vars.getVariables()) {
        localVars.addVariable(var->name, var->value, var->isConst);
    }

    for (const auto& param : paramNames) {
        if (!localVars.exists(param)) {
            localVars.addVariable(param, GenericValue()); 
        }
    }

    return body->eval(robot, localVars, graphics);
}

GenericValue FunctionCallNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    FunctionNode* func = FunctionTable::instance().getFunction(name);
    if (!func) {
        robot.selfDestruct();

        sf::Clock clock;
        while (clock.getElapsedTime().asSeconds() < 2.0f) {
            graphics.handleEvents();
            graphics.render(robot);
        }

        throw std::runtime_error("Function not found: " + name);
    }

    const auto& paramNames = func->getParamNames();
    if (args.size() != paramNames.size()) {
        robot.selfDestruct();

        sf::Clock clock;
        while (clock.getElapsedTime().asSeconds() < 2.0f) {
            graphics.handleEvents();
            graphics.render(robot);
        }

        throw std::runtime_error("Function " + name + ": argument count mismatch");
    }

    VariableTable localVars;

    for (size_t i = 0; i < args.size(); ++i) {
        GenericValue value = args[i]->eval(robot, vars, graphics);
        localVars.addVariable(paramNames[i], value);
    }

    try {
        return func->getBody()->eval(robot, localVars, graphics);
    } catch (const ReturnValue& rv) {
        return rv.value;
    }
}
GenericValue PrintNode::eval(Robot& robot, VariableTable& vars, Graphics& graphics) {
    GenericValue value = expr->eval(robot, vars, graphics);
    std::cout << value.toString() << std::endl;
    return GenericValue(); 
}
