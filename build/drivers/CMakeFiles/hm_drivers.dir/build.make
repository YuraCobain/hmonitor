# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/ikobein/dev/evo/hmonitor

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ikobein/dev/evo/hmonitor/build

# Include any dependencies generated for this target.
include drivers/CMakeFiles/hm_drivers.dir/depend.make

# Include the progress variables for this target.
include drivers/CMakeFiles/hm_drivers.dir/progress.make

# Include the compile flags for this target's objects.
include drivers/CMakeFiles/hm_drivers.dir/flags.make

# Object files for target hm_drivers
hm_drivers_OBJECTS =

# External object files for target hm_drivers
hm_drivers_EXTERNAL_OBJECTS = \
"/home/ikobein/dev/evo/hmonitor/build/drivers/src/CMakeFiles/gen_drivers.dir/hm_led.c.obj"

drivers/libhm_drivers.a: drivers/src/CMakeFiles/gen_drivers.dir/hm_led.c.obj
drivers/libhm_drivers.a: drivers/CMakeFiles/hm_drivers.dir/build.make
drivers/libhm_drivers.a: drivers/CMakeFiles/hm_drivers.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ikobein/dev/evo/hmonitor/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Linking C static library libhm_drivers.a"
	cd /home/ikobein/dev/evo/hmonitor/build/drivers && $(CMAKE_COMMAND) -P CMakeFiles/hm_drivers.dir/cmake_clean_target.cmake
	cd /home/ikobein/dev/evo/hmonitor/build/drivers && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/hm_drivers.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
drivers/CMakeFiles/hm_drivers.dir/build: drivers/libhm_drivers.a

.PHONY : drivers/CMakeFiles/hm_drivers.dir/build

drivers/CMakeFiles/hm_drivers.dir/requires:

.PHONY : drivers/CMakeFiles/hm_drivers.dir/requires

drivers/CMakeFiles/hm_drivers.dir/clean:
	cd /home/ikobein/dev/evo/hmonitor/build/drivers && $(CMAKE_COMMAND) -P CMakeFiles/hm_drivers.dir/cmake_clean.cmake
.PHONY : drivers/CMakeFiles/hm_drivers.dir/clean

drivers/CMakeFiles/hm_drivers.dir/depend:
	cd /home/ikobein/dev/evo/hmonitor/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ikobein/dev/evo/hmonitor /home/ikobein/dev/evo/hmonitor/drivers /home/ikobein/dev/evo/hmonitor/build /home/ikobein/dev/evo/hmonitor/build/drivers /home/ikobein/dev/evo/hmonitor/build/drivers/CMakeFiles/hm_drivers.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : drivers/CMakeFiles/hm_drivers.dir/depend

