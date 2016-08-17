# Install script for directory: C:/Users/brianweis/code/IMPACT/SolverUtils

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
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/BSMesh.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/FEM.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/FieldData.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/GeoPrimitives.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/InterfaceLayer.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/Mesh.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/MeshUtils.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/MeshVTK.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/PGeoPrim.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/PMesh.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/SolverAgent.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/BSMesh.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/FEM.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/FieldData.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/GeoPrimitives.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/InterfaceLayer.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/Mesh.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/MeshUtils.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/MeshVTK.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/PGeoPrim.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/PMesh.H"
    "C:/Users/brianweis/code/IMPACT/SolverUtils/include/SolverAgent.H"
    )
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/brianweis/code/IMPACT/bin/meshgen2d.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/meshgen2d.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/meshgen2d.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Qt/Tools/mingw492_32/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/meshgen2d.exe")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "C:/Users/brianweis/code/IMPACT/lib/libSolverUtils.dll.a")
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "C:/Users/brianweis/code/IMPACT/lib/libSolverUtils.dll")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSolverUtils.dll" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSolverUtils.dll")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Qt/Tools/mingw492_32/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/libSolverUtils.dll")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/brianweis/code/IMPACT/bin/wrl2mesh.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/wrl2mesh.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/wrl2mesh.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Qt/Tools/mingw492_32/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/wrl2mesh.exe")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/brianweis/code/IMPACT/bin/gg2mesh.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/gg2mesh.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/gg2mesh.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Qt/Tools/mingw492_32/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/gg2mesh.exe")
    endif()
  endif()
endif()

if("${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE EXECUTABLE FILES "C:/Users/brianweis/code/IMPACT/bin/t3d2mesh.exe")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/t3d2mesh.exe" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/t3d2mesh.exe")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "C:/Qt/Tools/mingw492_32/bin/strip.exe" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/bin/t3d2mesh.exe")
    endif()
  endif()
endif()

