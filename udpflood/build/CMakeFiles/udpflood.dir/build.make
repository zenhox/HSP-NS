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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /root/ms-bysj/HSP-NS/udpflood

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/ms-bysj/HSP-NS/udpflood/build

# Include any dependencies generated for this target.
include CMakeFiles/udpflood.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/udpflood.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/udpflood.dir/flags.make

CMakeFiles/udpflood.dir/main.cpp.o: CMakeFiles/udpflood.dir/flags.make
CMakeFiles/udpflood.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/ms-bysj/HSP-NS/udpflood/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/udpflood.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/udpflood.dir/main.cpp.o -c /root/ms-bysj/HSP-NS/udpflood/main.cpp

CMakeFiles/udpflood.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/udpflood.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/ms-bysj/HSP-NS/udpflood/main.cpp > CMakeFiles/udpflood.dir/main.cpp.i

CMakeFiles/udpflood.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/udpflood.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/ms-bysj/HSP-NS/udpflood/main.cpp -o CMakeFiles/udpflood.dir/main.cpp.s

CMakeFiles/udpflood.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/udpflood.dir/main.cpp.o.requires

CMakeFiles/udpflood.dir/main.cpp.o.provides: CMakeFiles/udpflood.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/udpflood.dir/build.make CMakeFiles/udpflood.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/udpflood.dir/main.cpp.o.provides

CMakeFiles/udpflood.dir/main.cpp.o.provides.build: CMakeFiles/udpflood.dir/main.cpp.o


# Object files for target udpflood
udpflood_OBJECTS = \
"CMakeFiles/udpflood.dir/main.cpp.o"

# External object files for target udpflood
udpflood_EXTERNAL_OBJECTS =

udpflood: CMakeFiles/udpflood.dir/main.cpp.o
udpflood: CMakeFiles/udpflood.dir/build.make
udpflood: libnetwrok.a
udpflood: libnscore.a
udpflood: /usr/local/lib/libg3logger.so.1.3.2-88
udpflood: ../../lib/ns-3-dev/build/lib/libns3-dev-core-debug.so
udpflood: libthreadpool.a
udpflood: libskiplist.a
udpflood: CMakeFiles/udpflood.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/ms-bysj/HSP-NS/udpflood/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable udpflood"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/udpflood.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/udpflood.dir/build: udpflood

.PHONY : CMakeFiles/udpflood.dir/build

CMakeFiles/udpflood.dir/requires: CMakeFiles/udpflood.dir/main.cpp.o.requires

.PHONY : CMakeFiles/udpflood.dir/requires

CMakeFiles/udpflood.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/udpflood.dir/cmake_clean.cmake
.PHONY : CMakeFiles/udpflood.dir/clean

CMakeFiles/udpflood.dir/depend:
	cd /root/ms-bysj/HSP-NS/udpflood/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/ms-bysj/HSP-NS/udpflood /root/ms-bysj/HSP-NS/udpflood /root/ms-bysj/HSP-NS/udpflood/build /root/ms-bysj/HSP-NS/udpflood/build /root/ms-bysj/HSP-NS/udpflood/build/CMakeFiles/udpflood.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/udpflood.dir/depend

