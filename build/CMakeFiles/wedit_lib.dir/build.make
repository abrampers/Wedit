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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.10.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.10.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/build"

# Include any dependencies generated for this target.
include CMakeFiles/wedit_lib.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/wedit_lib.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/wedit_lib.dir/flags.make

CMakeFiles/wedit_lib.dir/src/crdt.cc.o: CMakeFiles/wedit_lib.dir/flags.make
CMakeFiles/wedit_lib.dir/src/crdt.cc.o: ../src/crdt.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/wedit_lib.dir/src/crdt.cc.o"
	/usr/local/Cellar/gcc/8.2.0/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wedit_lib.dir/src/crdt.cc.o -c "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/src/crdt.cc"

CMakeFiles/wedit_lib.dir/src/crdt.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wedit_lib.dir/src/crdt.cc.i"
	/usr/local/Cellar/gcc/8.2.0/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/src/crdt.cc" > CMakeFiles/wedit_lib.dir/src/crdt.cc.i

CMakeFiles/wedit_lib.dir/src/crdt.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wedit_lib.dir/src/crdt.cc.s"
	/usr/local/Cellar/gcc/8.2.0/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/src/crdt.cc" -o CMakeFiles/wedit_lib.dir/src/crdt.cc.s

CMakeFiles/wedit_lib.dir/src/crdt.cc.o.requires:

.PHONY : CMakeFiles/wedit_lib.dir/src/crdt.cc.o.requires

CMakeFiles/wedit_lib.dir/src/crdt.cc.o.provides: CMakeFiles/wedit_lib.dir/src/crdt.cc.o.requires
	$(MAKE) -f CMakeFiles/wedit_lib.dir/build.make CMakeFiles/wedit_lib.dir/src/crdt.cc.o.provides.build
.PHONY : CMakeFiles/wedit_lib.dir/src/crdt.cc.o.provides

CMakeFiles/wedit_lib.dir/src/crdt.cc.o.provides.build: CMakeFiles/wedit_lib.dir/src/crdt.cc.o


CMakeFiles/wedit_lib.dir/src/item.cc.o: CMakeFiles/wedit_lib.dir/flags.make
CMakeFiles/wedit_lib.dir/src/item.cc.o: ../src/item.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/wedit_lib.dir/src/item.cc.o"
	/usr/local/Cellar/gcc/8.2.0/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wedit_lib.dir/src/item.cc.o -c "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/src/item.cc"

CMakeFiles/wedit_lib.dir/src/item.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wedit_lib.dir/src/item.cc.i"
	/usr/local/Cellar/gcc/8.2.0/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/src/item.cc" > CMakeFiles/wedit_lib.dir/src/item.cc.i

CMakeFiles/wedit_lib.dir/src/item.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wedit_lib.dir/src/item.cc.s"
	/usr/local/Cellar/gcc/8.2.0/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/src/item.cc" -o CMakeFiles/wedit_lib.dir/src/item.cc.s

CMakeFiles/wedit_lib.dir/src/item.cc.o.requires:

.PHONY : CMakeFiles/wedit_lib.dir/src/item.cc.o.requires

CMakeFiles/wedit_lib.dir/src/item.cc.o.provides: CMakeFiles/wedit_lib.dir/src/item.cc.o.requires
	$(MAKE) -f CMakeFiles/wedit_lib.dir/build.make CMakeFiles/wedit_lib.dir/src/item.cc.o.provides.build
.PHONY : CMakeFiles/wedit_lib.dir/src/item.cc.o.provides

CMakeFiles/wedit_lib.dir/src/item.cc.o.provides.build: CMakeFiles/wedit_lib.dir/src/item.cc.o


CMakeFiles/wedit_lib.dir/src/uid.cc.o: CMakeFiles/wedit_lib.dir/flags.make
CMakeFiles/wedit_lib.dir/src/uid.cc.o: ../src/uid.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/wedit_lib.dir/src/uid.cc.o"
	/usr/local/Cellar/gcc/8.2.0/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wedit_lib.dir/src/uid.cc.o -c "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/src/uid.cc"

CMakeFiles/wedit_lib.dir/src/uid.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wedit_lib.dir/src/uid.cc.i"
	/usr/local/Cellar/gcc/8.2.0/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/src/uid.cc" > CMakeFiles/wedit_lib.dir/src/uid.cc.i

CMakeFiles/wedit_lib.dir/src/uid.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wedit_lib.dir/src/uid.cc.s"
	/usr/local/Cellar/gcc/8.2.0/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/src/uid.cc" -o CMakeFiles/wedit_lib.dir/src/uid.cc.s

CMakeFiles/wedit_lib.dir/src/uid.cc.o.requires:

.PHONY : CMakeFiles/wedit_lib.dir/src/uid.cc.o.requires

CMakeFiles/wedit_lib.dir/src/uid.cc.o.provides: CMakeFiles/wedit_lib.dir/src/uid.cc.o.requires
	$(MAKE) -f CMakeFiles/wedit_lib.dir/build.make CMakeFiles/wedit_lib.dir/src/uid.cc.o.provides.build
.PHONY : CMakeFiles/wedit_lib.dir/src/uid.cc.o.provides

CMakeFiles/wedit_lib.dir/src/uid.cc.o.provides.build: CMakeFiles/wedit_lib.dir/src/uid.cc.o


CMakeFiles/wedit_lib.dir/src/utils.cc.o: CMakeFiles/wedit_lib.dir/flags.make
CMakeFiles/wedit_lib.dir/src/utils.cc.o: ../src/utils.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/wedit_lib.dir/src/utils.cc.o"
	/usr/local/Cellar/gcc/8.2.0/bin/g++-8  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/wedit_lib.dir/src/utils.cc.o -c "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/src/utils.cc"

CMakeFiles/wedit_lib.dir/src/utils.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/wedit_lib.dir/src/utils.cc.i"
	/usr/local/Cellar/gcc/8.2.0/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/src/utils.cc" > CMakeFiles/wedit_lib.dir/src/utils.cc.i

CMakeFiles/wedit_lib.dir/src/utils.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/wedit_lib.dir/src/utils.cc.s"
	/usr/local/Cellar/gcc/8.2.0/bin/g++-8 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/src/utils.cc" -o CMakeFiles/wedit_lib.dir/src/utils.cc.s

CMakeFiles/wedit_lib.dir/src/utils.cc.o.requires:

.PHONY : CMakeFiles/wedit_lib.dir/src/utils.cc.o.requires

CMakeFiles/wedit_lib.dir/src/utils.cc.o.provides: CMakeFiles/wedit_lib.dir/src/utils.cc.o.requires
	$(MAKE) -f CMakeFiles/wedit_lib.dir/build.make CMakeFiles/wedit_lib.dir/src/utils.cc.o.provides.build
.PHONY : CMakeFiles/wedit_lib.dir/src/utils.cc.o.provides

CMakeFiles/wedit_lib.dir/src/utils.cc.o.provides.build: CMakeFiles/wedit_lib.dir/src/utils.cc.o


# Object files for target wedit_lib
wedit_lib_OBJECTS = \
"CMakeFiles/wedit_lib.dir/src/crdt.cc.o" \
"CMakeFiles/wedit_lib.dir/src/item.cc.o" \
"CMakeFiles/wedit_lib.dir/src/uid.cc.o" \
"CMakeFiles/wedit_lib.dir/src/utils.cc.o"

# External object files for target wedit_lib
wedit_lib_EXTERNAL_OBJECTS =

libwedit_lib.a: CMakeFiles/wedit_lib.dir/src/crdt.cc.o
libwedit_lib.a: CMakeFiles/wedit_lib.dir/src/item.cc.o
libwedit_lib.a: CMakeFiles/wedit_lib.dir/src/uid.cc.o
libwedit_lib.a: CMakeFiles/wedit_lib.dir/src/utils.cc.o
libwedit_lib.a: CMakeFiles/wedit_lib.dir/build.make
libwedit_lib.a: CMakeFiles/wedit_lib.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX static library libwedit_lib.a"
	$(CMAKE_COMMAND) -P CMakeFiles/wedit_lib.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/wedit_lib.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/wedit_lib.dir/build: libwedit_lib.a

.PHONY : CMakeFiles/wedit_lib.dir/build

CMakeFiles/wedit_lib.dir/requires: CMakeFiles/wedit_lib.dir/src/crdt.cc.o.requires
CMakeFiles/wedit_lib.dir/requires: CMakeFiles/wedit_lib.dir/src/item.cc.o.requires
CMakeFiles/wedit_lib.dir/requires: CMakeFiles/wedit_lib.dir/src/uid.cc.o.requires
CMakeFiles/wedit_lib.dir/requires: CMakeFiles/wedit_lib.dir/src/utils.cc.o.requires

.PHONY : CMakeFiles/wedit_lib.dir/requires

CMakeFiles/wedit_lib.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/wedit_lib.dir/cmake_clean.cmake
.PHONY : CMakeFiles/wedit_lib.dir/clean

CMakeFiles/wedit_lib.dir/depend:
	cd "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit" "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit" "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/build" "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/build" "/Users/ffahleraz/Documents/ITB/Semester 6/Sister/tubes/wedit/build/CMakeFiles/wedit_lib.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/wedit_lib.dir/depend

