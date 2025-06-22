#ifndef ROBOT_H
#define ROBOT_H
#include "../ast/bases.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <thread>
#include <chrono>
#include "../ast/genericType.h"

class Robot {
    Cell position = {0, 0}; 
    Direction direction = Direction::NORTH; 
    int rotationCount = 0;
    int envRequests = 0;
    bool destroyed = false;
    bool exitReached = false; 
    Environment env;
    
    bool visualize = true;
    int animationDelay = 20;

    int mood = 3; 
    const int MAX_ENV_REQUESTS = 5; 
    const int MAX_SIGHT = 5;
public:

    Robot() {
        env.robotDirection = direction;
    }

    Cell getPosition() const { return position; }
    Direction getDirection() const { return direction; }

    void loadMapFromFile(const std::string& filename) {
        std::ifstream file(filename);
        if (!file.is_open()) {
            throw std::runtime_error("Не удалось открыть файл с картой: " + filename);
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(file, line)) {
            if (!line.empty()) {
                lines.push_back(line);
            }
        }

        if (lines.empty()) {
            throw std::runtime_error("Файл карты пуст");
        }

        size_t width = lines[0].size();
        size_t height = lines.size();

        env.walls.resize(height, std::vector<CellType>(width, CellType::EMPTY));
        env.exits.resize(height, std::vector<CellType>(width, CellType::EMPTY));

        for (size_t y = 0; y < height; ++y) {
            if (lines[y].size() != width) {
                throw std::runtime_error("Все строки карты должны быть одинаковой длины");
            }

            for (size_t x = 0; x < width; ++x) {
                char c = lines[y][x];
                switch (c) {
                    case '#': // Стена
                        env.walls[y][x] = CellType::WALL;
                        break;
                    case 'Q': // Выход
                        env.exits[y][x] = CellType::EXIT;
                        break;
                    case '^': 
                        position = {static_cast<int>(y), static_cast<int>(x)};
                        direction = Direction::NORTH;
                        break;
                    case '>': 
                        position = {static_cast<int>(y), static_cast<int>(x)};
                        direction = Direction::EAST;
                        break;
                    case 'v': 
                        position = {static_cast<int>(y), static_cast<int>(x)};
                        direction = Direction::SOUTH;
                        break;
                    case '<': 
                        position = {static_cast<int>(y), static_cast<int>(x)};
                        direction = Direction::WEST;
                        break;
                    case '.': 
                        break;
                    default:
                        throw std::runtime_error("Неизвестный символ в карте: " + std::string(1, c));
                }
            }
        }

        env.robotDirection = direction;
    }

    GenericValue getMapAsGenericValue() const {
        std::vector<GenericValue> wallsLayer;
        std::vector<GenericValue> exitsLayer;

        for (const auto& row : env.walls) {
            std::vector<GenericValue> wallRow;
            for (CellType cell : row) {
                wallRow.emplace_back(cell);
            }
            wallsLayer.emplace_back(wallRow);
        }

        for (const auto& row : env.exits) {
            std::vector<GenericValue> exitRow;
            for (CellType cell : row) {
                exitRow.emplace_back(cell);
            }
            exitsLayer.emplace_back(exitRow);
        }

        Dimension dim;
        dim.sizes = {static_cast<int>(env.walls.size()), 
                    static_cast<int>(env.walls[0].size()), 
                    2};

        GenericValue result;
        result.type = DataType::ARRAY;
        result.value = std::vector<GenericValue>{wallsLayer, exitsLayer};
        result.dimensions = dim;
        return result;
    }
    
    bool isDestroyed() const { return destroyed; }
    void selfDestruct() { 
        destroyed = true; 
    }
    
    void enableVisualization(bool enable, int delayMs = 300) {
        visualize = enable;
        animationDelay = delayMs;
    }

    void animationPause() const {
        if (visualize) {
            std::this_thread::sleep_for(std::chrono::milliseconds(animationDelay));
        }
    }

    bool hasReachedExit() const {
        return exitReached;
    }

    GenericValue buildVisibleEnvironment() const {
        const int size = 2 * MAX_SIGHT + 1;
        std::vector<std::vector<BoolValue>> wallsLayer(size, std::vector<BoolValue>(size, BoolValue::FALSE));
        std::vector<std::vector<BoolValue>> exitsLayer(size, std::vector<BoolValue>(size, BoolValue::FALSE));
        
        const int center = MAX_SIGHT;
        wallsLayer[center][center] = BoolValue::FALSE;
        exitsLayer[center][center] = BoolValue::FALSE;
        
        std::pair<int, int> forward_dir, right_dir, back_dir, left_dir;
        
        switch(direction) {
            case Direction::NORTH:
                forward_dir = {-1, 0};  // Север
                right_dir = {0, 1};     // Восток
                back_dir = {1, 0};      // Юг
                left_dir = {0, -1};     // Запад
                break;
            case Direction::EAST:
                forward_dir = {0, 1};   // Восток
                right_dir = {1, 0};     // Юг
                back_dir = {0, -1};     // Запад
                left_dir = {-1, 0};     // Север
                break;
            case Direction::SOUTH:
                forward_dir = {1, 0};   // Юг
                right_dir = {0, -1};    // Запад
                back_dir = {-1, 0};     // Север
                left_dir = {0, 1};      // Восток
                break;
            case Direction::WEST:
                forward_dir = {0, -1};  // Запад
                right_dir = {-1, 0};    // Север
                back_dir = {0, 1};      // Восток
                left_dir = {1, 0};      // Юг
                break;
        }
        
        const std::vector<std::pair<int, int>> relative_directions = {
            forward_dir, right_dir, back_dir, left_dir
        };
        
        for (const auto& dir : relative_directions) {
            for (int d = 1; d <= mood; d++) {
                int y = position.first + dir.first * d;
                int x = position.second + dir.second * d;
                
                if (y < 0 || y >= env.walls.size() || x < 0 || x >= env.walls[0].size()) {
                    break;
                }
                
                int visY = center;
                int visX = center;
                
                if (dir == forward_dir) {
                    visY -= d;  // Вперед - уменьшение Y
                } else if (dir == right_dir) {
                    visX += d;  // Вправо - увеличение X
                } else if (dir == back_dir) {
                    visY += d;  // Назад - увеличение Y
                } else if (dir == left_dir) {
                    visX -= d;  // Влево - уменьшение X
                }
                
                if (visY < 0 || visY >= size || visX < 0 || visX >= size) {
                    break;
                }
                
                if (env.walls[y][x] == CellType::WALL) {
                    wallsLayer[visY][visX] = BoolValue::TRUE;
                    break;
                }
                
                if (env.exits[y][x] == CellType::EXIT) {
                    exitsLayer[visY][visX] = BoolValue::TRUE;
                }
            }
        }
        
        // Заполняем результат
        std::vector<GenericValue> resultArray;
        for (int i = 0; i < size; i++) {
            std::vector<GenericValue> row;
            for (int j = 0; j < size; j++) {
                std::vector<GenericValue> cell;
                cell.push_back(GenericValue(wallsLayer[i][j])); // слой 1 - стены
                cell.push_back(GenericValue(exitsLayer[i][j])); // слой 2 - выходы
                row.push_back(GenericValue(cell));
            }
            resultArray.push_back(GenericValue(row));
        }

        Dimension dim;
        dim.sizes = {size, size, 2};
        
        GenericValue result;
        result.type = DataType::ARRAY;
        result.value = resultArray;
        result.dimensions = dim;
        
        return result;
    }

    int getMood() const { return mood; } 

    GenericValue getEnvironment() {
        if (destroyed) return GenericValue();
        
        envRequests++;
        if (envRequests > MAX_ENV_REQUESTS) {
            std::cout << "Робот обиделся из-за слишком частых запросов!\n";
            selfDestruct();
            return GenericValue();
        }
        
        GenericValue result = buildVisibleEnvironment();
        
        const auto& exits = boost::get<std::vector<GenericValue>>(
            boost::get<std::vector<GenericValue>>(result.value)[1].value
        );
        
        bool exitSeen = false;
        for (const auto& row : exits) {
            const auto& rowValues = boost::get<std::vector<GenericValue>>(row.value);
            for (const auto& cell : rowValues) {
                if (boost::get<BoolValue>(cell.value) == BoolValue::TRUE) {
                    exitSeen = true;
                    break;
                }
            }
            if (exitSeen) break;
        }
        
        if (exitSeen) {
            mood = std::min(mood + 1, MAX_SIGHT);
            std::cout << "Робот увидел выход! Настроение улучшено до: " << mood << "\n";
        }
        
        return result;
    }

    bool move() {
        if (destroyed || exitReached) return false;
        
        if (visualize) {
            animationPause();
        }
        
        Cell newPos = position;
        switch (direction) {
            case Direction::NORTH: newPos.first--; break;
            case Direction::EAST:  newPos.second++; break;
            case Direction::SOUTH: newPos.first++; break;
            case Direction::WEST:  newPos.second--; break;
        }
        
        if (newPos.first < 0 || newPos.first >= env.walls.size() ||
            newPos.second < 0 || newPos.second >= env.walls[0].size() ||
            env.walls[newPos.first][newPos.second] == CellType::WALL) {
            selfDestruct();
            if (visualize) {
                std::cout << "Движение невозможно!";
                animationPause();
            }
            return false;
        }
        
        position = newPos;
        envRequests = 0;
        rotationCount = 0;
        env.robotDirection = direction;
        
        if (env.exits[position.first][position.second] == CellType::EXIT) {
            exitReached = true;
            if (visualize) {
                std::cout << "\n\nРобот достиг выхода! Миссия выполнена!\n";
                animationPause();
            }
            return true;
        }
        
        if (visualize) {
            animationPause();
        }
        
        return true;
    }
    
    void rotateLeft() {
        if (!destroyed && !exitReached) {
            if (visualize) {
                animationPause();
            }
            
            rotationCount++;
            direction = static_cast<Direction>((static_cast<int>(direction) + 3) % 4);
            env.robotDirection = direction;
            
            if (visualize) {
                animationPause();
            }
            
            if (rotationCount > 4) {
                std::cout << "Робот слишком долго вертится на месте!";
                selfDestruct();
            }
        }
    }
    
    void rotateRight() {
        if (!destroyed && !exitReached) {
            if (visualize) {
                animationPause();
            }
            
            rotationCount++;
            direction = static_cast<Direction>((static_cast<int>(direction) + 1) % 4);
            env.robotDirection = direction;
            
            if (rotationCount > 4) {
                std::cout << "Робот слишком долго вертится на месте!";
                selfDestruct();
            }
        }
    }
    
    int getRotationCount() const { return rotationCount; }
    
    const Environment& getEnvironmentC() const { return env; }
    
    void resetRotationCount() { rotationCount = 0; }
    void resetEnvironmentRequests() { envRequests = 0; }

    
};
#endif