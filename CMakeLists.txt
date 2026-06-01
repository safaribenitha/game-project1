cmake_minimum_required(VERSION 3.16)
project(VampireSurvival LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(SFML  COMPONENTS Graphics Window System REQUIRED)

add_executable(VampireSurvival
    main.cpp
    src/Character.cpp
    src/DaggerPickup.cpp
    src/Game.cpp
    src/HealthPickup.cpp
    src/Pickup.cpp
    src/Tomb.cpp
    src/Tree.cpp
    src/Vampire.cpp
    src/Wolf.cpp
)

target_include_directories(VampireSurvival PRIVATE include)
target_link_libraries(VampireSurvival PRIVATE SFML::Graphics SFML::Window SFML::System)
