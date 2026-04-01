cmake_minimum_required(VERSION 3.10)
project(vectng LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Gather source and header files
file(GLOB_RECURSE VectNG_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
file(GLOB_RECURSE VectNG_HEADERS CONFIGURE_DEPENDS "src/*.hpp")
file(GLOB_RECURSE VectNG_ASSETS CONFIGURE_DEPENDS "assets/*")

# Set include directories from header locations
set(VectNG_INCLUDE_DIRS "")
foreach(_headerFile ${VectNG_HEADERS})
	get_filename_component(_dir ${_headerFile} PATH)
	list(APPEND VectNG_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES VectNG_INCLUDE_DIRS)

# Set release build flags
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -Ofast -march=native -mtune=native -DNDEBUG")

# Find dependencies
find_package(PkgConfig REQUIRED)
find_package(SDL2 REQUIRED)
pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)

# Copy assets to build directory
foreach(_asset ${VectNG_ASSETS})
	file(RELATIVE_PATH _relative_path ${CMAKE_SOURCE_DIR} ${_asset})
	configure_file(${_asset} ${CMAKE_BINARY_DIR}/${_relative_path} COPYONLY)
endforeach()

# Create executable
add_executable(${PROJECT_NAME} ${VectNG_SOURCES})

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
	${VectNG_INCLUDE_DIRS}
	${SDL2_INCLUDE_DIRS}
	${SDL2_IMAGE_INCLUDE_DIRS}
)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE
	${SDL2_LIBRARIES}
	${SDL2_IMAGE_LIBRARIES}
)
