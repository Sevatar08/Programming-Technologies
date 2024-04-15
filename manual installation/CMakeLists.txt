cmake_minimum_required (VERSION 3.8)

project ("Lost_Viking_1.1")

set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH C:/SFML/SFML-2.6.1)

set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.6.1 COMPONENTS graphics window system)
cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH MY_PARENT_DIR)

set(SOURCES 
    ${MY_PARENT_DIR}/Source/main.cpp
    ${MY_PARENT_DIR}/Source/Game.cpp
    ${MY_PARENT_DIR}/Source/Player.cpp
    ${MY_PARENT_DIR}/Source/Enemy.cpp
    ${MY_PARENT_DIR}/Source/Bullet.cpp
    ${MY_PARENT_DIR}/Source/Game.h
    ${MY_PARENT_DIR}/Source/Player.h
    ${MY_PARENT_DIR}/Source/Enemy.h
    ${MY_PARENT_DIR}/Source/Bullet.h
)

add_executable (Lost_Viking_1.1 ${SOURCES})

target_link_libraries(Lost_Viking_1.1 sfml-graphics sfml-window sfml-system)
include_directories(Lost_Viking_1.1 ${CMAKE_PREFIX_PATH}/include)



