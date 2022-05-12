set( CMAKE_EXPORT_COMPILE_COMMANDS ON )

cmake_minimum_required(VERSION 3.5)

project(A-star-Pathfinding VERSION 1.0.2) # Set variable PROJECT_NAME


if (WIN32)
	link_directories(${CMAKE_SOURCE_DIR}/Dependencies/SDL_FULL/x86/) # Call before to make sure VS detects it
endif()


if(UNIX)
	find_package(SDL2 REQUIRED)
endif()

add_executable(output) # Create a executable from main.cpp

if (WIN32)
	target_include_directories(output PUBLIC ./Dependencies/SDL_FULL/include)
endif()

if(UNIX)
	target_include_directories(output PUBLIC ${SDL2_INCLUDE_DIRS})
endif()

target_sources(output 
		PUBLIC 
		src/Knobs/Button.cpp
		src/main.cpp
		src/Grid/Grid.cpp
		src/Game.cpp
		src/Pathfinder/Pathfinder.cpp
		src/Setup.cpp
		src/Tools/Font.cpp
		src/Tools/TM.cpp
		src/Tools/InputSystem.cpp
		src/Tools/Timer.cpp
		src/Tools/Rect.cpp
		src/Tools/FRect.cpp
		)

add_subdirectory(Dependencies/hopscotch-map)
target_link_libraries(output 
		SDL2main
		SDL2_image
		SDL2
		SDL2_ttf
		tsl::hopscotch_map
		)
