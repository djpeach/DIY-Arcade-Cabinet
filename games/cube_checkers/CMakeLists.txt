cmake_minimum_required(VERSION 3.7)

project(cube_checkers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "~/lib/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

#we add the executable of the program
add_executable(cube_checkers
Button.cpp		StateMachine.hpp	State_MainMenu.cpp
Button.hpp		State_Base.cpp		State_MainMenu.hpp
Cube.cpp		State_Base.hpp		State_SplashScreen.cpp
Cube.hpp		State_Game.cpp		State_SplashScreen.hpp
Game.cpp		State_Game.hpp		Tile.cpp
Game.hpp		State_Instructions.cpp	Tile.hpp
StateMachine.cpp	State_Instructions.hpp	main.cpp
)

target_link_libraries(cube_checkers sfml-system sfml-window sfml-graphics sfml-audio sfml-network sqlite3)
