
cmake_minimum_required(VERSION 3.21)
project(semester)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "-Wall -pedantic -Wextra")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(tspaint
        src/Application.cpp             src/Command.h                   src/Command.cpp                 src/FormatterParams.cpp         src/Tspaint.cpp
        src/Application.h               src/FormatterParams.h                    src/Tspaint.h
        src/Circle.cpp                  src/CommandImpl.cpp             src/Helper.cpp                  src/Pos.cpp                     src/main.cpp
        src/Circle.h                    src/CommandImpl.h               src/Helper.h                    src/Pos.h                       src/messages.h
        src/Color.cpp                   src/Interface.cpp               src/PolyLine.h
        src/Color.h                     src/Interface.h                 src/PolyLine.cpp
        src/ColorPalette.cpp            src/Formatter.cpp               src/Line.cpp                    src/Shape.cpp
        src/ColorPalette.h              src/Formatter.h                 src/Line.h                      src/Shape.h
    src/Export.cpp src/Export.h     src/Ellipse.cpp                     src/Ellipse.h
        src/ExportSVG.cpp               src/ExportSVG.h                 src/ExportTspaint.cpp           src/ExportTspaint.h
        src/ProgtestErrors.cpp          src/ProgtestErrors.h            src/constants.h src/SysCommand.cpp src/SysCommand.h src/ShapeGroup.cpp src/ShapeGroup.h src/SuperShape.cpp src/SuperShape.h src/Rectangle.cpp src/PolyLine.cpp)

