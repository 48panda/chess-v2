# makefile for C++
# get all cpp files

SRC_DIR = src
BIN_DIR = bin

CPP = $(wildcard src/*.cpp)
HPP = $(wildcard $(DIR)/*.hpp)

C_OBJ_FILES = $(patsubst $(SRC_DIR)/%.cpp,$(BIN_DIR)/%.o,$(CPP))
H_OBJ_FILES = $(patsubst $(SRC_DIR)/%.hpp,$(BIN_DIR)/%.o,$(HPP))

OBJ_FILES = $(C_OBJ_FILES) $(H_OBJ_FILES)
dev: clean compile

firsttime: makebin compile

makebin:
	mkdir bin

compile: $(OBJ_FILES)
	g++ -O3 -static -o main.exe $(OBJ_FILES)

clean:
	cmd /C del $(subst /,\,$(OBJ_FILES)) /F /Q
	cmd /C del main.exe /F /Q

$(BIN_DIR)/%.o: $(SRC_DIR)/%.cpp
	g++ -O3 -c $< -o $@

