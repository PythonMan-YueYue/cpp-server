# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/liujun/Work/Study/CPP/project/cpp-server/io-block

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/liujun/Work/Study/CPP/project/cpp-server/build-io-block-unknown-Debug

# Utility rule file for io-block-server_autogen.

# Include the progress variables for this target.
include io-block-server/CMakeFiles/io-block-server_autogen.dir/progress.make

io-block-server/CMakeFiles/io-block-server_autogen:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/liujun/Work/Study/CPP/project/cpp-server/build-io-block-unknown-Debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Automatic MOC and UIC for target io-block-server"
	cd /home/liujun/Work/Study/CPP/project/cpp-server/build-io-block-unknown-Debug/io-block-server && /usr/bin/cmake -E cmake_autogen /home/liujun/Work/Study/CPP/project/cpp-server/build-io-block-unknown-Debug/io-block-server/CMakeFiles/io-block-server_autogen.dir/AutogenInfo.cmake Debug

io-block-server_autogen: io-block-server/CMakeFiles/io-block-server_autogen
io-block-server_autogen: io-block-server/CMakeFiles/io-block-server_autogen.dir/build.make

.PHONY : io-block-server_autogen

# Rule to build all files generated by this target.
io-block-server/CMakeFiles/io-block-server_autogen.dir/build: io-block-server_autogen

.PHONY : io-block-server/CMakeFiles/io-block-server_autogen.dir/build

io-block-server/CMakeFiles/io-block-server_autogen.dir/clean:
	cd /home/liujun/Work/Study/CPP/project/cpp-server/build-io-block-unknown-Debug/io-block-server && $(CMAKE_COMMAND) -P CMakeFiles/io-block-server_autogen.dir/cmake_clean.cmake
.PHONY : io-block-server/CMakeFiles/io-block-server_autogen.dir/clean

io-block-server/CMakeFiles/io-block-server_autogen.dir/depend:
	cd /home/liujun/Work/Study/CPP/project/cpp-server/build-io-block-unknown-Debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/liujun/Work/Study/CPP/project/cpp-server/io-block /home/liujun/Work/Study/CPP/project/cpp-server/io-block/io-block-server /home/liujun/Work/Study/CPP/project/cpp-server/build-io-block-unknown-Debug /home/liujun/Work/Study/CPP/project/cpp-server/build-io-block-unknown-Debug/io-block-server /home/liujun/Work/Study/CPP/project/cpp-server/build-io-block-unknown-Debug/io-block-server/CMakeFiles/io-block-server_autogen.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : io-block-server/CMakeFiles/io-block-server_autogen.dir/depend

