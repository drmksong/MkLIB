CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)

# PROJECT(MkLib)
# SET(proj_name "CMake MkLib")
# SET(CMAKE_CXX_STANDARD 20)

SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build )
SET( LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/../MkLIB )
SET( BINARY ${CMAKE_PROJECT_NAME} )

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
file(GLOB GLLIB "/opt/homebrew/lib/libGL.dylib")
file(GLOB GLUTLIB "/opt/homebrew/lib/libglut.dylib")

# set sources
SET (SRC_FILES 
        glLib.cpp
        MkArray.cpp 
        MkColor.cpp
        MkCircle.cpp
        MkCylinder.cpp
        MkCube.cpp
        MkLine.cpp 
        MkMatrix.cpp
        MkMisc.cpp 
        MkPlane.cpp
        MkPoint.cpp 
        MkPointData.cpp 
        MkPolygon.cpp
        MkRect.cpp
        MkShape.cpp
        MkSphere.cpp
        MkTriangle.cpp    
    )

SET (INC_FILES
        MkArray.hpp 
        MkColor.hpp
        MkCircle.hpp
        MkCylinder.hpp
        MkCube.hpp
        MkLine.hpp 
        MkMatrix.hpp
        MkMisc.hpp 
        MkPlane.hpp
        MkPoint.hpp 
        MkPointData.hpp 
        MkPolygon.hpp
        MkRect.hpp
        MkShape.hpp
        MkSphere.hpp
        MkTriangle.hpp    

)

# SET(SRC_FILES ${SCOURCES}) 

ADD_DEFINITIONS(-DMKDEBUG)

#build
# ADD_EXECUTABLE(${BINARY}_RUN ${SRC_FILES})
ADD_LIBRARY (${BINARY} ${SRC_FILES})

# windows
# TARGET_LINK_LIBRARIES(${BINARY} glu32 freeglut)
# macOS
  TARGET_LINK_LIBRARIES(${BINARY} ${GLLIB} ${GLUTLIB})
# linux
# TARGET_LINK_LIBRARIES(${BINARY} GL glut)

# set_target_properties(MkLIB PROPERTIES PUBLIC_HEADER "${INC_FILES}")
# INSTALL(TARGETS MkLIB
#         LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/../MkLib
#         PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/../MkInclude
# )