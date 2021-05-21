set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

cmake_minimum_required(VERSION 3.5)

project(Guys VERSION 1.0) # Set variable PROJECT_NAME

add_executable(output) # Create a executable from main.cpp

target_include_directories(output 
		PUBLIC 
		./
		./Dependencies/SDL_FULL/include/
		./Dependencies/hopscotch-map/include/
		./Src
		)

link_directories(output
		PUBLIC
		./Dependencies/SDL_FULL/x86/
		)

target_sources(output 
		PUBLIC 
		Src/Knobs/Button.cpp
		Src/main.cpp
		Src/Grid/Grid.cpp
		Src/Game.cpp
		Src/Pathfinder/Pathfinder.cpp
		Src/Setup.cpp
		Src/Tools/Font.cpp
		Src/Tools/TM.cpp
		Src/Tools/InputSystem.cpp
		Src/Tools/Timer.cpp
		Src/Tools/Rect.cpp
		Src/Tools/FRect.cpp
		
		)

target_link_libraries(output 
		SDL2main
		SDL2_image
		SDL2
		SDL2_ttf
		)
