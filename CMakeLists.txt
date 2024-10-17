cmake_minimum_required(VERSION 3.5)
project(vectng)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Gather source and header files
file (GLOB_RECURSE VectNG_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file (GLOB_RECURSE VectNG_HEADERS CONFIGURE_DEPENDS "src/*.hpp")
file (GLOB_RECURSE VectNG_ASSETS CONFIGURE_DEPENDS "assets/*")

# Set include directories
set (VectNG_INCLUDE_DIRS "")
foreach (_headerFile ${VectNG_HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list (APPEND VectNG_INCLUDE_DIRS ${_dir})
endforeach()
list (REMOVE_DUPLICATES VectNG_INCLUDE_DIRS)

# Set release build flags
set(CMAKE_CXX_FLAGS_RELEASE_INIT "${CMAKE_CXX_FLAGS_RELEASE_INIT} - -Ofast -march=native -mtune=native -DNDEBUG")

# Add library dependencies
include(FindPkgConfig)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

foreach (_asset ${VectNG_ASSETS})
	file(RELATIVE_PATH _relative_path ${CMAKE_SOURCE_DIR} ${_asset})
	configure_file(${_asset} ${CMAKE_BINARY_DIR}/${_relative_path} COPYONLY)
endforeach()

# Create executable
add_executable(${PROJECT_NAME} ${VectNG_SOURCES})

# Include directories
include_directories(${VectNG_INCLUDE_DIRS} ${SDL2_INCLUDE_DIRS} ${SDL2IMAGE_INCLUDE_DIRS})

# Link libraries
target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES} ${SDL2IMAGE_LIBRARIES})
