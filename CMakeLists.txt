CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)

SET(proj_name "MkLIB")
PROJECT(${proj_name})

SET(CMAKE_CXX_STANDARD 20)

# -DCMAKE_CXX_FLAGS=-pg -DCMAKE_EXE_LINKER_FLAGS=-pg
SET(CMAKE_CXX_FLAGS -pg)
SET(CMAKE_EXE_LINKER_FLAGS -pg)

SET( STATIC_LIB ${CMAKE_PROJECT_NAME}_static )
SET( DYNAMIC_LIB ${CMAKE_PROJECT_NAME} )

SET (INC_FILES
        src/MkAbstract.hpp
        src/MkArray.hpp 
        src/MkColor.hpp
        src/MkCircle.hpp
        src/MkCylinder.hpp
        src/MkCube.hpp
        src/MkLine.hpp 
        src/MkMatrix.hpp
        src/MkMisc.hpp 
        src/MkPlane.hpp
        src/MkPoint.hpp 
        src/MkPointData.hpp 
        src/MkPolygon.hpp
        src/MkRect.hpp
        src/MkShape.hpp
        src/MkSphere.hpp
        src/MkTriangle.hpp    

)

# set(dir ${CMAKE_CURRENT_SOURCE_DIR}/../Compile/)
# set(EXECUTABLE_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
# set(LIBRARY_OUTPUT_PATH ${dir} CACHE PATH "Build directory" FORCE)
# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${dir})
# set(CMAKE_BUILD_FILES_DIRECTORY ${dir})
# set(CMAKE_BUILD_DIRECTORY ${dir})
# set(CMAKE_BINARY_DIR  ${dir})
# SET(EXECUTABLE_OUTPUT_PATH ${dir})l
# SET(LIBRARY_OUTPUT_PATH ${dir}lib)
# SET(CMAKE_CACHEFILE_DIR ${dir})

# set(LIBRARY_OUTPUT_PATH lib CACHE PATH "Build directory" FORCE)

# for mac
INCLUDE_DIRECTORIES(src) 
INCLUDE_DIRECTORIES(/opt/homebrew/include)
# for windows/Users/myungkyusong/Documents/Develop/01_THMBEMSPH/01_MkLIB/src/MkMisc.hpp
# INCLUDE_DIRECTORIES(src)

ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(tests)

LINK_DIRECTORIES(/opt/homebrew/lib)

set_target_properties(${DYNAMIC_LIB} PROPERTIES PUBLIC_HEADER "${INC_FILES}")

INSTALL(TARGETS ${DYNAMIC_LIB}
        # LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/../MkLIB
        # PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/../MkInclude
        LIBRARY DESTINATION /usr/local/lib
        PUBLIC_HEADER DESTINATION /usr/local/include
)

INSTALL(TARGETS ${STATIC_LIB}
        # LIBRARY DESTINATION ${CMAKE_SOURCE_DIR}/../MkLIB
        # PUBLIC_HEADER DESTINATION ${CMAKE_SOURCE_DIR}/../MkInclude
        LIBRARY DESTINATION /usr/local/lib
        PUBLIC_HEADER DESTINATION /usr/local/include
)

# ADD_SUBDIRECTORY(googletest)

# SET (srcs MkArray.cpp MkColor.cpp MkMatrix.cpp MkMisc.cpp MkPoint.cpp MkPointData.cpp )

# ADD_DEFINITIONS(-DMKDEBUG)
# ADD_LIBRARY(MkLib ${srcs})
# ADD_EXECUTABLE(test test.cpp)



# PROJECT( ${proj_name} )

# C++ settings
