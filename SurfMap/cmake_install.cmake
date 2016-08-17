# Install script for directory: C:/Users/brianweis/code/IMPACT/SurfMap

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/brianweis/code/IMPACT/build")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
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

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/Dual_connectivity.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/KD_tree_3.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/Pane_boundary.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/Pane_communicator.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/Pane_connectivity.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/Pane_ghost_connectivity.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/Rocmap.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/Simple_manifold_2.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/mapbasic.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/Dual_connectivity.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/KD_tree_3.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/Pane_boundary.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/Pane_communicator.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/Pane_connectivity.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/Pane_ghost_connectivity.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/Rocmap.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/Simple_manifold_2.h"
    "C:/Users/brianweis/code/IMPACT/SurfMap/include/mapbasic.h"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/brianweis/code/IMPACT/lib/libSurfMap.dll.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/brianweis/code/IMPACT/lib/libSurfMap.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSurfMap.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSurfMap.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Qt/Tools/mingw492_32/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSurfMap.dll")
    endif()
  endif()
endif()

