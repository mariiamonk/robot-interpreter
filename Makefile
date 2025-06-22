CXX = g++
CXXFLAGS = -std=c++17 -I. -Iast -Irobot -Igenerated -Igraphics
LDFLAGS = -lboost_system -lboost_filesystem -lfl -lsfml-graphics -lsfml-window -lsfml-system

SRC_DIR = .
BUILD_DIR = build
GEN_DIR = generated
TARGET = robot_system

# Source files
LEX_SRC = robot/robot.l
YACC_SRC = robot/robot.y
SRCS = $(wildcard $(SRC_DIR)/*.cpp ast/*.cpp robot/*.cpp graphics/*.cpp)
GEN_SRCS = $(GEN_DIR)/lex.yy.cpp $(GEN_DIR)/robot.tab.cpp

# Object files
OBJS = $(patsubst $(SRC_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(SRCS))
GEN_OBJS = $(patsubst $(GEN_DIR)/%.cpp,$(BUILD_DIR)/%.o,$(GEN_SRCS))

all: $(TARGET)

$(TARGET): $(OBJS) $(GEN_OBJS)
	$(CXX) $(CXXFLAGS) $^ -o $@ $(LDFLAGS)

# Rule for flex generated files
$(GEN_DIR)/lex.yy.cpp $(GEN_DIR)/lex.yy.h: $(LEX_SRC) $(GEN_DIR)/robot.tab.h
	@mkdir -p $(GEN_DIR)
	flex --header-file=$(GEN_DIR)/lex.yy.h -o $@ $<

# Rule for bison generated files
$(GEN_DIR)/robot.tab.cpp $(GEN_DIR)/robot.tab.h: $(YACC_SRC)
	@mkdir -p $(GEN_DIR)
	bison -d -o $(GEN_DIR)/robot.tab.cpp --defines=$(GEN_DIR)/robot.tab.h -Wcounterexamples -Hparser.hpp $<

# Compile generated lexer
$(BUILD_DIR)/lex.yy.o: $(GEN_DIR)/lex.yy.cpp $(GEN_DIR)/robot.tab.h
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile generated parser
$(BUILD_DIR)/robot.tab.o: $(GEN_DIR)/robot.tab.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Compile regular source files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

copy_assets:
	mkdir -p $(BUILD_DIR)/graphics/sprites
	cp -r graphics/sprites/* $(BUILD_DIR)/graphics/sprites/

run: $(TARGET) copy_assets
	cd $(BUILD_DIR) && ./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(GEN_DIR) $(TARGET)

test: $(TARGET)
	./$(TARGET) test_prog.txt map.txt

.PHONY: all clean test