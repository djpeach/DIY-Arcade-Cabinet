cmake_minimum_required(VERSION 3.7)

project(cube_checkers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "~/lib/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

#we add the executable of the program
add_executable(cube_checkers
Button.cpp              Game.hpp                State_Base.cpp          State_MainMenu.hpp      main.cpp
Button.hpp              StateMachine.cpp        State_Base.hpp          State_SplashScreen.cpp
Game.cpp                StateMachine.hpp        State_MainMenu.cpp      State_SplashScreen.hpp
)

target_link_libraries(cube_checkers sfml-system sfml-window sfml-graphics sfml-audio sfml-network sqlite3)
