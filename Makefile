SRC_DIR := src
SRC_FILES := $(shell find $(SRC_DIR) -name *.cpp)
LDFLAGS :=  -lSDL2 -lSDL2_image
CXXFLAGS := -Wall -Wextra -pedantic

DEBUGFLAGS := --debug
RELEASEFLAGS := -O3 -march=native -mtune=native

debug: $(SRC_FILES)
	clang++ $(CXXFLAGS) $(DEBUGFLAGS) $(LDFLAGS) -o $@ $^

release: $(SRC_FILES)
	clang++ $(CXXFLAGS) $(RELEASEFLAGS) $(LDFLAGS) -o $@ $^

clean:
	rm -rf release debug
