cmake_minimum_required(VERSION 3.7)

project(cube_checkers LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SFML_DIR "~/lib/SFML")

find_package(SFML 2.5.1 COMPONENTS system window graphics audio network REQUIRED)

#we add the executable of the program
add_executable(cube_checkers
Button.cpp		StateMachine.cpp	State_MainMenu.cpp
Button.hpp		StateMachine.hpp	State_MainMenu.hpp
Cube.cpp		State_Base.cpp		State_SplashScreen.cpp
Cube.hpp		State_Base.hpp		State_SplashScreen.hpp
Game.cpp		State_Game.cpp		Tile.cpp
Game.hpp		State_Game.hpp		Tile.hpp
Player.cpp		State_Instructions.cpp	main.cpp
Player.hpp		State_Instructions.hpp
)

target_link_libraries(cube_checkers sfml-system sfml-window sfml-graphics sfml-audio sfml-network sqlite3)
