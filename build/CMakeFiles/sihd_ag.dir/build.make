# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.27

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/lunemonday/repo_progetto

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/lunemonday/repo_progetto/build

# Include any dependencies generated for this target.
include CMakeFiles/sihd_ag.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/sihd_ag.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/sihd_ag.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/sihd_ag.dir/flags.make

CMakeFiles/sihd_ag.dir/pandemic.cpp.o: CMakeFiles/sihd_ag.dir/flags.make
CMakeFiles/sihd_ag.dir/pandemic.cpp.o: /home/lunemonday/repo_progetto/pandemic.cpp
CMakeFiles/sihd_ag.dir/pandemic.cpp.o: CMakeFiles/sihd_ag.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lunemonday/repo_progetto/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/sihd_ag.dir/pandemic.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sihd_ag.dir/pandemic.cpp.o -MF CMakeFiles/sihd_ag.dir/pandemic.cpp.o.d -o CMakeFiles/sihd_ag.dir/pandemic.cpp.o -c /home/lunemonday/repo_progetto/pandemic.cpp

CMakeFiles/sihd_ag.dir/pandemic.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sihd_ag.dir/pandemic.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lunemonday/repo_progetto/pandemic.cpp > CMakeFiles/sihd_ag.dir/pandemic.cpp.i

CMakeFiles/sihd_ag.dir/pandemic.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sihd_ag.dir/pandemic.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lunemonday/repo_progetto/pandemic.cpp -o CMakeFiles/sihd_ag.dir/pandemic.cpp.s

CMakeFiles/sihd_ag.dir/agent.cpp.o: CMakeFiles/sihd_ag.dir/flags.make
CMakeFiles/sihd_ag.dir/agent.cpp.o: /home/lunemonday/repo_progetto/agent.cpp
CMakeFiles/sihd_ag.dir/agent.cpp.o: CMakeFiles/sihd_ag.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lunemonday/repo_progetto/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/sihd_ag.dir/agent.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sihd_ag.dir/agent.cpp.o -MF CMakeFiles/sihd_ag.dir/agent.cpp.o.d -o CMakeFiles/sihd_ag.dir/agent.cpp.o -c /home/lunemonday/repo_progetto/agent.cpp

CMakeFiles/sihd_ag.dir/agent.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sihd_ag.dir/agent.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lunemonday/repo_progetto/agent.cpp > CMakeFiles/sihd_ag.dir/agent.cpp.i

CMakeFiles/sihd_ag.dir/agent.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sihd_ag.dir/agent.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lunemonday/repo_progetto/agent.cpp -o CMakeFiles/sihd_ag.dir/agent.cpp.s

CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.o: CMakeFiles/sihd_ag.dir/flags.make
CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.o: /home/lunemonday/repo_progetto/main_ag_simulation.cpp
CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.o: CMakeFiles/sihd_ag.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/lunemonday/repo_progetto/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.o -MF CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.o.d -o CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.o -c /home/lunemonday/repo_progetto/main_ag_simulation.cpp

CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/lunemonday/repo_progetto/main_ag_simulation.cpp > CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.i

CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/lunemonday/repo_progetto/main_ag_simulation.cpp -o CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.s

# Object files for target sihd_ag
sihd_ag_OBJECTS = \
"CMakeFiles/sihd_ag.dir/pandemic.cpp.o" \
"CMakeFiles/sihd_ag.dir/agent.cpp.o" \
"CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.o"

# External object files for target sihd_ag
sihd_ag_EXTERNAL_OBJECTS =

sihd_ag: CMakeFiles/sihd_ag.dir/pandemic.cpp.o
sihd_ag: CMakeFiles/sihd_ag.dir/agent.cpp.o
sihd_ag: CMakeFiles/sihd_ag.dir/main_ag_simulation.cpp.o
sihd_ag: CMakeFiles/sihd_ag.dir/build.make
sihd_ag: /usr/lib/x86_64-linux-gnu/libsfml-graphics.so.2.5.1
sihd_ag: /usr/lib/x86_64-linux-gnu/libsfml-window.so.2.5.1
sihd_ag: /usr/lib/x86_64-linux-gnu/libsfml-system.so.2.5.1
sihd_ag: CMakeFiles/sihd_ag.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/lunemonday/repo_progetto/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable sihd_ag"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/sihd_ag.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/sihd_ag.dir/build: sihd_ag
.PHONY : CMakeFiles/sihd_ag.dir/build

CMakeFiles/sihd_ag.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/sihd_ag.dir/cmake_clean.cmake
.PHONY : CMakeFiles/sihd_ag.dir/clean

CMakeFiles/sihd_ag.dir/depend:
	cd /home/lunemonday/repo_progetto/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/lunemonday/repo_progetto /home/lunemonday/repo_progetto /home/lunemonday/repo_progetto/build /home/lunemonday/repo_progetto/build /home/lunemonday/repo_progetto/build/CMakeFiles/sihd_ag.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/sihd_ag.dir/depend

