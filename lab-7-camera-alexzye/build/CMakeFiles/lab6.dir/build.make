# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.6.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.6.2/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alexye/school/cpe471/lab-7-camera-alexzye

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alexye/school/cpe471/lab-7-camera-alexzye/build

# Include any dependencies generated for this target.
include CMakeFiles/lab6.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/lab6.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/lab6.dir/flags.make

CMakeFiles/lab6.dir/src/GLSL.cpp.o: CMakeFiles/lab6.dir/flags.make
CMakeFiles/lab6.dir/src/GLSL.cpp.o: ../src/GLSL.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexye/school/cpe471/lab-7-camera-alexzye/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/lab6.dir/src/GLSL.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab6.dir/src/GLSL.cpp.o -c /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/GLSL.cpp

CMakeFiles/lab6.dir/src/GLSL.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab6.dir/src/GLSL.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/GLSL.cpp > CMakeFiles/lab6.dir/src/GLSL.cpp.i

CMakeFiles/lab6.dir/src/GLSL.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab6.dir/src/GLSL.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/GLSL.cpp -o CMakeFiles/lab6.dir/src/GLSL.cpp.s

CMakeFiles/lab6.dir/src/GLSL.cpp.o.requires:

.PHONY : CMakeFiles/lab6.dir/src/GLSL.cpp.o.requires

CMakeFiles/lab6.dir/src/GLSL.cpp.o.provides: CMakeFiles/lab6.dir/src/GLSL.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab6.dir/build.make CMakeFiles/lab6.dir/src/GLSL.cpp.o.provides.build
.PHONY : CMakeFiles/lab6.dir/src/GLSL.cpp.o.provides

CMakeFiles/lab6.dir/src/GLSL.cpp.o.provides.build: CMakeFiles/lab6.dir/src/GLSL.cpp.o


CMakeFiles/lab6.dir/src/MatrixStack.cpp.o: CMakeFiles/lab6.dir/flags.make
CMakeFiles/lab6.dir/src/MatrixStack.cpp.o: ../src/MatrixStack.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexye/school/cpe471/lab-7-camera-alexzye/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/lab6.dir/src/MatrixStack.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab6.dir/src/MatrixStack.cpp.o -c /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/MatrixStack.cpp

CMakeFiles/lab6.dir/src/MatrixStack.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab6.dir/src/MatrixStack.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/MatrixStack.cpp > CMakeFiles/lab6.dir/src/MatrixStack.cpp.i

CMakeFiles/lab6.dir/src/MatrixStack.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab6.dir/src/MatrixStack.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/MatrixStack.cpp -o CMakeFiles/lab6.dir/src/MatrixStack.cpp.s

CMakeFiles/lab6.dir/src/MatrixStack.cpp.o.requires:

.PHONY : CMakeFiles/lab6.dir/src/MatrixStack.cpp.o.requires

CMakeFiles/lab6.dir/src/MatrixStack.cpp.o.provides: CMakeFiles/lab6.dir/src/MatrixStack.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab6.dir/build.make CMakeFiles/lab6.dir/src/MatrixStack.cpp.o.provides.build
.PHONY : CMakeFiles/lab6.dir/src/MatrixStack.cpp.o.provides

CMakeFiles/lab6.dir/src/MatrixStack.cpp.o.provides.build: CMakeFiles/lab6.dir/src/MatrixStack.cpp.o


CMakeFiles/lab6.dir/src/Program.cpp.o: CMakeFiles/lab6.dir/flags.make
CMakeFiles/lab6.dir/src/Program.cpp.o: ../src/Program.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexye/school/cpe471/lab-7-camera-alexzye/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/lab6.dir/src/Program.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab6.dir/src/Program.cpp.o -c /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/Program.cpp

CMakeFiles/lab6.dir/src/Program.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab6.dir/src/Program.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/Program.cpp > CMakeFiles/lab6.dir/src/Program.cpp.i

CMakeFiles/lab6.dir/src/Program.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab6.dir/src/Program.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/Program.cpp -o CMakeFiles/lab6.dir/src/Program.cpp.s

CMakeFiles/lab6.dir/src/Program.cpp.o.requires:

.PHONY : CMakeFiles/lab6.dir/src/Program.cpp.o.requires

CMakeFiles/lab6.dir/src/Program.cpp.o.provides: CMakeFiles/lab6.dir/src/Program.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab6.dir/build.make CMakeFiles/lab6.dir/src/Program.cpp.o.provides.build
.PHONY : CMakeFiles/lab6.dir/src/Program.cpp.o.provides

CMakeFiles/lab6.dir/src/Program.cpp.o.provides.build: CMakeFiles/lab6.dir/src/Program.cpp.o


CMakeFiles/lab6.dir/src/Shape.cpp.o: CMakeFiles/lab6.dir/flags.make
CMakeFiles/lab6.dir/src/Shape.cpp.o: ../src/Shape.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexye/school/cpe471/lab-7-camera-alexzye/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/lab6.dir/src/Shape.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab6.dir/src/Shape.cpp.o -c /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/Shape.cpp

CMakeFiles/lab6.dir/src/Shape.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab6.dir/src/Shape.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/Shape.cpp > CMakeFiles/lab6.dir/src/Shape.cpp.i

CMakeFiles/lab6.dir/src/Shape.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab6.dir/src/Shape.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/Shape.cpp -o CMakeFiles/lab6.dir/src/Shape.cpp.s

CMakeFiles/lab6.dir/src/Shape.cpp.o.requires:

.PHONY : CMakeFiles/lab6.dir/src/Shape.cpp.o.requires

CMakeFiles/lab6.dir/src/Shape.cpp.o.provides: CMakeFiles/lab6.dir/src/Shape.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab6.dir/build.make CMakeFiles/lab6.dir/src/Shape.cpp.o.provides.build
.PHONY : CMakeFiles/lab6.dir/src/Shape.cpp.o.provides

CMakeFiles/lab6.dir/src/Shape.cpp.o.provides.build: CMakeFiles/lab6.dir/src/Shape.cpp.o


CMakeFiles/lab6.dir/src/main.cpp.o: CMakeFiles/lab6.dir/flags.make
CMakeFiles/lab6.dir/src/main.cpp.o: ../src/main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/alexye/school/cpe471/lab-7-camera-alexzye/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/lab6.dir/src/main.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/lab6.dir/src/main.cpp.o -c /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/main.cpp

CMakeFiles/lab6.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/lab6.dir/src/main.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/main.cpp > CMakeFiles/lab6.dir/src/main.cpp.i

CMakeFiles/lab6.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/lab6.dir/src/main.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alexye/school/cpe471/lab-7-camera-alexzye/src/main.cpp -o CMakeFiles/lab6.dir/src/main.cpp.s

CMakeFiles/lab6.dir/src/main.cpp.o.requires:

.PHONY : CMakeFiles/lab6.dir/src/main.cpp.o.requires

CMakeFiles/lab6.dir/src/main.cpp.o.provides: CMakeFiles/lab6.dir/src/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/lab6.dir/build.make CMakeFiles/lab6.dir/src/main.cpp.o.provides.build
.PHONY : CMakeFiles/lab6.dir/src/main.cpp.o.provides

CMakeFiles/lab6.dir/src/main.cpp.o.provides.build: CMakeFiles/lab6.dir/src/main.cpp.o


# Object files for target lab6
lab6_OBJECTS = \
"CMakeFiles/lab6.dir/src/GLSL.cpp.o" \
"CMakeFiles/lab6.dir/src/MatrixStack.cpp.o" \
"CMakeFiles/lab6.dir/src/Program.cpp.o" \
"CMakeFiles/lab6.dir/src/Shape.cpp.o" \
"CMakeFiles/lab6.dir/src/main.cpp.o"

# External object files for target lab6
lab6_EXTERNAL_OBJECTS =

lab6: CMakeFiles/lab6.dir/src/GLSL.cpp.o
lab6: CMakeFiles/lab6.dir/src/MatrixStack.cpp.o
lab6: CMakeFiles/lab6.dir/src/Program.cpp.o
lab6: CMakeFiles/lab6.dir/src/Shape.cpp.o
lab6: CMakeFiles/lab6.dir/src/main.cpp.o
lab6: CMakeFiles/lab6.dir/build.make
lab6: /Users/alexye/lib/glfw-3.2.1/debug/src/libglfw3.a
lab6: /Users/alexye/lib/glew-2.0.0/lib/libGLEW.a
lab6: CMakeFiles/lab6.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/alexye/school/cpe471/lab-7-camera-alexzye/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable lab6"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/lab6.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/lab6.dir/build: lab6

.PHONY : CMakeFiles/lab6.dir/build

CMakeFiles/lab6.dir/requires: CMakeFiles/lab6.dir/src/GLSL.cpp.o.requires
CMakeFiles/lab6.dir/requires: CMakeFiles/lab6.dir/src/MatrixStack.cpp.o.requires
CMakeFiles/lab6.dir/requires: CMakeFiles/lab6.dir/src/Program.cpp.o.requires
CMakeFiles/lab6.dir/requires: CMakeFiles/lab6.dir/src/Shape.cpp.o.requires
CMakeFiles/lab6.dir/requires: CMakeFiles/lab6.dir/src/main.cpp.o.requires

.PHONY : CMakeFiles/lab6.dir/requires

CMakeFiles/lab6.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/lab6.dir/cmake_clean.cmake
.PHONY : CMakeFiles/lab6.dir/clean

CMakeFiles/lab6.dir/depend:
	cd /Users/alexye/school/cpe471/lab-7-camera-alexzye/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alexye/school/cpe471/lab-7-camera-alexzye /Users/alexye/school/cpe471/lab-7-camera-alexzye /Users/alexye/school/cpe471/lab-7-camera-alexzye/build /Users/alexye/school/cpe471/lab-7-camera-alexzye/build /Users/alexye/school/cpe471/lab-7-camera-alexzye/build/CMakeFiles/lab6.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/lab6.dir/depend

