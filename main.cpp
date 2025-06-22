#include "scanner.h"
#include "graphics/graphics.h"
#include "ast/ast.h"
#include "robot/robot.h"
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stdexcept>

using Parser = yy::parser;
extern Robot robot;
extern Graphics graphics;
extern VariableTable vars;
extern FunctionTable global_functions;;

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: ./robot_system <filename>" << std::endl;
        return 1;
    }

    std::ifstream input(argv[1]);
    if (!input) {
        std::cerr << "Failed to open file: " << argv[1] << std::endl;
        return 1;
    }

    Scanner scanner;
    Parser parser(scanner);
    scanner.yyrestart(&input);

    auto result = parser.parse();
    if (result != 0) {
        std::cerr << "Parsing failed!" << std::endl;
        return 1;
    }


    return 0;
}
