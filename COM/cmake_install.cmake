# Install script for directory: C:/Users/brianweis/code/IMPACT/COM

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
    "C:/Users/brianweis/code/IMPACT/COM/include/com.h"
    "C:/Users/brianweis/code/IMPACT/COM/include/com_assertion.h"
    "C:/Users/brianweis/code/IMPACT/COM/include/com_basic.h"
    "C:/Users/brianweis/code/IMPACT/COM/include/com_c.h"
    "C:/Users/brianweis/code/IMPACT/COM/include/comf90.h"
    "C:/Users/brianweis/code/IMPACT/COM/include/commpi.h"
    "C:/Users/brianweis/code/IMPACT/COM/include/mapptr.h"
    "C:/Users/brianweis/code/IMPACT/COM/include/com.h"
    "C:/Users/brianweis/code/IMPACT/COM/include/com_assertion.h"
    "C:/Users/brianweis/code/IMPACT/COM/include/com_basic.h"
    "C:/Users/brianweis/code/IMPACT/COM/include/com_c.h"
    "C:/Users/brianweis/code/IMPACT/COM/include/comf90.h"
    "C:/Users/brianweis/code/IMPACT/COM/include/commpi.h"
    "C:/Users/brianweis/code/IMPACT/COM/include/mapptr.h"
    "C:/Users/brianweis/code/IMPACT/COM/include/COM_base.hpp"
    "C:/Users/brianweis/code/IMPACT/COM/include/ComponentInterface.hpp"
    "C:/Users/brianweis/code/IMPACT/COM/include/Connectivity.hpp"
    "C:/Users/brianweis/code/IMPACT/COM/include/DataItem.hpp"
    "C:/Users/brianweis/code/IMPACT/COM/include/Element_accessors.hpp"
    "C:/Users/brianweis/code/IMPACT/COM/include/Function.hpp"
    "C:/Users/brianweis/code/IMPACT/COM/include/Pane.hpp"
    "C:/Users/brianweis/code/IMPACT/COM/include/Pane_node_accessors.hpp"
    "C:/Users/brianweis/code/IMPACT/COM/include/com_c++.hpp"
    "C:/Users/brianweis/code/IMPACT/COM/include/com_devel.hpp"
    "C:/Users/brianweis/code/IMPACT/COM/include/com_exception.hpp"
    "C:/Users/brianweis/code/IMPACT/COM/include/maps.hpp"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include" TYPE FILE FILES "C:/Users/brianweis/code/IMPACT/include/FC.h")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/brianweis/code/IMPACT/lib/libSITCOM.dll.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/brianweis/code/IMPACT/lib/libSITCOM.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSITCOM.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSITCOM.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Qt/Tools/mingw492_32/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSITCOM.dll")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/brianweis/code/IMPACT/lib/libSITCOMF.dll.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/brianweis/code/IMPACT/lib/libSITCOMF.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSITCOMF.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSITCOMF.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Qt/Tools/mingw492_32/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSITCOMF.dll")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/brianweis/code/IMPACT/COM/testing/cmake_install.cmake")

endif()

