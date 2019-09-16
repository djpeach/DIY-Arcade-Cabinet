cmake_minimum_required(VERSION 3.7)

project(menu LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "~/lib/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

#we add the executable of the program
add_executable(menu
main.cpp SharedContext.hpp
DIYACMenu.hpp DIYACMenu.cpp
EventManager.hpp EventManager.cpp
Window.hpp Window.cpp
StateMachine.hpp StateMachine.cpp
State_Base.hpp
State_DIYACMenu.hpp State_DIYACMenu.cpp
State_Instructions.hpp State_Instructions.cpp
State_Alert.hpp State_Alert.cpp
)

target_link_libraries(menu sfml-system sfml-window sfml-graphics sfml-audio sfml-network )
