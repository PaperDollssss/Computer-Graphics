# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.22.2/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.22.2/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/huyusen/Desktop/Computer-Graphics

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/huyusen/Desktop/Computer-Graphics/build

# Include any dependencies generated for this target.
include external/glfw/tests/CMakeFiles/events.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include external/glfw/tests/CMakeFiles/events.dir/compiler_depend.make

# Include the progress variables for this target.
include external/glfw/tests/CMakeFiles/events.dir/progress.make

# Include the compile flags for this target's objects.
include external/glfw/tests/CMakeFiles/events.dir/flags.make

external/glfw/tests/CMakeFiles/events.dir/events.c.o: external/glfw/tests/CMakeFiles/events.dir/flags.make
external/glfw/tests/CMakeFiles/events.dir/events.c.o: ../external/glfw/tests/events.c
external/glfw/tests/CMakeFiles/events.dir/events.c.o: external/glfw/tests/CMakeFiles/events.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/huyusen/Desktop/Computer-Graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object external/glfw/tests/CMakeFiles/events.dir/events.c.o"
	cd /Users/huyusen/Desktop/Computer-Graphics/build/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw/tests/CMakeFiles/events.dir/events.c.o -MF CMakeFiles/events.dir/events.c.o.d -o CMakeFiles/events.dir/events.c.o -c /Users/huyusen/Desktop/Computer-Graphics/external/glfw/tests/events.c

external/glfw/tests/CMakeFiles/events.dir/events.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/events.dir/events.c.i"
	cd /Users/huyusen/Desktop/Computer-Graphics/build/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/huyusen/Desktop/Computer-Graphics/external/glfw/tests/events.c > CMakeFiles/events.dir/events.c.i

external/glfw/tests/CMakeFiles/events.dir/events.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/events.dir/events.c.s"
	cd /Users/huyusen/Desktop/Computer-Graphics/build/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/huyusen/Desktop/Computer-Graphics/external/glfw/tests/events.c -o CMakeFiles/events.dir/events.c.s

external/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o: external/glfw/tests/CMakeFiles/events.dir/flags.make
external/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o: ../external/glfw/deps/getopt.c
external/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o: external/glfw/tests/CMakeFiles/events.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/huyusen/Desktop/Computer-Graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building C object external/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o"
	cd /Users/huyusen/Desktop/Computer-Graphics/build/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o -MF CMakeFiles/events.dir/__/deps/getopt.c.o.d -o CMakeFiles/events.dir/__/deps/getopt.c.o -c /Users/huyusen/Desktop/Computer-Graphics/external/glfw/deps/getopt.c

external/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/events.dir/__/deps/getopt.c.i"
	cd /Users/huyusen/Desktop/Computer-Graphics/build/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/huyusen/Desktop/Computer-Graphics/external/glfw/deps/getopt.c > CMakeFiles/events.dir/__/deps/getopt.c.i

external/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/events.dir/__/deps/getopt.c.s"
	cd /Users/huyusen/Desktop/Computer-Graphics/build/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/huyusen/Desktop/Computer-Graphics/external/glfw/deps/getopt.c -o CMakeFiles/events.dir/__/deps/getopt.c.s

external/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o: external/glfw/tests/CMakeFiles/events.dir/flags.make
external/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o: ../external/glfw/deps/glad_gl.c
external/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o: external/glfw/tests/CMakeFiles/events.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/huyusen/Desktop/Computer-Graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building C object external/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o"
	cd /Users/huyusen/Desktop/Computer-Graphics/build/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT external/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o -MF CMakeFiles/events.dir/__/deps/glad_gl.c.o.d -o CMakeFiles/events.dir/__/deps/glad_gl.c.o -c /Users/huyusen/Desktop/Computer-Graphics/external/glfw/deps/glad_gl.c

external/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/events.dir/__/deps/glad_gl.c.i"
	cd /Users/huyusen/Desktop/Computer-Graphics/build/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/huyusen/Desktop/Computer-Graphics/external/glfw/deps/glad_gl.c > CMakeFiles/events.dir/__/deps/glad_gl.c.i

external/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/events.dir/__/deps/glad_gl.c.s"
	cd /Users/huyusen/Desktop/Computer-Graphics/build/external/glfw/tests && /Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/huyusen/Desktop/Computer-Graphics/external/glfw/deps/glad_gl.c -o CMakeFiles/events.dir/__/deps/glad_gl.c.s

# Object files for target events
events_OBJECTS = \
"CMakeFiles/events.dir/events.c.o" \
"CMakeFiles/events.dir/__/deps/getopt.c.o" \
"CMakeFiles/events.dir/__/deps/glad_gl.c.o"

# External object files for target events
events_EXTERNAL_OBJECTS =

external/glfw/tests/events: external/glfw/tests/CMakeFiles/events.dir/events.c.o
external/glfw/tests/events: external/glfw/tests/CMakeFiles/events.dir/__/deps/getopt.c.o
external/glfw/tests/events: external/glfw/tests/CMakeFiles/events.dir/__/deps/glad_gl.c.o
external/glfw/tests/events: external/glfw/tests/CMakeFiles/events.dir/build.make
external/glfw/tests/events: external/glfw/src/libglfw3.a
external/glfw/tests/events: external/glfw/tests/CMakeFiles/events.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/huyusen/Desktop/Computer-Graphics/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking C executable events"
	cd /Users/huyusen/Desktop/Computer-Graphics/build/external/glfw/tests && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/events.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
external/glfw/tests/CMakeFiles/events.dir/build: external/glfw/tests/events
.PHONY : external/glfw/tests/CMakeFiles/events.dir/build

external/glfw/tests/CMakeFiles/events.dir/clean:
	cd /Users/huyusen/Desktop/Computer-Graphics/build/external/glfw/tests && $(CMAKE_COMMAND) -P CMakeFiles/events.dir/cmake_clean.cmake
.PHONY : external/glfw/tests/CMakeFiles/events.dir/clean

external/glfw/tests/CMakeFiles/events.dir/depend:
	cd /Users/huyusen/Desktop/Computer-Graphics/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/huyusen/Desktop/Computer-Graphics /Users/huyusen/Desktop/Computer-Graphics/external/glfw/tests /Users/huyusen/Desktop/Computer-Graphics/build /Users/huyusen/Desktop/Computer-Graphics/build/external/glfw/tests /Users/huyusen/Desktop/Computer-Graphics/build/external/glfw/tests/CMakeFiles/events.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : external/glfw/tests/CMakeFiles/events.dir/depend

