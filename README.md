# Интерпретатор для клеточного робота

[![C++ Standard](https://img.shields.io/badge/C++-20-blue?logo=cplusplus)]()
[![License](https://img.shields.io/badge/License-MIT-green?logo=opensourceinitiative)]()
[![Build Status](https://img.shields.io/badge/build-passing-brightgreen?logo=githubactions)]()
[![Code Size](https://img.shields.io/github/languages/code-size/durachill/BST-C)]()
[![Last Commit](https://img.shields.io/github/last-commit/durachill/BST-C?color=blue)]()
### о проекте
Система для управления клеточным роботом, осуществляющим передвижение по квадратному клеточному лабиринту. Робот может перемещаться в соседние клетки при отсутствии препятствий. Реализован формальный язык программирования для управления роботом с последующей компиляцией через `flex` и `bison`.
## Основные возможности языка

### Литералы
- Логические: `TRUE`, `FALSE`
- Целочисленные:
  - Восьмеричные: `077` (начинаются с `0`)
  - Десятичные: `123` (без цифр `8`,`9`)
  - Шестнадцатеричные: `0x1F` (начинаются с `0x`)

### Переменные
```robot
VAR matrix[2,3] = 0;      // 2x3 матрица с нулями
VAR scalar = TRUE;          // Логический скаляр
```
### Операции
- **Индексация:** matrix[[1,2]]
- **Размерность:** SIZE(matrix) → временный массив размерности
- **Преобразование типов:**
  - LOGITIZE var → логический тип
  - DIGITIZE var → целочисленный тип
- **Изменение** размерности:
  - REDUCE var [new_dim]
  - EXTEND var [new_dim]
- **Арифметические:** +, -, *, /
- **Логические:** NOT, AND

## Функции
```robot
TASK FACTORIAL(n) {
    VAR res = 0;
    SWITCH ((n == 0) OR (n == 1)){
        res = 1;
    }ELSE{
        res =  (n*(DO FACTORIAL(n - 1)));
    }
    RESULT res;
}

TASK FINDEXIT() {
    VAR number = 5;
    VAR fact = DO FACTORIAL(number);
    PRINT fact;
    RESULT 0;
}
```

## Управление клеточным роботом
| Команда           | Действие                              | Риск самоуничтожения               | Пример кода                   |
|-------------------|---------------------------------------|-------------------------------------|-------------------------------|
| **MOVE**          | Перемещение на 1 клетку вперед        | При столкновении с препятствием     | `PLEASE MOVE THANKS`          |
| **ROTATE LEFT**   | Поворот на 90° против часовой стрелки | При >4 повторах без движения        | `PLEASE ROTATE LEFT THANKS`   |
| **ROTATE RIGHT**  | Поворот на 90° по часовой стрелке     | При >4 повторах без движения        | `PLEASE ROTATE RIGHT THANKS`  |
| **GET ENVIRONMENT**| Получение 3D-карты окружения (N×N×2) | При >3 запросах без движения        | `PLEASE GET ENVIRONMENT THANKS` |

> [!WARNING]
> Для запуска проекта необходимо установить flex и bison
## Запуск проекта
```
git clone https://github.com/mariiamonk/robot-interpreter.git
make
./robot_system <name_of_file>  
```
