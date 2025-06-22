#pragma once
#include "bases.h"
#include <iostream>
#include <memory>
#include <sstream>
#include <stdexcept>
#include <algorithm> 
#include <numeric> 
#include <boost/variant.hpp>

class GenericValue {
public:
    using ValueType = boost::variant<BoolValue,int,CellType,std::vector<GenericValue>>;

    DataType type;
    Dimension dimensions;
    ValueType value;

    bool isReturn = false;
    void setReturnFlag() { isReturn = true; }
    bool getRet() const { return isReturn; }

    GenericValue() : type(DataType::BOOL), value(BoolValue::FALSE) {}
    GenericValue(BoolValue b) : type(DataType::BOOL), value(b) {}
    GenericValue(int i) : type(DataType::INT), value(i) {}
    GenericValue(CellType c) : type(DataType::CELL), value(c) {}
    GenericValue(const std::vector<GenericValue>& arr)
    : type(DataType::ARRAY), value(arr) {
    dimensions.sizes.push_back(arr.size());
        if (!arr.empty() && arr[0].type == DataType::ARRAY) {
            const auto& subDims = arr[0].dimensions;
            dimensions.sizes.insert(dimensions.sizes.end(), subDims.sizes.begin(), subDims.sizes.end());
        }
    }
    
    static GenericValue createArray(const std::vector<int>& dims, const GenericValue& fill) {
        if (dims.empty()) return fill;

        int size = dims[0];
        std::vector<int> subDims(dims.begin() + 1, dims.end());
        std::vector<GenericValue> result(size);

        for (int i = 0; i < size; ++i)
            result[i] = createArray(subDims, fill);

        GenericValue array(result);
        array.dimensions.sizes = dims;
        return array;
    }


    GenericValue& at(size_t index) {
        if (type != DataType::ARRAY) {
            throw std::runtime_error("Not an array");
        }
        auto& arr = boost::get<std::vector<GenericValue>>(value);
        if (index >= arr.size()) {
            throw std::runtime_error("Array index out of bounds");
        }
        return arr.at(index);
    }

    GenericValue digitize() const;
    GenericValue logitize() const;
    
    GenericValue reduce(const std::vector<int>& newDims) const;
    GenericValue extend(const std::vector<int>& newDims) const;

    GenericValue operator+(const GenericValue& other) const;
    GenericValue operator-(const GenericValue& other) const;
    GenericValue operator*(const GenericValue& other) const;
    GenericValue operator/(const GenericValue& other) const;
    
    GenericValue operator==(const GenericValue& other) const;
    GenericValue operator<=(const GenericValue& other) const;
    GenericValue operator>=(const GenericValue& other) const;
    GenericValue operator!=(const GenericValue& other) const;
    
    GenericValue operator!() const;
    GenericValue operator&&(const GenericValue& other) const;
    GenericValue operator||(const GenericValue& other) const;
    
    //void checkType(DataType expected) const;
    //void checkDimensions(const GenericValue& other) const;
    
    GenericValue size() const;

    std::string toString() const {
        std::ostringstream oss;
        
        switch (type) {
            case DataType::BOOL: {
                auto val = boost::get<BoolValue>(value);
                oss << (val == BoolValue::TRUE ? "TRUE" : 
                       val == BoolValue::FALSE ? "FALSE" : "UNDEF");
                break;
            }
            case DataType::INT:
                oss << boost::get<int>(value);
                break;
            case DataType::CELL: {
                auto val = boost::get<CellType>(value);
                oss << (val == CellType::EMPTY ? "EMPTY" :
                       val == CellType::WALL ? "WALL" :
                       val == CellType::EXIT ? "EXIT" : "UNKNOWN");
                break;
            }
            case DataType::ARRAY: {
                const auto& arr = boost::get<std::vector<GenericValue>>(value);
                oss << "[";
                for (size_t i = 0; i < arr.size(); ++i) {
                    if (i > 0) oss << ", ";
                    oss << arr[i].toString();
                }
                oss << "]";
                break;
            }
        }
        
        return oss.str();
    }
};

class Variable {
public:
    std::string name;
    GenericValue value;
    bool isConst;
    
    Variable(std::string n, GenericValue v, bool c = false)
        : name(std::move(n)), value(std::move(v)), isConst(c) {}
};

class VariableTable {
public:
    std::vector<std::unique_ptr<Variable>> variables;
    void addVariable(std::string name, GenericValue value, bool isConst = false);
    GenericValue& getVariable(const std::string& name);
        const std::vector<std::unique_ptr<Variable>>& getVariables() const {
        return variables;
    }
    bool exists(const std::string& name) const;

    void removeVariable(const std::string& name) {
        auto it = std::remove_if(variables.begin(), variables.end(),
            [&](const std::unique_ptr<Variable>& var) {
                return var->name == name;
            });
        variables.erase(it, variables.end());
    }

    void setVariable(const std::string& name, GenericValue value) {
        for (auto& var : variables) {
            if (var->name == name) {
                if (var->isConst) {
                    throw std::runtime_error("Переменная '" + name + "' является константой");
                }
                var->value = std::move(value);
                return;
            }
        }
        throw std::runtime_error("Переменная не найдена: " + name);
    }
};