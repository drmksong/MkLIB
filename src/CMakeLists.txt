CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)

# PROJECT(MkLib)
# SET(proj_name "CMake MkLib")
# SET(CMAKE_CXX_STANDARD 20)

SET( EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build )
# SET( LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/../MkLIB )
# SET( INCLUDE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/../MkInclude )
SET( STATIC_LIB ${CMAKE_PROJECT_NAME}_static )
SET( DYNAMIC_LIB ${CMAKE_PROJECT_NAME} )

# to use valgrind start
set(CMAKE_CXX_FLAGS_RELEASE  "${CMAKE_CXX_FLAGS_RELEASE} -g -ggdb3")
set(CMAKE_C_FLAGS_RELEASE  "${CMAKE_C_FLAGS_RELEASE} -g -ggdb3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -ggdb3")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -ggdb3")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -g -ggdb3")
set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -g -ggdb3")
# to use valgrind end

if(APPLE)
    file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
    file(GLOB GLLIB "/opt/homebrew/lib/libGLEW.dylib")
    file(GLOB GLUTLIB "/opt/homebrew/lib/libglfw.dylib")
elseif(UNIX)
    # linux
    file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)
    file(GLOB GLLIB "/usr/local/lib/libGLEW.so")
    file(GLOB GLUTLIB "/usr/local/lib/libglfw.so")
endif()

# set sources
SET (SRC_FILES 
        # glLib.cpp
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
# ADD_EXECUTABLE(${STATIC_LIB}_RUN ${SRC_FILES})
ADD_LIBRARY (${STATIC_LIB} ${SRC_FILES})
ADD_LIBRARY (${DYNAMIC_LIB} SHARED ${SRC_FILES})

# windows
# TARGET_LINK_LIBRARIES(${STATIC_LIB} glu32 freeglut)
# macOS
TARGET_LINK_LIBRARIES(${STATIC_LIB} ${GLLIB} ${GLUTLIB})
TARGET_LINK_LIBRARIES(${DYNAMIC_LIB} ${GLLIB} ${GLUTLIB})
# linux
# TARGET_LINK_LIBRARIES(${STATIC_LIB} GL glut)

# set_target_properties(MkLIB PROPERTIES PUBLIC_HEADER "${INC_FILES}")
# INSTALL(TARGETS MkLIB
#         LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/../MkLib
#         PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/../MkInclude
# )