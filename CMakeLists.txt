cmake_minimum_required(VERSION 3.0) 
project(simple_example)               
set(CMAKE_CXX_STANDARD 17)            

find_package (Eigen3 3.3 REQUIRED NO_MODULE)

# Add main.cpp file of project root directory as source file
set(files src/main.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(simple_example ${files})
target_link_libraries(simple_example Eigen3::Eigen)