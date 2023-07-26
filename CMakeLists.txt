CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)

SET(proj_name "MkLib")
PROJECT(${proj_name})

SET(CMAKE_CXX_STANDARD 20)

# -DCMAKE_CXX_FLAGS=-pg -DCMAKE_EXE_LINKER_FLAGS=-pg
SET(CMAKE_CXX_FLAGS -pg)
SET(CMAKE_EXE_LINKER_FLAGS -pg)

# for mac
#INCLUDE_DIRECTORIES(src, /opt/homebrew/Cellar/boost/1.82.0_1/include, /opt/homebrew/Cellar/glfw/3.3.8/include, /opt/homebrew/Cellar/glew/2.2.0_1/include)
INCLUDE_DIRECTORIES(src) 
INCLUDE_DIRECTORIES(/opt/homebrew/Cellar/boost/1.82.0_1/include)
INCLUDE_DIRECTORIES(/opt/homebrew/Cellar/mesa/22.3.6_1/include)
INCLUDE_DIRECTORIES(/opt/homebrew/Cellar/freeglut/3.4.0/include)
# for windows
# INCLUDE_DIRECTORIES(src)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)

LINK_DIRECTORIES(/opt/homebrew/Cellar/mesa/22.3.6_1/lib)
LINK_DIRECTORIES(/opt/homebrew/Cellar/freeglut/3.4.0/lib)

# ADD_SUBDIRECTORY(googletest)

# SET (srcs MkArray.cpp MkColor.cpp MkMatrix.cpp MkMisc.cpp MkPoint.cpp MkPointData.cpp )

# ADD_DEFINITIONS(-DMKDEBUG)
# ADD_LIBRARY(MkLib ${srcs})
# ADD_EXECUTABLE(test test.cpp)



# PROJECT( ${proj_name} )

# C++ settings
