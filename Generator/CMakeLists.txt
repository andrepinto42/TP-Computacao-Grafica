cmake_minimum_required(VERSION 3.21)
project(Generator)

set(CMAKE_CXX_STANDARD 14)

add_executable(Generator main.cpp main.h
        tinyxml/tinyxmlparser.cpp tinyxml/tinyxmlerror.cpp
        tinyxml/tinyxml.cpp tinyxml/tinyxml.h
        tinyxml/tinystr.cpp tinyxml/tinystr.h
        GenerateCube.cpp GenerateCube.h GenerateSphere.cpp GenerateSphere.h GenerateCone.cpp GenerateCone.h)