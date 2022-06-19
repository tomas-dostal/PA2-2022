
cmake_minimum_required(VERSION 3.21)
project(tspaint-test)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -pedantic -Wextra")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(tspaint-test main.cpp
        ../src/Application.cpp             ../src/Command.h                   ../src/Command.cpp                 ../src/FormatterParams.cpp         ../src/Tspaint.cpp
        ../src/Application.h               ../src/FormatterParams.h           ../src/Tspaint.h                   ../src/SysCommand.cpp              ../src/constants.h
        ../src/Circle.cpp                  ../src/CommandImpl.cpp             ../src/Helper.cpp                  ../src/Pos.cpp
        ../src/Circle.h                    ../src/CommandImpl.h               ../src/Helper.h                    ../src/Pos.h                       ../src/messages.h
        ../src/Color.cpp                   ../src/Interface.cpp               ../src/PolyLine.h                  ../src/SysCommand.h                ../src/ShapeGroup.cpp
        ../src/Color.h                     ../src/Interface.h                 ../src/PolyLine.cpp                ../src/SuperShape.cpp              ../src/SuperShape.h
        ../src/ColorPalette.cpp            ../src/Formatter.cpp               ../src/Line.cpp                    ../src/Shape.cpp                   ../src/Rectangle.cpp
        ../src/ColorPalette.h              ../src/Formatter.h                 ../src/Line.h                      ../src/Shape.h                     ../src/PolyLine.cpp
        ../src/Export.cpp ../src/Export.h     ../src/Ellipse.cpp                 ../src/Ellipse.h
        ../src/ExportSVG.cpp               ../src/ExportSVG.h                 ../src/ExportTspaint.cpp           ../src/ExportTspaint.h             ../src/ShapeGroup.h
        ../src/ProgtestErrors.cpp          ../src/ProgtestErrors.h            ../src/ExportBMP.cpp               ../src/ExportBMP.h                 ../src/Pixel.h)

