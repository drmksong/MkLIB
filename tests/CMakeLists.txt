CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)

# PROJECT(MkLib Tester)
# SET(proj_name "CMake MkLib Tester")
# SET(CMAKE_CXX_STANDARD 20)

# ADD_SUBDIRECTORY(src)
# ADD_SUBDIRECTORY(tests)
# # ADD_SUBDIRECTORY(extern/googletest)

# SET (srcs test.cpp )

# ADD_EXECUTABLE(test ${srcs})
# TARGET_LINK_LIBRARIES(test ../build/MkLib glu32 freeglut)

if(APPLE)
    INCLUDE_DIRECTORIES(/opt/homebrew/include)
    LINK_DIRECTORIES(/opt/homebrew/lib)

    FILE(GLOB GLLIB "/opt/homebrew/lib/libGL.1.dylib")
    FILE(GLOB GLEWLIB "/opt/homebrew/lib/libGLEW.2.2.dylib")
    FILE(GLOB GLUTLIB "/opt/homebrew/lib/libglfw.3.dylib")
elseif(UNIX)
    INCLUDE_DIRECTORIES(/usr/local/include)
    LINK_DIRECTORIES(/usr/local/lib)

    FILE(GLOB GLLIB "/usr/local/lib/libGL.so")
    FILE(GLOB GLEWLIB "/usr/local/lib/libGLEW.so")
    FILE(GLOB GLUTLIB "/usr/local/lib/libglfw.so")
endif()

SET(TESTER ${CMAKE_PROJECT_NAME}_test)
SET(DYNAMIC_LIB ${CMAKE_PROJECT_NAME} )
SET(STATIC_LIB ${CMAKE_PROJECT_NAME}_static )
# SET(TESTER test)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/build )

# file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
# SET(SOURCES ${TEST_SOURCES})
SET(TEST_SOURCES test.cpp)
# SET(TEST_SOURCES test.cpp ../src/glLib.cpp ../src/Shader.cpp)

add_executable(${TESTER} ${TEST_SOURCES})
add_test(NAME ${TESTER} COMMAND ${TESTER})
# target_link_libraries(${TESTER} PUBLIC ${CMAKE_PROJECT_NAME} )
# target_link_libraries(${TESTER} PUBLIC ${DYNAMIC_LIB} ${GLLIB} ${GLEWLIB} ${GLUTLIB} )
target_link_libraries(${TESTER} PUBLIC ${GLLIB} ${GLEWLIB} ${GLUTLIB} )