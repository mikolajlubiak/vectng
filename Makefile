# Where the source code is located.
SRC_DIR := src
# Include all the .cpp files from SRC_DIR directory.
SRC_FILES := $(shell find $(SRC_DIR) -name *.cpp)
# Link needed SDL2 libraries.
LDFLAGS :=  -lSDL2 -lSDL2_image
# Print every warning, be pedantic, optimize code on the 3rd level, use processor native compilation optimizations.
CXXFLAGS := -Wall -Wextra -pedantic -O3 -march=native -mtune=native

# Compile the game
game: $(SRC_FILES)
	clang++ $(CXXFLAGS) $(LDFLAGS) -o $@ $^

# Remove object files and game executable, sometimes make thinks you have chaned nothing and doesnt compile your changed, then you need to clean the object files.
clean:
	rm -rf game
