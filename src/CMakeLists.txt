add_library(entity entity.cpp entity.hpp)
add_library(grid grid.cpp grid.hpp)
add_library(movement movement.cpp movement.hpp)
add_library(graphics graphics.cpp graphics.hpp)
add_library(util util.cpp util.hpp)

target_include_directories(entity
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${sdl_include}
)
target_include_directories(grid 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${sdl_include}
)
target_include_directories(movement
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${sdl_include}
)
target_include_directories(graphics 
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${sdl_include}
)
target_include_directories(util
    INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}
    PUBLIC ${sdl_include}
)

target_link_libraries(entity PUBLIC ${sdl_libs} compiler_flags)
target_link_libraries(grid PUBLIC ${sdl_libs} compiler_flags)
target_link_libraries(movement PUBLIC ${sdl_libs} compiler_flags)
target_link_libraries(graphics PUBLIC ${sdl_libs} compiler_flags)
target_link_libraries(util PUBLIC ${sdl_libs} compiler_flags)