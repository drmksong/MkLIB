# Install script for directory: /home/mksong/work/MkLIB

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/usr/bin/objdump")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mksong/work/MkLIB/cmake-build-debug/src/cmake_install.cmake")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for the subdirectory.
  include("/home/mksong/work/MkLIB/cmake-build-debug/tests/cmake_install.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libMkLIB.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libMkLIB.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}/usr/local/lib/libMkLIB.so"
         RPATH "")
  endif()
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/lib/libMkLIB.so")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/lib" TYPE SHARED_LIBRARY FILES "/home/mksong/work/MkLIB/cmake-build-debug/src/libMkLIB.so")
  if(EXISTS "$ENV{DESTDIR}/usr/local/lib/libMkLIB.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}/usr/local/lib/libMkLIB.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}/usr/local/lib/libMkLIB.so")
    endif()
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  list(APPEND CMAKE_ABSOLUTE_DESTINATION_FILES
   "/usr/local/include/MkAbstract.hpp;/usr/local/include/MkArray.hpp;/usr/local/include/MkColor.hpp;/usr/local/include/MkCircle.hpp;/usr/local/include/MkCylinder.hpp;/usr/local/include/MkCube.hpp;/usr/local/include/MkLine.hpp;/usr/local/include/MkMatrix.hpp;/usr/local/include/MkMisc.hpp;/usr/local/include/MkPlane.hpp;/usr/local/include/MkPoint.hpp;/usr/local/include/MkPointData.hpp;/usr/local/include/MkPolygon.hpp;/usr/local/include/MkRect.hpp;/usr/local/include/MkShape.hpp;/usr/local/include/MkSphere.hpp;/usr/local/include/MkTriangle.hpp")
  if(CMAKE_WARN_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(WARNING "ABSOLUTE path INSTALL DESTINATION : ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  if(CMAKE_ERROR_ON_ABSOLUTE_INSTALL_DESTINATION)
    message(FATAL_ERROR "ABSOLUTE path INSTALL DESTINATION forbidden (by caller): ${CMAKE_ABSOLUTE_DESTINATION_FILES}")
  endif()
  file(INSTALL DESTINATION "/usr/local/include" TYPE FILE FILES
    "/home/mksong/work/MkLIB/src/MkAbstract.hpp"
    "/home/mksong/work/MkLIB/src/MkArray.hpp"
    "/home/mksong/work/MkLIB/src/MkColor.hpp"
    "/home/mksong/work/MkLIB/src/MkCircle.hpp"
    "/home/mksong/work/MkLIB/src/MkCylinder.hpp"
    "/home/mksong/work/MkLIB/src/MkCube.hpp"
    "/home/mksong/work/MkLIB/src/MkLine.hpp"
    "/home/mksong/work/MkLIB/src/MkMatrix.hpp"
    "/home/mksong/work/MkLIB/src/MkMisc.hpp"
    "/home/mksong/work/MkLIB/src/MkPlane.hpp"
    "/home/mksong/work/MkLIB/src/MkPoint.hpp"
    "/home/mksong/work/MkLIB/src/MkPointData.hpp"
    "/home/mksong/work/MkLIB/src/MkPolygon.hpp"
    "/home/mksong/work/MkLIB/src/MkRect.hpp"
    "/home/mksong/work/MkLIB/src/MkShape.hpp"
    "/home/mksong/work/MkLIB/src/MkSphere.hpp"
    "/home/mksong/work/MkLIB/src/MkTriangle.hpp"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/mksong/work/MkLIB/cmake-build-debug/src/libMkLIB_static.a")
endif()

if(CMAKE_INSTALL_COMPONENT)
  if(CMAKE_INSTALL_COMPONENT MATCHES "^[a-zA-Z0-9_.+-]+$")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
  else()
    string(MD5 CMAKE_INST_COMP_HASH "${CMAKE_INSTALL_COMPONENT}")
    set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INST_COMP_HASH}.txt")
    unset(CMAKE_INST_COMP_HASH)
  endif()
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
  file(WRITE "/home/mksong/work/MkLIB/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
endif()
