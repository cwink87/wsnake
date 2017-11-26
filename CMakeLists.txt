cmake_minimum_required(VERSION 3.4)
project(wsnake)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

find_package(SDL2 REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(${PROJECT_NAME} "main.cpp" "display.hpp" "display.cpp" "system.hpp" "system.cpp" "input.hpp" "input.cpp" "grid.hpp" "grid.cpp" "food.hpp" "food.cpp" "timestep.hpp" "timestep.cpp" "snake.hpp" "snake.cpp" "font.hpp" "font.cpp")

target_include_directories(${PROJECT_NAME} PUBLIC ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PUBLIC ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARIES})
