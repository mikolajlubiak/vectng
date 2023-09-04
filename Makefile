SRC_DIR := ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS :=  -L/usr/lib -lSDL2 -lSDL2_image
CPPFLAGS := -std=c++20
CXXFLAGS := -Wall -Wextra -pedantic -O3 -static -march=native -mtune=native -I/usr/include

game: $(OBJ_FILES)
	clang++ $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	clang++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
clean:
	rm -rf $(OBJ_DIR)/* game
