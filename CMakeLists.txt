cmake_minimum_required(VERSION 3.14)
project(snake)

SET(CMAKE_EXPORT_COMPILE_COMMANDS 1)
SET(CMAKE_CXX_COMPILER "g++")
SET(CMAKE_CXX_STANDARD_INCLUDE_DIRECTORIES  ${CMAKE_CXX_IMPLICIT_INCLUDE_DIRECTORIES})
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -O0")

# to jest OK, można zmienić na 17 ale na podstawach programowania nie ma to znaczenia
set(CMAKE_CXX_STANDARD 14)

# tego brakuje !! To są opcje, których ja sam używam w moich programach
# te opcje muszą być ZAWSZE włączone
add_compile_options(-Wall -Wextra)

# chcemy, by nasz kod był w pełni zgodny ze standardem
add_compile_options(-pedantic)

# zmieniamy niektóre ostrzeżenia na błędy
# missing return in non-void function: “control reaches end of non-void function"
add_compile_options(-Werror=return-type)

# misleading parentheses - read here: https://www.ibm.com/docs/en/ztpf/1.1.0.14?topic=warnings-parentheses
add_compile_options(-Werror=parentheses)

# VLA is a non-standard feature of some c++ compilers - this prevents its usage
add_compile_options(-Werror=vla)

# detect some trivial array-bounds errors in code (only compile-time !!)
add_compile_options(-Werror=array-bounds)

# additional warnings
add_compile_options ( -Wcast-qual )
add_compile_options ( -Wmaybe-uninitialized )


file(GLOB SRC CONFIGURE_DEPENDS src/*.cpp)
add_executable(snake ${SRC})

include_directories(/usr/local/include)


find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(snake sfml-system sfml-window sfml-graphics sfml-audio sfml-network)

add_custom_target(
        copy-compile-commands ALL
        ${CMAKE_COMMAND} -E copy_if_different
        ${CMAKE_CURRENT_LIST_DIR}
)

#przenoszenie folderów i plików do binarki CMakeList.txt
file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/snake_pictures/
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/scores.txt
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(COPY ${CMAKE_CURRENT_SOURCE_DIR}/SQUARE.ttf
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})