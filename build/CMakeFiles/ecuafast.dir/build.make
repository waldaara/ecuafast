# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/davidaragundy/ecuafast

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/davidaragundy/ecuafast/build

# Include any dependencies generated for this target.
include CMakeFiles/ecuafast.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/ecuafast.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/ecuafast.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ecuafast.dir/flags.make

CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.o: CMakeFiles/ecuafast.dir/flags.make
CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.o: ../src/entities/senae_server.cpp
CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.o: CMakeFiles/ecuafast.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davidaragundy/ecuafast/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.o -MF CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.o.d -o CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.o -c /home/davidaragundy/ecuafast/src/entities/senae_server.cpp

CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davidaragundy/ecuafast/src/entities/senae_server.cpp > CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.i

CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davidaragundy/ecuafast/src/entities/senae_server.cpp -o CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.s

CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.o: CMakeFiles/ecuafast.dir/flags.make
CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.o: ../src/entities/sri_server.cpp
CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.o: CMakeFiles/ecuafast.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davidaragundy/ecuafast/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.o -MF CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.o.d -o CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.o -c /home/davidaragundy/ecuafast/src/entities/sri_server.cpp

CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davidaragundy/ecuafast/src/entities/sri_server.cpp > CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.i

CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davidaragundy/ecuafast/src/entities/sri_server.cpp -o CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.s

CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.o: CMakeFiles/ecuafast.dir/flags.make
CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.o: ../src/entities/supercia_server.cpp
CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.o: CMakeFiles/ecuafast.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davidaragundy/ecuafast/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.o -MF CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.o.d -o CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.o -c /home/davidaragundy/ecuafast/src/entities/supercia_server.cpp

CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davidaragundy/ecuafast/src/entities/supercia_server.cpp > CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.i

CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davidaragundy/ecuafast/src/entities/supercia_server.cpp -o CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.s

CMakeFiles/ecuafast.dir/src/main.cpp.o: CMakeFiles/ecuafast.dir/flags.make
CMakeFiles/ecuafast.dir/src/main.cpp.o: ../src/main.cpp
CMakeFiles/ecuafast.dir/src/main.cpp.o: CMakeFiles/ecuafast.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davidaragundy/ecuafast/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/ecuafast.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ecuafast.dir/src/main.cpp.o -MF CMakeFiles/ecuafast.dir/src/main.cpp.o.d -o CMakeFiles/ecuafast.dir/src/main.cpp.o -c /home/davidaragundy/ecuafast/src/main.cpp

CMakeFiles/ecuafast.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecuafast.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davidaragundy/ecuafast/src/main.cpp > CMakeFiles/ecuafast.dir/src/main.cpp.i

CMakeFiles/ecuafast.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecuafast.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davidaragundy/ecuafast/src/main.cpp -o CMakeFiles/ecuafast.dir/src/main.cpp.s

CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.o: CMakeFiles/ecuafast.dir/flags.make
CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.o: ../src/port/port_manager.cpp
CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.o: CMakeFiles/ecuafast.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davidaragundy/ecuafast/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.o -MF CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.o.d -o CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.o -c /home/davidaragundy/ecuafast/src/port/port_manager.cpp

CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davidaragundy/ecuafast/src/port/port_manager.cpp > CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.i

CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davidaragundy/ecuafast/src/port/port_manager.cpp -o CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.s

CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.o: CMakeFiles/ecuafast.dir/flags.make
CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.o: ../src/ship/ship_client.cpp
CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.o: CMakeFiles/ecuafast.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/davidaragundy/ecuafast/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.o -MF CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.o.d -o CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.o -c /home/davidaragundy/ecuafast/src/ship/ship_client.cpp

CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/davidaragundy/ecuafast/src/ship/ship_client.cpp > CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.i

CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/davidaragundy/ecuafast/src/ship/ship_client.cpp -o CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.s

# Object files for target ecuafast
ecuafast_OBJECTS = \
"CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.o" \
"CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.o" \
"CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.o" \
"CMakeFiles/ecuafast.dir/src/main.cpp.o" \
"CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.o" \
"CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.o"

# External object files for target ecuafast
ecuafast_EXTERNAL_OBJECTS =

ecuafast: CMakeFiles/ecuafast.dir/src/entities/senae_server.cpp.o
ecuafast: CMakeFiles/ecuafast.dir/src/entities/sri_server.cpp.o
ecuafast: CMakeFiles/ecuafast.dir/src/entities/supercia_server.cpp.o
ecuafast: CMakeFiles/ecuafast.dir/src/main.cpp.o
ecuafast: CMakeFiles/ecuafast.dir/src/port/port_manager.cpp.o
ecuafast: CMakeFiles/ecuafast.dir/src/ship/ship_client.cpp.o
ecuafast: CMakeFiles/ecuafast.dir/build.make
ecuafast: CMakeFiles/ecuafast.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/davidaragundy/ecuafast/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Linking CXX executable ecuafast"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ecuafast.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ecuafast.dir/build: ecuafast
.PHONY : CMakeFiles/ecuafast.dir/build

CMakeFiles/ecuafast.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ecuafast.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ecuafast.dir/clean

CMakeFiles/ecuafast.dir/depend:
	cd /home/davidaragundy/ecuafast/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/davidaragundy/ecuafast /home/davidaragundy/ecuafast /home/davidaragundy/ecuafast/build /home/davidaragundy/ecuafast/build /home/davidaragundy/ecuafast/build/CMakeFiles/ecuafast.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ecuafast.dir/depend

