cmake_minimum_required (VERSION 3.8)

project ("Lost_Viking_1.1")

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)


set(SOURCES 
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Player.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Enemy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Bullet.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Game.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Player.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Enemy.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Source/Bullet.h
)

add_executable (Lost_Viking_1.1 ${SOURCES})

target_include_directories(Lost_Viking_1.1 PRIVATE ${SFML_INCLUDE_DIRS})
target_link_libraries(Lost_Viking_1.1 PRIVATE sfml-system sfml-network sfml-graphics sfml-window)

