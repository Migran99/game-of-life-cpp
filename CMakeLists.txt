cmake_minimum_required(VERSION 3.0) 
project(game_of_life)               
set(CMAKE_CXX_STANDARD 17)            

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# Add main.cpp file of project root directory as source file
set(files src/main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(run ${files})
target_link_libraries(run Eigen3::Eigen)