cmake_minimum_required(VERSION 3.15)
project(chess-engine VERSION 1.0)
if(APPLE)
    enable_language(OBJC)
endif()

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_17)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(compiler_flags INTERFACE
	"$<${gcc_like_cxx}:$<BUILD_INTERFACE:-Wall;-Wextra;-Wshadow;-Wformat=2;-Wunused>>"
	"$<${msvc_cxx}:$<BUILD_INTERFACE:-W3>>"
)
#configure_file(config.h.in config.h)

find_package(SDL2 REQUIRED)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
find_package(SDL2_image REQUIRED)
set(sdl_include ${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS})
set(sdl_libs ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

add_subdirectory(src)
list(APPEND LIBS entity graphics grid movement util ${sdl_libs})
add_executable(chess-engine src/main.cpp)

target_link_libraries(chess-engine 
    PUBLIC ${LIBS} compiler_flags
)

target_include_directories(chess-engine
    PUBLIC "${PROJECT_BINARY_DIR}"
    PUBLIC ${sdl_include}
)