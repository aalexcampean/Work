# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.21

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/alexcampean/Documents/university/sem_2/OOP/Labs/Labs Code/a1-912-Campean-Catalin-1"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/alexcampean/Documents/university/sem_2/OOP/Labs/Labs Code/a1-912-Campean-Catalin-1/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/OOP.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/OOP.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/OOP.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OOP.dir/flags.make

CMakeFiles/OOP.dir/main.c.o: CMakeFiles/OOP.dir/flags.make
CMakeFiles/OOP.dir/main.c.o: ../main.c
CMakeFiles/OOP.dir/main.c.o: CMakeFiles/OOP.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/alexcampean/Documents/university/sem_2/OOP/Labs/Labs Code/a1-912-Campean-Catalin-1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/OOP.dir/main.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/OOP.dir/main.c.o -MF CMakeFiles/OOP.dir/main.c.o.d -o CMakeFiles/OOP.dir/main.c.o -c "/Users/alexcampean/Documents/university/sem_2/OOP/Labs/Labs Code/a1-912-Campean-Catalin-1/main.c"

CMakeFiles/OOP.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/OOP.dir/main.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/Users/alexcampean/Documents/university/sem_2/OOP/Labs/Labs Code/a1-912-Campean-Catalin-1/main.c" > CMakeFiles/OOP.dir/main.c.i

CMakeFiles/OOP.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/OOP.dir/main.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/Users/alexcampean/Documents/university/sem_2/OOP/Labs/Labs Code/a1-912-Campean-Catalin-1/main.c" -o CMakeFiles/OOP.dir/main.c.s

# Object files for target OOP
OOP_OBJECTS = \
"CMakeFiles/OOP.dir/main.c.o"

# External object files for target OOP
OOP_EXTERNAL_OBJECTS =

OOP: CMakeFiles/OOP.dir/main.c.o
OOP: CMakeFiles/OOP.dir/build.make
OOP: CMakeFiles/OOP.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/alexcampean/Documents/university/sem_2/OOP/Labs/Labs Code/a1-912-Campean-Catalin-1/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable OOP"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OOP.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OOP.dir/build: OOP
.PHONY : CMakeFiles/OOP.dir/build

CMakeFiles/OOP.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OOP.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OOP.dir/clean

CMakeFiles/OOP.dir/depend:
	cd "/Users/alexcampean/Documents/university/sem_2/OOP/Labs/Labs Code/a1-912-Campean-Catalin-1/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/alexcampean/Documents/university/sem_2/OOP/Labs/Labs Code/a1-912-Campean-Catalin-1" "/Users/alexcampean/Documents/university/sem_2/OOP/Labs/Labs Code/a1-912-Campean-Catalin-1" "/Users/alexcampean/Documents/university/sem_2/OOP/Labs/Labs Code/a1-912-Campean-Catalin-1/cmake-build-debug" "/Users/alexcampean/Documents/university/sem_2/OOP/Labs/Labs Code/a1-912-Campean-Catalin-1/cmake-build-debug" "/Users/alexcampean/Documents/university/sem_2/OOP/Labs/Labs Code/a1-912-Campean-Catalin-1/cmake-build-debug/CMakeFiles/OOP.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/OOP.dir/depend
