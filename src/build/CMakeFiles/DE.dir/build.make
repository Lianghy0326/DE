# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/Cellar/cmake/3.28.3/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/hsiaoyenlaing/Software-course/DE/DE/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/hsiaoyenlaing/Software-course/DE/DE/src/build

# Include any dependencies generated for this target.
include CMakeFiles/DE.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/DE.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/DE.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DE.dir/flags.make

CMakeFiles/DE.dir/main.cpp.o: CMakeFiles/DE.dir/flags.make
CMakeFiles/DE.dir/main.cpp.o: /Users/hsiaoyenlaing/Software-course/DE/DE/src/main.cpp
CMakeFiles/DE.dir/main.cpp.o: CMakeFiles/DE.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/hsiaoyenlaing/Software-course/DE/DE/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/DE.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/DE.dir/main.cpp.o -MF CMakeFiles/DE.dir/main.cpp.o.d -o CMakeFiles/DE.dir/main.cpp.o -c /Users/hsiaoyenlaing/Software-course/DE/DE/src/main.cpp

CMakeFiles/DE.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/DE.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/hsiaoyenlaing/Software-course/DE/DE/src/main.cpp > CMakeFiles/DE.dir/main.cpp.i

CMakeFiles/DE.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/DE.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/hsiaoyenlaing/Software-course/DE/DE/src/main.cpp -o CMakeFiles/DE.dir/main.cpp.s

# Object files for target DE
DE_OBJECTS = \
"CMakeFiles/DE.dir/main.cpp.o"

# External object files for target DE
DE_EXTERNAL_OBJECTS =

DE: CMakeFiles/DE.dir/main.cpp.o
DE: CMakeFiles/DE.dir/build.make
DE: /opt/homebrew/opt/python@3.12/Frameworks/Python.framework/Versions/3.12/lib/libpython3.12.dylib
DE: CMakeFiles/DE.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/hsiaoyenlaing/Software-course/DE/DE/src/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable DE"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DE.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DE.dir/build: DE
.PHONY : CMakeFiles/DE.dir/build

CMakeFiles/DE.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DE.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DE.dir/clean

CMakeFiles/DE.dir/depend:
	cd /Users/hsiaoyenlaing/Software-course/DE/DE/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hsiaoyenlaing/Software-course/DE/DE/src /Users/hsiaoyenlaing/Software-course/DE/DE/src /Users/hsiaoyenlaing/Software-course/DE/DE/src/build /Users/hsiaoyenlaing/Software-course/DE/DE/src/build /Users/hsiaoyenlaing/Software-course/DE/DE/src/build/CMakeFiles/DE.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/DE.dir/depend

