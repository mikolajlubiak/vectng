SRC_DIR := src
OBJ_DIR := obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS :=  -lSDL2 -lSDL2_image
CXXFLAGS := -Wall -Wextra -pedantic -O3 -march=native -mtune=native

game: $(OBJ_FILES)
	clang++ $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	clang++ $(CXXFLAGS) -c -o $@ $<
clean:
	rm -rf $(OBJ_DIR)/* game
