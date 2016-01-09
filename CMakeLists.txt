cmake_minimum_required(VERSION 3.3)
project(SimpleHexRiskGame)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -std=c99 -I/usr/local/include/SDL2 -D_THREAD_SAFE")
set(CMAKE_EXE_LINKER_FLAGS "-L/usr/local/lib -lSDL2 -lSDL2_gfx -lSDL2_ttf")

set(SOURCE_FILES
    src/board.c
    src/board.h
    src/defs.h
    src/graphic.c
    src/graphic.h
    src/input.c
    src/input.h
    src/main.c
    src/main.h
    src/player.c
    src/player.h
    src/utility.c
    src/utility.h src/game.c src/game.h src/battle.c src/battle.h)

add_executable(SimpleHexRiskGame ${SOURCE_FILES})