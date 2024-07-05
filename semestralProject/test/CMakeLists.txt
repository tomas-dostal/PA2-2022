
cmake_minimum_required(VERSION 3.21)
project(tspaint-test)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -pedantic -Wextra")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(tspaint-test main.cpp
        ../src/Application.h ../src/CommandImpl.h ../src/ExportTspaint.h ../src/Line.h ../src/Rectangle.h ../src/SysCommand.h
        ../src/Circle.h ../src/Ellipse.h ../src/Formatter.h ../src/Pixel.h ../src/Shape.h ../src/Tspaint.h
        ../src/Color.h ../src/Export.h ../src/FormatterParams.h ../src/PolyLine.h ../src/ShapeGroup.h ../src/constants.h
        ../src/ColorPalette.h ../src/ExportBMP.h ../src/Helper.h ../src/Pos.h ../src/Star.h ../src/messages.h
        ../src/Command.h ../src/ExportSVG.h ../src/Interface.h ../src/ProgtestErrors.h ../src/SuperShape.h
        ../src/Application.cpp ../src/CommandImpl.cpp ../src/ExportTspaint.cpp ../src/Line.cpp ../src/Shape.cpp ../src/Tspaint.cpp
        ../src/Circle.cpp ../src/Ellipse.cpp ../src/Formatter.cpp ../src/PolyLine.cpp ../src/ShapeGroup.cpp
        ../src/Color.cpp ../src/Export.cpp ../src/FormatterParams.cpp ../src/Pos.cpp ../src/Star.cpp
        ../src/ColorPalette.cpp ../src/ExportBMP.cpp ../src/Helper.cpp ../src/ProgtestErrors.cpp ../src/SuperShape.cpp
        ../src/Command.cpp ../src/ExportSVG.cpp ../src/Interface.cpp ../src/Rectangle.cpp ../src/SysCommand.cpp)
