# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.6

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\CMake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\CMake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\brianweis\code\IMPACT

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\brianweis\code\IMPACT

# Include any dependencies generated for this target.
include COM/testing/CMakeFiles/COMFTESTMOD.dir/depend.make

# Include the progress variables for this target.
include COM/testing/CMakeFiles/COMFTESTMOD.dir/progress.make

# Include the compile flags for this target's objects.
include COM/testing/CMakeFiles/COMFTESTMOD.dir/flags.make

COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj: COM/testing/CMakeFiles/COMFTESTMOD.dir/flags.make
COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj: COM/testing/CMakeFiles/COMFTESTMOD.dir/includes_Fortran.rsp
COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj: COM/testing/src/ModTestObject.f90
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\brianweis\code\IMPACT\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building Fortran object COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj"
	cd /d C:\Users\brianweis\code\IMPACT\COM\testing && C:\Qt\Tools\mingw492_32\bin\gfortran.exe  $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -fPIC -c C:\Users\brianweis\code\IMPACT\COM\testing\src\ModTestObject.f90 -o CMakeFiles\COMFTESTMOD.dir\src\ModTestObject.f90.obj

COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing Fortran source to CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.i"
	cd /d C:\Users\brianweis\code\IMPACT\COM\testing && C:\Qt\Tools\mingw492_32\bin\gfortran.exe  $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -fPIC -E C:\Users\brianweis\code\IMPACT\COM\testing\src\ModTestObject.f90 > CMakeFiles\COMFTESTMOD.dir\src\ModTestObject.f90.i

COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling Fortran source to assembly CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.s"
	cd /d C:\Users\brianweis\code\IMPACT\COM\testing && C:\Qt\Tools\mingw492_32\bin\gfortran.exe  $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -fPIC -S C:\Users\brianweis\code\IMPACT\COM\testing\src\ModTestObject.f90 -o CMakeFiles\COMFTESTMOD.dir\src\ModTestObject.f90.s

COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj.requires:

.PHONY : COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj.requires

COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj.provides: COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj.requires
	$(MAKE) -f COM\testing\CMakeFiles\COMFTESTMOD.dir\build.make COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj.provides.build
.PHONY : COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj.provides

COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj.provides.build: COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj


COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj: COM/testing/CMakeFiles/COMFTESTMOD.dir/flags.make
COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj: COM/testing/CMakeFiles/COMFTESTMOD.dir/includes_Fortran.rsp
COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj: COM/testing/src/TestModule.f90
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\brianweis\code\IMPACT\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building Fortran object COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj"
	cd /d C:\Users\brianweis\code\IMPACT\COM\testing && C:\Qt\Tools\mingw492_32\bin\gfortran.exe  $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -fPIC -c C:\Users\brianweis\code\IMPACT\COM\testing\src\TestModule.f90 -o CMakeFiles\COMFTESTMOD.dir\src\TestModule.f90.obj

COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing Fortran source to CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.i"
	cd /d C:\Users\brianweis\code\IMPACT\COM\testing && C:\Qt\Tools\mingw492_32\bin\gfortran.exe  $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -fPIC -E C:\Users\brianweis\code\IMPACT\COM\testing\src\TestModule.f90 > CMakeFiles\COMFTESTMOD.dir\src\TestModule.f90.i

COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling Fortran source to assembly CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.s"
	cd /d C:\Users\brianweis\code\IMPACT\COM\testing && C:\Qt\Tools\mingw492_32\bin\gfortran.exe  $(Fortran_DEFINES) $(Fortran_INCLUDES) $(Fortran_FLAGS) -fPIC -S C:\Users\brianweis\code\IMPACT\COM\testing\src\TestModule.f90 -o CMakeFiles\COMFTESTMOD.dir\src\TestModule.f90.s

COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj.requires:

.PHONY : COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj.requires

COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj.provides: COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj.requires
	$(MAKE) -f COM\testing\CMakeFiles\COMFTESTMOD.dir\build.make COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj.provides.build
.PHONY : COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj.provides

COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj.provides.build: COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj


# Object files for target COMFTESTMOD
COMFTESTMOD_OBJECTS = \
"CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj" \
"CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj"

# External object files for target COMFTESTMOD
COMFTESTMOD_EXTERNAL_OBJECTS =

lib/libCOMFTESTMOD.dll: COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj
lib/libCOMFTESTMOD.dll: COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj
lib/libCOMFTESTMOD.dll: COM/testing/CMakeFiles/COMFTESTMOD.dir/build.make
lib/libCOMFTESTMOD.dll: lib/libSolverUtils.dll.a
lib/libCOMFTESTMOD.dll: lib/libSITCOMF.dll.a
lib/libCOMFTESTMOD.dll: lib/libSITCOM.dll.a
lib/libCOMFTESTMOD.dll: C:/Program\ Files\ (x86)/Microsoft\ SDKs/MPI/lib/x86/msmpi.lib
lib/libCOMFTESTMOD.dll: C:/Program\ Files\ (x86)/Microsoft\ SDKs/MPI/lib/x86/msmpi.lib
lib/libCOMFTESTMOD.dll: lib/libIRAD.dll.a
lib/libCOMFTESTMOD.dll: C:/Users/brianweis/code/dlib/dl.dll
lib/libCOMFTESTMOD.dll: C:/Program\ Files\ (x86)/Microsoft\ SDKs/MPI/lib/x86/msmpi.lib
lib/libCOMFTESTMOD.dll: COM/testing/CMakeFiles/COMFTESTMOD.dir/linklibs.rsp
lib/libCOMFTESTMOD.dll: COM/testing/CMakeFiles/COMFTESTMOD.dir/objects1.rsp
lib/libCOMFTESTMOD.dll: COM/testing/CMakeFiles/COMFTESTMOD.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\brianweis\code\IMPACT\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking Fortran shared library ..\..\lib\libCOMFTESTMOD.dll"
	cd /d C:\Users\brianweis\code\IMPACT\COM\testing && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\COMFTESTMOD.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
COM/testing/CMakeFiles/COMFTESTMOD.dir/build: lib/libCOMFTESTMOD.dll

.PHONY : COM/testing/CMakeFiles/COMFTESTMOD.dir/build

COM/testing/CMakeFiles/COMFTESTMOD.dir/requires: COM/testing/CMakeFiles/COMFTESTMOD.dir/src/ModTestObject.f90.obj.requires
COM/testing/CMakeFiles/COMFTESTMOD.dir/requires: COM/testing/CMakeFiles/COMFTESTMOD.dir/src/TestModule.f90.obj.requires

.PHONY : COM/testing/CMakeFiles/COMFTESTMOD.dir/requires

COM/testing/CMakeFiles/COMFTESTMOD.dir/clean:
	cd /d C:\Users\brianweis\code\IMPACT\COM\testing && $(CMAKE_COMMAND) -P CMakeFiles\COMFTESTMOD.dir\cmake_clean.cmake
.PHONY : COM/testing/CMakeFiles/COMFTESTMOD.dir/clean

COM/testing/CMakeFiles/COMFTESTMOD.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\brianweis\code\IMPACT C:\Users\brianweis\code\IMPACT\COM\testing C:\Users\brianweis\code\IMPACT C:\Users\brianweis\code\IMPACT\COM\testing C:\Users\brianweis\code\IMPACT\COM\testing\CMakeFiles\COMFTESTMOD.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : COM/testing/CMakeFiles/COMFTESTMOD.dir/depend

