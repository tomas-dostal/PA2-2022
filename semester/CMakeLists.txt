cmake_minimum_required(VERSION 3.21)
project(ts_paint)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -pedantic -Wextra")

include_directories(src/)

add_executable(ts_paint
        src/main.cpp src/Circle.cpp  src/Circle.h  src/Color.cpp  src/Color.h  src/Command.cpp src/Command.h src/CommandParameters.cpp src/CommandParameters.h src/Interface.cpp src/Interface.h src/Line.cpp src/Line.h src/Polyline.cpp src/Polyline.h src/Pos.cpp src/Pos.h src/Rectangle.cpp src/Rectangle.h src/Shape.cpp src/Shape.h src/Tspaint.cpp src/Tspaint.h  src/ColorPalett.cpp  src/ColorPallet.h )
