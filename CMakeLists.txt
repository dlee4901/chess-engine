cmake_minimum_required(VERSION 3.13.4)
project(chess-engine)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

add_executable(${PROJECT_NAME} src/main.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)
#set(CMAKE_CXX_STANDARD 17)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)

add_subdirectory(src)

target_include_directories(${PROJECT_NAME} 
    PRIVATE ${SDL2_INCLUDE_DIRS}
    PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS}
    PUBLIC src
)

target_link_directories(${PROJECT_NAME}
    PRIVATE src
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${SDL2_LIBRARIES}
    PRIVATE ${SDL2_IMAGE_LIBRARIES}
    entity
    grid
    movement
)