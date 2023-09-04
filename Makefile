SRC_DIR := ./src
OBJ_DIR := ./obj
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
LDFLAGS :=  -L/usr/lib -lSDL2 -lSDL2_image
CPPFLAGS := -std=c++2b
CXXFLAGS := -Wall -Wextra -O2 -I/usr/include -static

game: $(OBJ_FILES)
	clang++ $(LDFLAGS) -o $@ $^

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	clang++ $(CPPFLAGS) $(CXXFLAGS) -c -o $@ $<
clean:
	rm -rf $(OBJ_DIR)/* game
