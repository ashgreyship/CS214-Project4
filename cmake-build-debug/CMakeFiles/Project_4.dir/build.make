# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.8

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
CMAKE_COMMAND = "/Users/gabriel/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/172.4343.16/CLion.app/Contents/bin/cmake/bin/cmake"

# The command to remove a file.
RM = "/Users/gabriel/Library/Application Support/JetBrains/Toolbox/apps/CLion/ch-0/172.4343.16/CLion.app/Contents/bin/cmake/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Project_4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Project_4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Project_4.dir/flags.make

CMakeFiles/Project_4.dir/sorter.c.o: CMakeFiles/Project_4.dir/flags.make
CMakeFiles/Project_4.dir/sorter.c.o: ../sorter.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Project_4.dir/sorter.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Project_4.dir/sorter.c.o   -c "/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4/sorter.c"

CMakeFiles/Project_4.dir/sorter.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project_4.dir/sorter.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4/sorter.c" > CMakeFiles/Project_4.dir/sorter.c.i

CMakeFiles/Project_4.dir/sorter.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project_4.dir/sorter.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4/sorter.c" -o CMakeFiles/Project_4.dir/sorter.c.s

CMakeFiles/Project_4.dir/sorter.c.o.requires:

.PHONY : CMakeFiles/Project_4.dir/sorter.c.o.requires

CMakeFiles/Project_4.dir/sorter.c.o.provides: CMakeFiles/Project_4.dir/sorter.c.o.requires
	$(MAKE) -f CMakeFiles/Project_4.dir/build.make CMakeFiles/Project_4.dir/sorter.c.o.provides.build
.PHONY : CMakeFiles/Project_4.dir/sorter.c.o.provides

CMakeFiles/Project_4.dir/sorter.c.o.provides.build: CMakeFiles/Project_4.dir/sorter.c.o


CMakeFiles/Project_4.dir/client.c.o: CMakeFiles/Project_4.dir/flags.make
CMakeFiles/Project_4.dir/client.c.o: ../client.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building C object CMakeFiles/Project_4.dir/client.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Project_4.dir/client.c.o   -c "/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4/client.c"

CMakeFiles/Project_4.dir/client.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Project_4.dir/client.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4/client.c" > CMakeFiles/Project_4.dir/client.c.i

CMakeFiles/Project_4.dir/client.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Project_4.dir/client.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4/client.c" -o CMakeFiles/Project_4.dir/client.c.s

CMakeFiles/Project_4.dir/client.c.o.requires:

.PHONY : CMakeFiles/Project_4.dir/client.c.o.requires

CMakeFiles/Project_4.dir/client.c.o.provides: CMakeFiles/Project_4.dir/client.c.o.requires
	$(MAKE) -f CMakeFiles/Project_4.dir/build.make CMakeFiles/Project_4.dir/client.c.o.provides.build
.PHONY : CMakeFiles/Project_4.dir/client.c.o.provides

CMakeFiles/Project_4.dir/client.c.o.provides.build: CMakeFiles/Project_4.dir/client.c.o


# Object files for target Project_4
Project_4_OBJECTS = \
"CMakeFiles/Project_4.dir/sorter.c.o" \
"CMakeFiles/Project_4.dir/client.c.o"

# External object files for target Project_4
Project_4_EXTERNAL_OBJECTS =

Project_4: CMakeFiles/Project_4.dir/sorter.c.o
Project_4: CMakeFiles/Project_4.dir/client.c.o
Project_4: CMakeFiles/Project_4.dir/build.make
Project_4: CMakeFiles/Project_4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Linking C executable Project_4"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Project_4.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Project_4.dir/build: Project_4

.PHONY : CMakeFiles/Project_4.dir/build

CMakeFiles/Project_4.dir/requires: CMakeFiles/Project_4.dir/sorter.c.o.requires
CMakeFiles/Project_4.dir/requires: CMakeFiles/Project_4.dir/client.c.o.requires

.PHONY : CMakeFiles/Project_4.dir/requires

CMakeFiles/Project_4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Project_4.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Project_4.dir/clean

CMakeFiles/Project_4.dir/depend:
	cd "/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4" "/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4" "/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4/cmake-build-debug" "/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4/cmake-build-debug" "/Users/gabriel/Onedrive/Education/RU/5th semester/Systems Programming/Project 4/cmake-build-debug/CMakeFiles/Project_4.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Project_4.dir/depend
