#include "genericType.h"
#include <boost/variant.hpp>
#include <stdexcept>
#include <numeric>

using namespace std;

namespace {
    template<typename T>
    bool holds_alternative(const GenericValue::ValueType& v) {
        return boost::get<T>(&v) != nullptr;
    }

    void checkDimensionsMatch(const GenericValue& a, const GenericValue& b) {
        if (a.dimensions.sizes != b.dimensions.sizes) {
            throw runtime_error("Размерности не совпадают");
        }
    }
}

GenericValue GenericValue::digitize() const {
    GenericValue result;
    result.type = DataType::INT;
    
    switch (type) {
        case DataType::BOOL:
            result.value = (boost::get<BoolValue>(value) == BoolValue::TRUE) ? 1 : 0;
            break;
        case DataType::INT:
            result.value = boost::get<int>(value);
            break;
        case DataType::CELL:
            result.value = (boost::get<CellType>(value) == CellType::EMPTY) ? 0 : 1;
            break;
        case DataType::ARRAY: {
            vector<GenericValue> newArr;
            const auto& arr = boost::get<vector<GenericValue>>(value);
            transform(arr.begin(), arr.end(), back_inserter(newArr), 
                    [](const GenericValue& v) { return v.digitize(); });
            result.value = newArr;
            result.type = DataType::ARRAY;
            break;
        }
    }
    
    result.dimensions = dimensions;
    return result;
}

GenericValue GenericValue::logitize() const {
    GenericValue result;
    result.type = DataType::BOOL;
    
    switch (type) {
        case DataType::BOOL:
            result.value = boost::get<BoolValue>(value);
            break;
        case DataType::INT: {
            int val = boost::get<int>(value);
            result.value = (val != 0) ? BoolValue::TRUE : BoolValue::FALSE;
            break;
        }
        case DataType::CELL: {
            CellType cell = boost::get<CellType>(value);
            result.value = (cell == CellType::EMPTY) ? BoolValue::FALSE : BoolValue::TRUE;
            break;
        }
        case DataType::ARRAY: {
            vector<GenericValue> newArr;
            const auto& arr = boost::get<vector<GenericValue>>(value);
            transform(arr.begin(), arr.end(), back_inserter(newArr),
                    [](const GenericValue& v) { return v.logitize(); });
            result.value = newArr;
            result.type = DataType::ARRAY;
            break;
        }
    }
    
    result.dimensions = dimensions;
    return result;
}

GenericValue GenericValue::reduce(const vector<int>& newDims) const {
    if (type != DataType::ARRAY) {
        throw runtime_error("REDUCE применяется только к массивам");
    }

    size_t totalElements = 1;
    for (int d : newDims) {
        if (d <= 0) {
            throw runtime_error("Недопустимая размерность в REDUCE");
        }
        totalElements *= d;
    }

    const auto& arr = boost::get<vector<GenericValue>>(value);
    if (totalElements > arr.size()) {
        throw runtime_error("Новая размерность больше исходной в REDUCE");
    }

    vector<GenericValue> newArr(arr.begin(), arr.begin() + totalElements);
    
    GenericValue result;
    result.type = DataType::ARRAY;
    result.value = newArr;
    result.dimensions.sizes = newDims;
    return result;
}

GenericValue GenericValue::extend(const vector<int>& newDims) const {
    if (type != DataType::ARRAY) {
        throw runtime_error("EXTEND применяется только к массивам");
    }

    const auto& arr = boost::get<vector<GenericValue>>(value);
    size_t totalElements = 1;
    for (int d : newDims) {
        if (d <= 0) {
            throw runtime_error("Недопустимая размерность в EXTEND");
        }
        totalElements *= d;
    }

    if (totalElements < arr.size()) {
        throw runtime_error("Новая размерность меньше исходной в EXTEND");
    }

    vector<GenericValue> newArr = arr;
    newArr.resize(totalElements);

    GenericValue defaultValue;
    if (!arr.empty()) {
        defaultValue = arr[0].type == DataType::BOOL ? 
            GenericValue(BoolValue::FALSE) : GenericValue(0);
    }

    for (size_t i = arr.size(); i < totalElements; ++i) {
        newArr[i] = defaultValue;
    }

    GenericValue result;
    result.type = DataType::ARRAY;
    result.value = newArr;
    result.dimensions.sizes = newDims;
    return result;
}

GenericValue GenericValue::operator+(const GenericValue& other) const {
    if (type != other.type) {
        throw runtime_error("Несоответствие типов в операции +");
    }

    if (type == DataType::ARRAY) {
        checkDimensionsMatch(*this, other);
        vector<GenericValue> result;
        const auto& arr1 = boost::get<vector<GenericValue>>(value);
        const auto& arr2 = boost::get<vector<GenericValue>>(other.value);
        
        transform(arr1.begin(), arr1.end(), arr2.begin(), back_inserter(result),
                [](const GenericValue& a, const GenericValue& b) { return a + b; });
        
        GenericValue res;
        res.type = DataType::ARRAY;
        res.value = result;
        res.dimensions = dimensions;
        return res;
    }

    GenericValue result;
    result.type = type;
    result.dimensions = dimensions;

    if (type == DataType::INT) {
        result.value = boost::get<int>(value) + boost::get<int>(other.value);
    } else if (type == DataType::BOOL) {
        result.value = (boost::get<BoolValue>(value) == BoolValue::TRUE || 
                       boost::get<BoolValue>(other.value) == BoolValue::TRUE) ? 
                       BoolValue::TRUE : BoolValue::FALSE;
    } else {
        throw runtime_error("Операция + не поддерживается для данного типа");
    }

    return result;
}

GenericValue GenericValue::operator-(const GenericValue& other) const {
    if (type != other.type) {
        throw runtime_error("Несоответствие типов в операции -");
    }

    if (type == DataType::ARRAY) {
        checkDimensionsMatch(*this, other);
        vector<GenericValue> result;
        const auto& arr1 = boost::get<vector<GenericValue>>(value);
        const auto& arr2 = boost::get<vector<GenericValue>>(other.value);
        
        transform(arr1.begin(), arr1.end(), arr2.begin(), back_inserter(result),
                [](const GenericValue& a, const GenericValue& b) { return a - b; });
        
        GenericValue res;
        res.type = DataType::ARRAY;
        res.value = result;
        res.dimensions = dimensions;
        return res;
    }

    GenericValue result;
    result.type = type;
    result.dimensions = dimensions;

    if (type == DataType::INT) {
        result.value = boost::get<int>(value) - boost::get<int>(other.value);
    } else if (type == DataType::BOOL) {
        result.value = (boost::get<BoolValue>(value) == BoolValue::TRUE || 
                       boost::get<BoolValue>(other.value) == BoolValue::TRUE) ? 
                       BoolValue::TRUE : BoolValue::FALSE;
    } else {
        throw runtime_error("Операция - не поддерживается для данного типа");
    }

    return result;
}

GenericValue GenericValue::operator*(const GenericValue& other) const {
    if (type != other.type) {
        throw runtime_error("Несоответствие типов в операции *");
    }

    if (type == DataType::ARRAY) {
        checkDimensionsMatch(*this, other);
        vector<GenericValue> result;
        const auto& arr1 = boost::get<vector<GenericValue>>(value);
        const auto& arr2 = boost::get<vector<GenericValue>>(other.value);
        
        transform(arr1.begin(), arr1.end(), arr2.begin(), back_inserter(result),
                [](const GenericValue& a, const GenericValue& b) { return a + b; });
        
        GenericValue res;
        res.type = DataType::ARRAY;
        res.value = result;
        res.dimensions = dimensions;
        return res;
    }

    GenericValue result;
    result.type = type;
    result.dimensions = dimensions;

    if (type == DataType::INT) {
        result.value = boost::get<int>(value) * boost::get<int>(other.value);
    } else if (type == DataType::BOOL) {
        result.value = (boost::get<BoolValue>(value) == BoolValue::TRUE || 
                       boost::get<BoolValue>(other.value) == BoolValue::TRUE) ? 
                       BoolValue::TRUE : BoolValue::FALSE;
    } else {
        throw runtime_error("Операция * не поддерживается для данного типа");
    }

    return result;
}

GenericValue GenericValue::operator/(const GenericValue& other) const {
    if (type != other.type) {
        throw runtime_error("Несоответствие типов в операции /");
    }

    if (type == DataType::ARRAY) {
        checkDimensionsMatch(*this, other);
        vector<GenericValue> result;
        const auto& arr1 = boost::get<vector<GenericValue>>(value);
        const auto& arr2 = boost::get<vector<GenericValue>>(other.value);
        
        transform(arr1.begin(), arr1.end(), arr2.begin(), back_inserter(result),
                [](const GenericValue& a, const GenericValue& b) { return a + b; });
        
        GenericValue res;
        res.type = DataType::ARRAY;
        res.value = result;
        res.dimensions = dimensions;
        return res;
    }

    GenericValue result;
    result.type = type;
    result.dimensions = dimensions;

    if (type == DataType::INT) {
        result.value = boost::get<int>(value) / boost::get<int>(other.value);
    } else if (type == DataType::BOOL) {
        result.value = (boost::get<BoolValue>(value) == BoolValue::TRUE || 
                       boost::get<BoolValue>(other.value) == BoolValue::TRUE) ? 
                       BoolValue::TRUE : BoolValue::FALSE;
    } else {
        throw runtime_error("Операция / не поддерживается для данного типа");
    }

    return result;
}

GenericValue GenericValue::operator==(const GenericValue& other) const {
    if (type != other.type) {
        return GenericValue(BoolValue::FALSE);
    }

    if (type == DataType::ARRAY) {
        checkDimensionsMatch(*this, other);
        vector<GenericValue> result;
        const auto& arr1 = boost::get<vector<GenericValue>>(value);
        const auto& arr2 = boost::get<vector<GenericValue>>(other.value);
        
        transform(arr1.begin(), arr1.end(), arr2.begin(), back_inserter(result),
                [](const GenericValue& a, const GenericValue& b) { return a == b; });
        
        GenericValue res;
        res.type = DataType::ARRAY;
        res.value = result;
        res.dimensions = dimensions;
        return res;
    }

    bool isEqual;
    switch (type) {
        case DataType::BOOL:
            isEqual = boost::get<BoolValue>(value) == boost::get<BoolValue>(other.value);
            break;
        case DataType::INT:
            isEqual = boost::get<int>(value) == boost::get<int>(other.value);
            break;
        case DataType::CELL:
            isEqual = boost::get<CellType>(value) == boost::get<CellType>(other.value);
            break;
        default:
            isEqual = false;
    }

    return GenericValue(isEqual ? BoolValue::TRUE : BoolValue::FALSE);
}

GenericValue GenericValue::operator<=(const GenericValue& other) const {
    if (type != other.type) {
        return GenericValue(BoolValue::FALSE);
    }

    if (type == DataType::ARRAY) {
        checkDimensionsMatch(*this, other);
        vector<GenericValue> result;
        const auto& arr1 = boost::get<vector<GenericValue>>(value);
        const auto& arr2 = boost::get<vector<GenericValue>>(other.value);
        
        transform(arr1.begin(), arr1.end(), arr2.begin(), back_inserter(result),
                [](const GenericValue& a, const GenericValue& b) { return a <= b; });
        
        GenericValue res;
        res.type = DataType::ARRAY;
        res.value = result;
        res.dimensions = dimensions;
        return res;
    }

    bool isEqual;
    switch (type) {
        case DataType::BOOL:
            isEqual = boost::get<BoolValue>(value) <= boost::get<BoolValue>(other.value);
            break;
        case DataType::INT:
            isEqual = boost::get<int>(value) <= boost::get<int>(other.value);
            break;
        case DataType::CELL:
            isEqual = boost::get<CellType>(value) <= boost::get<CellType>(other.value);
            break;
        default:
            isEqual = false;
    }

    return GenericValue(isEqual ? BoolValue::TRUE : BoolValue::FALSE);
}

GenericValue GenericValue::operator>=(const GenericValue& other) const {
    if (type != other.type) {
        return GenericValue(BoolValue::FALSE);
    }

    if (type == DataType::ARRAY) {
        checkDimensionsMatch(*this, other);
        vector<GenericValue> result;
        const auto& arr1 = boost::get<vector<GenericValue>>(value);
        const auto& arr2 = boost::get<vector<GenericValue>>(other.value);
        
        transform(arr1.begin(), arr1.end(), arr2.begin(), back_inserter(result),
                [](const GenericValue& a, const GenericValue& b) { return a >= b; });
        
        GenericValue res;
        res.type = DataType::ARRAY;
        res.value = result;
        res.dimensions = dimensions;
        return res;
    }

    bool isEqual;
    switch (type) {
        case DataType::BOOL:
            isEqual = boost::get<BoolValue>(value) >= boost::get<BoolValue>(other.value);
            break;
        case DataType::INT:
            isEqual = boost::get<int>(value) >= boost::get<int>(other.value);
            break;
        case DataType::CELL:
            isEqual = boost::get<CellType>(value) >= boost::get<CellType>(other.value);
            break;
        default:
            isEqual = false;
    }

    return GenericValue(isEqual ? BoolValue::TRUE : BoolValue::FALSE);
}

GenericValue GenericValue::operator!=(const GenericValue& other) const {
    if (type != other.type) {
        return GenericValue(BoolValue::FALSE);
    }

    if (type == DataType::ARRAY) {
        checkDimensionsMatch(*this, other);
        vector<GenericValue> result;
        const auto& arr1 = boost::get<vector<GenericValue>>(value);
        const auto& arr2 = boost::get<vector<GenericValue>>(other.value);
        
        transform(arr1.begin(), arr1.end(), arr2.begin(), back_inserter(result),
                [](const GenericValue& a, const GenericValue& b) { return a != b; });
        
        GenericValue res;
        res.type = DataType::ARRAY;
        res.value = result;
        res.dimensions = dimensions;
        return res;
    }

    bool isEqual;
    switch (type) {
        case DataType::BOOL:
            isEqual = boost::get<BoolValue>(value) != boost::get<BoolValue>(other.value);
            break;
        case DataType::INT:
            isEqual = boost::get<int>(value) != boost::get<int>(other.value);
            break;
        case DataType::CELL:
            isEqual = boost::get<CellType>(value) != boost::get<CellType>(other.value);
            break;
        default:
            isEqual = false;
    }

    return GenericValue(isEqual ? BoolValue::TRUE : BoolValue::FALSE);
}

GenericValue GenericValue::operator!() const {
    if (type != DataType::BOOL && type != DataType::ARRAY) {
        throw runtime_error("Оператор NOT применяется только к логическим значениям");
    }

    if (type == DataType::ARRAY) {
        vector<GenericValue> result;
        const auto& arr = boost::get<vector<GenericValue>>(value);
        transform(arr.begin(), arr.end(), back_inserter(result),
                [](const GenericValue& v) { return !v; });
        
        GenericValue res;
        res.type = DataType::ARRAY;
        res.value = result;
        res.dimensions = dimensions;
        return res;
    }

    BoolValue val = boost::get<BoolValue>(value);
    return GenericValue(val == BoolValue::TRUE ? BoolValue::FALSE : 
                       val == BoolValue::FALSE ? BoolValue::TRUE : BoolValue::UNDEF);
}

GenericValue GenericValue::operator&&(const GenericValue& other) const {
    if (type != DataType::BOOL && type != DataType::ARRAY) {
        throw runtime_error("Оператор AND применяется только к логическим значениям");
    }
    if (type != other.type) {
        throw runtime_error("Несоответствие типов в операции AND");
    }

    if (type == DataType::ARRAY) {
        checkDimensionsMatch(*this, other);
        vector<GenericValue> result;
        const auto& arr1 = boost::get<vector<GenericValue>>(value);
        const auto& arr2 = boost::get<vector<GenericValue>>(other.value);
        
        std::transform(arr1.begin(), arr1.end(), arr2.begin(), back_inserter(result),
            [](const GenericValue& a, const GenericValue& b) { return a && b; });
        
        GenericValue res;
        res.type = DataType::ARRAY;
        res.value = result;
        res.dimensions = dimensions;
        return res;
    }
    BoolValue val1 = boost::get<BoolValue>(value);
    BoolValue val2 = boost::get<BoolValue>(other.value);

    if (val1 == BoolValue::FALSE || val2 == BoolValue::FALSE) {
        return GenericValue(BoolValue::FALSE);
    }
    if (val1 == BoolValue::UNDEF || val2 == BoolValue::UNDEF) {
        return GenericValue(BoolValue::UNDEF);
    }
    return GenericValue(BoolValue::TRUE);
}

GenericValue GenericValue::operator||(const GenericValue& other) const {
    if (type != DataType::BOOL && type != DataType::ARRAY) {
        throw runtime_error("Оператор OR применяется только к логическим значениям");
    }
    if (type != other.type) {
        throw runtime_error("Несоответствие типов в операции OR");
    }

    if (type == DataType::ARRAY) {
        checkDimensionsMatch(*this, other);
        vector<GenericValue> result;
        const auto& arr1 = boost::get<vector<GenericValue>>(value);
        const auto& arr2 = boost::get<vector<GenericValue>>(other.value);
        
        std::transform(arr1.begin(), arr1.end(), arr2.begin(), back_inserter(result),
            [](const GenericValue& a, const GenericValue& b) { return a || b; });
        
        GenericValue res;
        res.type = DataType::ARRAY;
        res.value = result;
        res.dimensions = dimensions;
        return res;
    }

    BoolValue val1 = boost::get<BoolValue>(value);
    BoolValue val2 = boost::get<BoolValue>(other.value);

    if (val1 == BoolValue::TRUE || val2 == BoolValue::TRUE) {
        return GenericValue(BoolValue::TRUE);
    }
    if (val1 == BoolValue::UNDEF || val2 == BoolValue::UNDEF) {
        return GenericValue(BoolValue::UNDEF);
    }
    return GenericValue(BoolValue::FALSE);
}

GenericValue GenericValue::size() const {
    vector<GenericValue> result;
    for (int dim : dimensions.sizes) {
        result.emplace_back(dim);
    }
    
    GenericValue sizeArray;
    sizeArray.type = DataType::ARRAY;
    sizeArray.value = result;
    sizeArray.dimensions.sizes = {(int)result.size()};
    return sizeArray;
}

void VariableTable::addVariable(string name, GenericValue value, bool isConst) {
    if (exists(name)) {
        throw runtime_error("Переменная уже существует: " + name);
    }
    variables.emplace_back(make_unique<Variable>(move(name), move(value), isConst));
}

GenericValue& VariableTable::getVariable(const string& name) {
    for (auto& var : variables) {
        if (var->name == name) {
            if (var->isConst) {
                throw runtime_error("Попытка изменить константу: " + name);
            }
            return var->value;
        }
    }
    throw runtime_error("Переменная не найдена: " + name);
}

bool VariableTable::exists(const std::string& name) const {
    for (const auto& var : variables) {
        if (var->name == name) {
            return true;
        }
    }
    return false;
}
