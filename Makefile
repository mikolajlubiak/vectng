# Where the source code is located.
SRC_DIR := src
# Where the object files (not yet linked) are located.
OBJ_DIR := obj
# Include all the .cpp files from SRC_DIR directory.
SRC_FILES := $(wildcard $(SRC_DIR)/*.cpp)
# Include all the object files from OBJ_DIR directory.
OBJ_FILES := $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SRC_FILES))
# Link needed SDL2 libraries.
LDFLAGS :=  -lSDL2 -lSDL2_image
# Print every warning, be pedantic, optimize code on the 3rd level, use processor native compilation optimizations.
CXXFLAGS := -Wall -Wextra -pedantic -O3 -march=native -mtune=native

# Compile the source code to object files.
game: $(OBJ_FILES)
	clang++ $(LDFLAGS) -o $@ $^

# Link the object files to executable.
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	clang++ $(CXXFLAGS) -c -o $@ $<

# Remove object files and game executable, sometimes make thinks you have chaned nothing and doesnt compile your changed, then you need to clean the object files.
clean:
	rm -rf $(OBJ_DIR)/* game
