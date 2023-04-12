# CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)

# PROJECT(MkLib Tester)
# SET(proj_name "CMake MkLib Tester")
# SET(CMAKE_CXX_STANDARD 20)

# ADD_SUBDIRECTORY(src)
# ADD_SUBDIRECTORY(tests)
# # ADD_SUBDIRECTORY(extern/googletest)

# SET (srcs test.cpp )

# ADD_EXECUTABLE(test ${srcs})
# TARGET_LINK_LIBRARIES(test ../build/MkLib glu32 freeglut)

link_libraries(glfw)

set(GLFW_SOURCE_DIR "../../glfw")
include_directories("${GLFW_SOURCE_DIR}/deps")


if (MATH_LIBRARY)
    link_libraries("${MATH_LIBRARY}")
endif()


set(GLAD_GL "${GLFW_SOURCE_DIR}/deps/glad/gl.h")
set(GLAD_GLES2 "${GLFW_SOURCE_DIR}/deps/glad/gles2.h")
set(GETOPT "${GLFW_SOURCE_DIR}/deps/getopt.h"
           "${GLFW_SOURCE_DIR}/deps/getopt.c")
set(TINYCTHREAD "${GLFW_SOURCE_DIR}/deps/tinycthread.h"
                "${GLFW_SOURCE_DIR}/deps/tinycthread.c")

SET(BINARY ${CMAKE_PROJECT_NAME}_test)
# SET(BINARY test)

SET(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR} )

# file(GLOB_RECURSE TEST_SOURCES LIST_DIRECTORIES false *.h *.cpp)
# SET(SOURCES ${TEST_SOURCES})
SET(TEST_SOURCES test gltest )

add_executable(${BINARY} ${TEST_SOURCES} ${GLAD_GL})
add_test(NAME ${BINARY} COMMAND ${BINARY})
target_link_libraries(${BINARY} PUBLIC ${CMAKE_PROJECT_NAME})




# add_executable(boing WIN32 MACOSX_BUNDLE boing.c ${ICON} ${GLAD_GL})
# add_executable(gears WIN32 MACOSX_BUNDLE gears.c ${ICON} ${GLAD_GL})
# add_executable(heightmap WIN32 MACOSX_BUNDLE heightmap.c ${ICON} ${GLAD_GL})
# add_executable(offscreen offscreen.c ${ICON} ${GLAD_GL})
# add_executable(particles WIN32 MACOSX_BUNDLE particles.c ${ICON} ${TINYCTHREAD} ${GETOPT} ${GLAD_GL})
# add_executable(sharing WIN32 MACOSX_BUNDLE sharing.c ${ICON} ${GLAD_GL})
# add_executable(splitview WIN32 MACOSX_BUNDLE splitview.c ${ICON} ${GLAD_GL})
# add_executable(triangle-opengl WIN32 MACOSX_BUNDLE triangle-opengl.c ${ICON} ${GLAD_GL})
# add_executable(triangle-opengles WIN32 MACOSX_BUNDLE triangle-opengles.c ${ICON} ${GLAD_GLES2})
# add_executable(wave WIN32 MACOSX_BUNDLE wave.c ${ICON} ${GLAD_GL})
# add_executable(windows WIN32 MACOSX_BUNDLE windows.c ${ICON} ${GLAD_GL})

# target_link_libraries(particles Threads::Threads)
if (RT_LIBRARY)
    target_link_libraries(particles "${RT_LIBRARY}")
endif()

set(GUI_ONLY_BINARIES boing gears heightmap particles sharing splitview
    triangle-opengl triangle-opengles wave windows)
set(CONSOLE_BINARIES offscreen)

# set_target_properties(${GUI_ONLY_BINARIES} ${CONSOLE_BINARIES} PROPERTIES
#                       C_STANDARD 99
#                       FOLDER "GLFW3/Examples")


