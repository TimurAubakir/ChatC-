# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alibi/Desktop/echo

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alibi/Desktop/echo/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/echo.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/echo.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/echo.dir/flags.make

CMakeFiles/echo.dir/client.cpp.o: CMakeFiles/echo.dir/flags.make
CMakeFiles/echo.dir/client.cpp.o: ../client.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alibi/Desktop/echo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/echo.dir/client.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo.dir/client.cpp.o -c /Users/alibi/Desktop/echo/client.cpp

CMakeFiles/echo.dir/client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo.dir/client.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alibi/Desktop/echo/client.cpp > CMakeFiles/echo.dir/client.cpp.i

CMakeFiles/echo.dir/client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo.dir/client.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alibi/Desktop/echo/client.cpp -o CMakeFiles/echo.dir/client.cpp.s

CMakeFiles/echo.dir/client.cpp.o.requires:

.PHONY : CMakeFiles/echo.dir/client.cpp.o.requires

CMakeFiles/echo.dir/client.cpp.o.provides: CMakeFiles/echo.dir/client.cpp.o.requires
	$(MAKE) -f CMakeFiles/echo.dir/build.make CMakeFiles/echo.dir/client.cpp.o.provides.build
.PHONY : CMakeFiles/echo.dir/client.cpp.o.provides

CMakeFiles/echo.dir/client.cpp.o.provides.build: CMakeFiles/echo.dir/client.cpp.o


CMakeFiles/echo.dir/server.cpp.o: CMakeFiles/echo.dir/flags.make
CMakeFiles/echo.dir/server.cpp.o: ../server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alibi/Desktop/echo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/echo.dir/server.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/echo.dir/server.cpp.o -c /Users/alibi/Desktop/echo/server.cpp

CMakeFiles/echo.dir/server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/echo.dir/server.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alibi/Desktop/echo/server.cpp > CMakeFiles/echo.dir/server.cpp.i

CMakeFiles/echo.dir/server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/echo.dir/server.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alibi/Desktop/echo/server.cpp -o CMakeFiles/echo.dir/server.cpp.s

CMakeFiles/echo.dir/server.cpp.o.requires:

.PHONY : CMakeFiles/echo.dir/server.cpp.o.requires

CMakeFiles/echo.dir/server.cpp.o.provides: CMakeFiles/echo.dir/server.cpp.o.requires
	$(MAKE) -f CMakeFiles/echo.dir/build.make CMakeFiles/echo.dir/server.cpp.o.provides.build
.PHONY : CMakeFiles/echo.dir/server.cpp.o.provides

CMakeFiles/echo.dir/server.cpp.o.provides.build: CMakeFiles/echo.dir/server.cpp.o


# Object files for target echo
echo_OBJECTS = \
"CMakeFiles/echo.dir/client.cpp.o" \
"CMakeFiles/echo.dir/server.cpp.o"

# External object files for target echo
echo_EXTERNAL_OBJECTS =

echo: CMakeFiles/echo.dir/client.cpp.o
echo: CMakeFiles/echo.dir/server.cpp.o
echo: CMakeFiles/echo.dir/build.make
echo: CMakeFiles/echo.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alibi/Desktop/echo/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable echo"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/echo.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/echo.dir/build: echo

.PHONY : CMakeFiles/echo.dir/build

CMakeFiles/echo.dir/requires: CMakeFiles/echo.dir/client.cpp.o.requires
CMakeFiles/echo.dir/requires: CMakeFiles/echo.dir/server.cpp.o.requires

.PHONY : CMakeFiles/echo.dir/requires

CMakeFiles/echo.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/echo.dir/cmake_clean.cmake
.PHONY : CMakeFiles/echo.dir/clean

CMakeFiles/echo.dir/depend:
	cd /Users/alibi/Desktop/echo/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alibi/Desktop/echo /Users/alibi/Desktop/echo /Users/alibi/Desktop/echo/cmake-build-debug /Users/alibi/Desktop/echo/cmake-build-debug /Users/alibi/Desktop/echo/cmake-build-debug/CMakeFiles/echo.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/echo.dir/depend

