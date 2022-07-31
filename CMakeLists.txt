cmake_minimum_required(VERSION 3.13.4)
project(chess-engine)

add_executable(${PROJECT_NAME} src/main.cpp)

find_package(SDL2 REQUIRED)

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${SDL2_INCLUDE_DIRS}
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${SDL2_LIBRARIES}
)

find_package(SDL2_image REQUIRED)