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

# Utility rule file for run_test_pybind.

# Include any custom commands dependencies for this target.
include CMakeFiles/run_test_pybind.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/run_test_pybind.dir/progress.make

CMakeFiles/run_test_pybind:
	cd /Users/hsiaoyenlaing/Software-course/DE/DE/src && python /Users/hsiaoyenlaing/Software-course/DE/DE/test/test_pybind.py

run_test_pybind: CMakeFiles/run_test_pybind
run_test_pybind: CMakeFiles/run_test_pybind.dir/build.make
.PHONY : run_test_pybind

# Rule to build all files generated by this target.
CMakeFiles/run_test_pybind.dir/build: run_test_pybind
.PHONY : CMakeFiles/run_test_pybind.dir/build

CMakeFiles/run_test_pybind.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/run_test_pybind.dir/cmake_clean.cmake
.PHONY : CMakeFiles/run_test_pybind.dir/clean

CMakeFiles/run_test_pybind.dir/depend:
	cd /Users/hsiaoyenlaing/Software-course/DE/DE/src/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/hsiaoyenlaing/Software-course/DE/DE/src /Users/hsiaoyenlaing/Software-course/DE/DE/src /Users/hsiaoyenlaing/Software-course/DE/DE/src/build /Users/hsiaoyenlaing/Software-course/DE/DE/src/build /Users/hsiaoyenlaing/Software-course/DE/DE/src/build/CMakeFiles/run_test_pybind.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/run_test_pybind.dir/depend

