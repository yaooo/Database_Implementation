# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

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
CMAKE_SOURCE_DIR = /home/yash/Documents/Oxford/Database-implementation/BufMgr

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin

# Include any dependencies generated for this target.
include bufmgr/CMakeFiles/bufmgr.dir/depend.make

# Include the progress variables for this target.
include bufmgr/CMakeFiles/bufmgr.dir/progress.make

# Include the compile flags for this target's objects.
include bufmgr/CMakeFiles/bufmgr.dir/flags.make

bufmgr/CMakeFiles/bufmgr.dir/bufmgr.o: bufmgr/CMakeFiles/bufmgr.dir/flags.make
bufmgr/CMakeFiles/bufmgr.dir/bufmgr.o: /home/yash/Documents/Oxford/Database-implementation/BufMgr/bufmgr/bufmgr.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object bufmgr/CMakeFiles/bufmgr.dir/bufmgr.o"
	cd /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/bufmgr && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bufmgr.dir/bufmgr.o -c /home/yash/Documents/Oxford/Database-implementation/BufMgr/bufmgr/bufmgr.cpp

bufmgr/CMakeFiles/bufmgr.dir/bufmgr.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bufmgr.dir/bufmgr.i"
	cd /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/bufmgr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yash/Documents/Oxford/Database-implementation/BufMgr/bufmgr/bufmgr.cpp > CMakeFiles/bufmgr.dir/bufmgr.i

bufmgr/CMakeFiles/bufmgr.dir/bufmgr.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bufmgr.dir/bufmgr.s"
	cd /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/bufmgr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yash/Documents/Oxford/Database-implementation/BufMgr/bufmgr/bufmgr.cpp -o CMakeFiles/bufmgr.dir/bufmgr.s

bufmgr/CMakeFiles/bufmgr.dir/bmtest.o: bufmgr/CMakeFiles/bufmgr.dir/flags.make
bufmgr/CMakeFiles/bufmgr.dir/bmtest.o: /home/yash/Documents/Oxford/Database-implementation/BufMgr/bufmgr/bmtest.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object bufmgr/CMakeFiles/bufmgr.dir/bmtest.o"
	cd /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/bufmgr && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bufmgr.dir/bmtest.o -c /home/yash/Documents/Oxford/Database-implementation/BufMgr/bufmgr/bmtest.cpp

bufmgr/CMakeFiles/bufmgr.dir/bmtest.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bufmgr.dir/bmtest.i"
	cd /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/bufmgr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yash/Documents/Oxford/Database-implementation/BufMgr/bufmgr/bmtest.cpp > CMakeFiles/bufmgr.dir/bmtest.i

bufmgr/CMakeFiles/bufmgr.dir/bmtest.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bufmgr.dir/bmtest.s"
	cd /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/bufmgr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yash/Documents/Oxford/Database-implementation/BufMgr/bufmgr/bmtest.cpp -o CMakeFiles/bufmgr.dir/bmtest.s

bufmgr/CMakeFiles/bufmgr.dir/frame.o: bufmgr/CMakeFiles/bufmgr.dir/flags.make
bufmgr/CMakeFiles/bufmgr.dir/frame.o: /home/yash/Documents/Oxford/Database-implementation/BufMgr/bufmgr/frame.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object bufmgr/CMakeFiles/bufmgr.dir/frame.o"
	cd /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/bufmgr && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/bufmgr.dir/frame.o -c /home/yash/Documents/Oxford/Database-implementation/BufMgr/bufmgr/frame.cpp

bufmgr/CMakeFiles/bufmgr.dir/frame.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bufmgr.dir/frame.i"
	cd /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/bufmgr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/yash/Documents/Oxford/Database-implementation/BufMgr/bufmgr/frame.cpp > CMakeFiles/bufmgr.dir/frame.i

bufmgr/CMakeFiles/bufmgr.dir/frame.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bufmgr.dir/frame.s"
	cd /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/bufmgr && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/yash/Documents/Oxford/Database-implementation/BufMgr/bufmgr/frame.cpp -o CMakeFiles/bufmgr.dir/frame.s

# Object files for target bufmgr
bufmgr_OBJECTS = \
"CMakeFiles/bufmgr.dir/bufmgr.o" \
"CMakeFiles/bufmgr.dir/bmtest.o" \
"CMakeFiles/bufmgr.dir/frame.o"

# External object files for target bufmgr
bufmgr_EXTERNAL_OBJECTS =

bufmgr/libbufmgr.a: bufmgr/CMakeFiles/bufmgr.dir/bufmgr.o
bufmgr/libbufmgr.a: bufmgr/CMakeFiles/bufmgr.dir/bmtest.o
bufmgr/libbufmgr.a: bufmgr/CMakeFiles/bufmgr.dir/frame.o
bufmgr/libbufmgr.a: bufmgr/CMakeFiles/bufmgr.dir/build.make
bufmgr/libbufmgr.a: bufmgr/CMakeFiles/bufmgr.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX static library libbufmgr.a"
	cd /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/bufmgr && $(CMAKE_COMMAND) -P CMakeFiles/bufmgr.dir/cmake_clean_target.cmake
	cd /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/bufmgr && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/bufmgr.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
bufmgr/CMakeFiles/bufmgr.dir/build: bufmgr/libbufmgr.a

.PHONY : bufmgr/CMakeFiles/bufmgr.dir/build

bufmgr/CMakeFiles/bufmgr.dir/clean:
	cd /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/bufmgr && $(CMAKE_COMMAND) -P CMakeFiles/bufmgr.dir/cmake_clean.cmake
.PHONY : bufmgr/CMakeFiles/bufmgr.dir/clean

bufmgr/CMakeFiles/bufmgr.dir/depend:
	cd /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/yash/Documents/Oxford/Database-implementation/BufMgr /home/yash/Documents/Oxford/Database-implementation/BufMgr/bufmgr /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/bufmgr /home/yash/Documents/Oxford/Database-implementation/BufMgr-bin/bufmgr/CMakeFiles/bufmgr.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : bufmgr/CMakeFiles/bufmgr.dir/depend

