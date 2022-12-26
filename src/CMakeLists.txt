###
find_package(SDL2 REQUIRED)
set(sdl2_include ${SDL2_INCLUDE_DIRS})
set(sdl2_libraries ${SDL2_LIBRARIES})

find_package(SDL2_image REQUIRED)
set(sdl2_image_include ${SDL2_IMAGE_INCLUDE_DIRS})
set(sdl2_image_libraries ${SDL2_IMAGE_LIBRARIES})

list(APPEND LIBS2 ${sdl2_libraries} ${sdl2_image_libraries})
###

add_library(entity entity.cpp entity.hpp)
add_library(grid grid.cpp grid.hpp)
add_library(movement movement.cpp movement.hpp)
add_library(graphics graphics.cpp graphics.hpp)

target_include_directories(entity INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(grid INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(movement INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(graphics 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${sdl2_include}
    PUBLIC ${sdl2_image_include}
)

target_link_libraries(entity compiler_flags)
target_link_libraries(grid compiler_flags)
target_link_libraries(movement compiler_flags)
target_link_libraries(graphics PUBLIC ${LIBS2} compiler_flags) 