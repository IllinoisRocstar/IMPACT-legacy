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
include SurfMap/CMakeFiles/pcommpartest.dir/depend.make

# Include the progress variables for this target.
include SurfMap/CMakeFiles/pcommpartest.dir/progress.make

# Include the compile flags for this target's objects.
include SurfMap/CMakeFiles/pcommpartest.dir/flags.make

SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj: SurfMap/CMakeFiles/pcommpartest.dir/flags.make
SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj: SurfMap/CMakeFiles/pcommpartest.dir/includes_CXX.rsp
SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj: SurfMap/test/pcommpartest.C
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\brianweis\code\IMPACT\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj"
	cd /d C:\Users\brianweis\code\IMPACT\SurfMap && C:\Qt\Tools\mingw492_32\bin\g++.exe   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\pcommpartest.dir\test\pcommpartest.C.obj -c C:\Users\brianweis\code\IMPACT\SurfMap\test\pcommpartest.C

SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pcommpartest.dir/test/pcommpartest.C.i"
	cd /d C:\Users\brianweis\code\IMPACT\SurfMap && C:\Qt\Tools\mingw492_32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\brianweis\code\IMPACT\SurfMap\test\pcommpartest.C > CMakeFiles\pcommpartest.dir\test\pcommpartest.C.i

SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pcommpartest.dir/test/pcommpartest.C.s"
	cd /d C:\Users\brianweis\code\IMPACT\SurfMap && C:\Qt\Tools\mingw492_32\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\brianweis\code\IMPACT\SurfMap\test\pcommpartest.C -o CMakeFiles\pcommpartest.dir\test\pcommpartest.C.s

SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj.requires:

.PHONY : SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj.requires

SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj.provides: SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj.requires
	$(MAKE) -f SurfMap\CMakeFiles\pcommpartest.dir\build.make SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj.provides.build
.PHONY : SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj.provides

SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj.provides.build: SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj


# Object files for target pcommpartest
pcommpartest_OBJECTS = \
"CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj"

# External object files for target pcommpartest
pcommpartest_EXTERNAL_OBJECTS =

bin/pcommpartest.exe: SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj
bin/pcommpartest.exe: SurfMap/CMakeFiles/pcommpartest.dir/build.make
bin/pcommpartest.exe: lib/libSurfMap.dll.a
bin/pcommpartest.exe: C:/Program\ Files\ (x86)/Microsoft\ SDKs/MPI/lib/x86/msmpi.lib
bin/pcommpartest.exe: lib/libSimOUT.dll.a
bin/pcommpartest.exe: lib/libSimIN.dll.a
bin/pcommpartest.exe: lib/libRHDF4.dll.a
bin/pcommpartest.exe: C:/Program\ Files/HDF_Group/HDF/4.2.12/lib/libhdf.lib
bin/pcommpartest.exe: C:/Program\ Files/HDF_Group/HDF/4.2.12/lib/libmfhdf.lib
bin/pcommpartest.exe: C:/Program\ Files/HDF_Group/HDF/4.2.12/lib/libjpeg.lib
bin/pcommpartest.exe: lib/libSITCOM.dll.a
bin/pcommpartest.exe: C:/Users/brianweis/code/dlib/dl.dll
bin/pcommpartest.exe: C:/Program\ Files\ (x86)/Microsoft\ SDKs/MPI/lib/x86/msmpi.lib
bin/pcommpartest.exe: SurfMap/CMakeFiles/pcommpartest.dir/linklibs.rsp
bin/pcommpartest.exe: SurfMap/CMakeFiles/pcommpartest.dir/objects1.rsp
bin/pcommpartest.exe: SurfMap/CMakeFiles/pcommpartest.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\brianweis\code\IMPACT\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ..\bin\pcommpartest.exe"
	cd /d C:\Users\brianweis\code\IMPACT\SurfMap && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\pcommpartest.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
SurfMap/CMakeFiles/pcommpartest.dir/build: bin/pcommpartest.exe

.PHONY : SurfMap/CMakeFiles/pcommpartest.dir/build

SurfMap/CMakeFiles/pcommpartest.dir/requires: SurfMap/CMakeFiles/pcommpartest.dir/test/pcommpartest.C.obj.requires

.PHONY : SurfMap/CMakeFiles/pcommpartest.dir/requires

SurfMap/CMakeFiles/pcommpartest.dir/clean:
	cd /d C:\Users\brianweis\code\IMPACT\SurfMap && $(CMAKE_COMMAND) -P CMakeFiles\pcommpartest.dir\cmake_clean.cmake
.PHONY : SurfMap/CMakeFiles/pcommpartest.dir/clean

SurfMap/CMakeFiles/pcommpartest.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\brianweis\code\IMPACT C:\Users\brianweis\code\IMPACT\SurfMap C:\Users\brianweis\code\IMPACT C:\Users\brianweis\code\IMPACT\SurfMap C:\Users\brianweis\code\IMPACT\SurfMap\CMakeFiles\pcommpartest.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : SurfMap/CMakeFiles/pcommpartest.dir/depend

