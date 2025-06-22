#pragma once

#include <vector>
#include <string>
#include <variant>

// Базовые типы значений
enum class BoolValue {
    TRUE,
    FALSE,
    UNDEF
};

enum class IntBase {
    ZERO,
    POS,
    NEG,
    NAN
};

enum class CellType {
    EMPTY,
    WALL,
    EXIT,
    ROBOT,
    UNKNOWN
};

enum class Direction {
    NORTH, //^
    EAST,  //>
    SOUTH, //v
    WEST   //<
};

using Cell = std::pair<int, int>;

enum class DataType {
    BOOL,
    INT,
    CELL,
    ARRAY
};

//для представления размерности
struct Dimension {
    std::vector<int> sizes;
    bool isDynamic = false;
};

//окружение
struct Environment {
    std::vector<std::vector<CellType>> walls;
    std::vector<std::vector<CellType>> exits;
    Direction robotDirection;
};