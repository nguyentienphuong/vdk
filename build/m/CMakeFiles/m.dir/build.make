# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_SOURCE_DIR = /home/phuong/tn/src

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/phuong/tn/build

# Include any dependencies generated for this target.
include m/CMakeFiles/m.dir/depend.make

# Include the progress variables for this target.
include m/CMakeFiles/m.dir/progress.make

# Include the compile flags for this target's objects.
include m/CMakeFiles/m.dir/flags.make

m/CMakeFiles/m.dir/src/m.cpp.o: m/CMakeFiles/m.dir/flags.make
m/CMakeFiles/m.dir/src/m.cpp.o: /home/phuong/tn/src/m/src/m.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/phuong/tn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object m/CMakeFiles/m.dir/src/m.cpp.o"
	cd /home/phuong/tn/build/m && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/m.dir/src/m.cpp.o -c /home/phuong/tn/src/m/src/m.cpp

m/CMakeFiles/m.dir/src/m.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/m.dir/src/m.cpp.i"
	cd /home/phuong/tn/build/m && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/phuong/tn/src/m/src/m.cpp > CMakeFiles/m.dir/src/m.cpp.i

m/CMakeFiles/m.dir/src/m.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/m.dir/src/m.cpp.s"
	cd /home/phuong/tn/build/m && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/phuong/tn/src/m/src/m.cpp -o CMakeFiles/m.dir/src/m.cpp.s

# Object files for target m
m_OBJECTS = \
"CMakeFiles/m.dir/src/m.cpp.o"

# External object files for target m
m_EXTERNAL_OBJECTS =

/home/phuong/tn/devel/lib/m/m: m/CMakeFiles/m.dir/src/m.cpp.o
/home/phuong/tn/devel/lib/m/m: m/CMakeFiles/m.dir/build.make
/home/phuong/tn/devel/lib/m/m: /opt/ros/noetic/lib/libroscpp.so
/home/phuong/tn/devel/lib/m/m: /usr/lib/x86_64-linux-gnu/libpthread.so
/home/phuong/tn/devel/lib/m/m: /usr/lib/x86_64-linux-gnu/libboost_chrono.so.1.71.0
/home/phuong/tn/devel/lib/m/m: /usr/lib/x86_64-linux-gnu/libboost_filesystem.so.1.71.0
/home/phuong/tn/devel/lib/m/m: /opt/ros/noetic/lib/librosconsole.so
/home/phuong/tn/devel/lib/m/m: /opt/ros/noetic/lib/librosconsole_log4cxx.so
/home/phuong/tn/devel/lib/m/m: /opt/ros/noetic/lib/librosconsole_backend_interface.so
/home/phuong/tn/devel/lib/m/m: /usr/lib/x86_64-linux-gnu/liblog4cxx.so
/home/phuong/tn/devel/lib/m/m: /usr/lib/x86_64-linux-gnu/libboost_regex.so.1.71.0
/home/phuong/tn/devel/lib/m/m: /opt/ros/noetic/lib/libxmlrpcpp.so
/home/phuong/tn/devel/lib/m/m: /opt/ros/noetic/lib/libroscpp_serialization.so
/home/phuong/tn/devel/lib/m/m: /opt/ros/noetic/lib/librostime.so
/home/phuong/tn/devel/lib/m/m: /usr/lib/x86_64-linux-gnu/libboost_date_time.so.1.71.0
/home/phuong/tn/devel/lib/m/m: /opt/ros/noetic/lib/libcpp_common.so
/home/phuong/tn/devel/lib/m/m: /usr/lib/x86_64-linux-gnu/libboost_system.so.1.71.0
/home/phuong/tn/devel/lib/m/m: /usr/lib/x86_64-linux-gnu/libboost_thread.so.1.71.0
/home/phuong/tn/devel/lib/m/m: /usr/lib/x86_64-linux-gnu/libconsole_bridge.so.0.4
/home/phuong/tn/devel/lib/m/m: m/CMakeFiles/m.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/phuong/tn/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable /home/phuong/tn/devel/lib/m/m"
	cd /home/phuong/tn/build/m && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/m.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
m/CMakeFiles/m.dir/build: /home/phuong/tn/devel/lib/m/m

.PHONY : m/CMakeFiles/m.dir/build

m/CMakeFiles/m.dir/clean:
	cd /home/phuong/tn/build/m && $(CMAKE_COMMAND) -P CMakeFiles/m.dir/cmake_clean.cmake
.PHONY : m/CMakeFiles/m.dir/clean

m/CMakeFiles/m.dir/depend:
	cd /home/phuong/tn/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/phuong/tn/src /home/phuong/tn/src/m /home/phuong/tn/build /home/phuong/tn/build/m /home/phuong/tn/build/m/CMakeFiles/m.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : m/CMakeFiles/m.dir/depend

