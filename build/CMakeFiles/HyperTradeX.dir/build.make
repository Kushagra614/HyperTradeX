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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/build"

# Include any dependencies generated for this target.
include CMakeFiles/HyperTradeX.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/HyperTradeX.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/HyperTradeX.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/HyperTradeX.dir/flags.make

CMakeFiles/HyperTradeX.dir/src/main.cpp.o: CMakeFiles/HyperTradeX.dir/flags.make
CMakeFiles/HyperTradeX.dir/src/main.cpp.o: /mnt/d/ME/Work/Codeverse/Coding/C++/Projects\ C++/HyperTradeX/src/main.cpp
CMakeFiles/HyperTradeX.dir/src/main.cpp.o: CMakeFiles/HyperTradeX.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/HyperTradeX.dir/src/main.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HyperTradeX.dir/src/main.cpp.o -MF CMakeFiles/HyperTradeX.dir/src/main.cpp.o.d -o CMakeFiles/HyperTradeX.dir/src/main.cpp.o -c "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/main.cpp"

CMakeFiles/HyperTradeX.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HyperTradeX.dir/src/main.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/main.cpp" > CMakeFiles/HyperTradeX.dir/src/main.cpp.i

CMakeFiles/HyperTradeX.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HyperTradeX.dir/src/main.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/main.cpp" -o CMakeFiles/HyperTradeX.dir/src/main.cpp.s

CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.o: CMakeFiles/HyperTradeX.dir/flags.make
CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.o: /mnt/d/ME/Work/Codeverse/Coding/C++/Projects\ C++/HyperTradeX/src/binance/binance_api.cpp
CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.o: CMakeFiles/HyperTradeX.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.o -MF CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.o.d -o CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.o -c "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/binance/binance_api.cpp"

CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/binance/binance_api.cpp" > CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.i

CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/binance/binance_api.cpp" -o CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.s

CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.o: CMakeFiles/HyperTradeX.dir/flags.make
CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.o: /mnt/d/ME/Work/Codeverse/Coding/C++/Projects\ C++/HyperTradeX/src/binance/binance_ws_client.cpp
CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.o: CMakeFiles/HyperTradeX.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.o -MF CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.o.d -o CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.o -c "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/binance/binance_ws_client.cpp"

CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/binance/binance_ws_client.cpp" > CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.i

CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/binance/binance_ws_client.cpp" -o CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.s

CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.o: CMakeFiles/HyperTradeX.dir/flags.make
CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.o: /mnt/d/ME/Work/Codeverse/Coding/C++/Projects\ C++/HyperTradeX/src/websocket/websocket_server.cpp
CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.o: CMakeFiles/HyperTradeX.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.o -MF CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.o.d -o CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.o -c "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/websocket/websocket_server.cpp"

CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/websocket/websocket_server.cpp" > CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.i

CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/websocket/websocket_server.cpp" -o CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.s

CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.o: CMakeFiles/HyperTradeX.dir/flags.make
CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.o: /mnt/d/ME/Work/Codeverse/Coding/C++/Projects\ C++/HyperTradeX/src/models/orderbook.cpp
CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.o: CMakeFiles/HyperTradeX.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.o -MF CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.o.d -o CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.o -c "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/models/orderbook.cpp"

CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/models/orderbook.cpp" > CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.i

CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/models/orderbook.cpp" -o CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.s

CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.o: CMakeFiles/HyperTradeX.dir/flags.make
CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.o: /mnt/d/ME/Work/Codeverse/Coding/C++/Projects\ C++/HyperTradeX/src/utils/logger.cpp
CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.o: CMakeFiles/HyperTradeX.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.o -MF CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.o.d -o CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.o -c "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/utils/logger.cpp"

CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/utils/logger.cpp" > CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.i

CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/utils/logger.cpp" -o CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.s

CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.o: CMakeFiles/HyperTradeX.dir/flags.make
CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.o: /mnt/d/ME/Work/Codeverse/Coding/C++/Projects\ C++/HyperTradeX/src/utils/config.cpp
CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.o: CMakeFiles/HyperTradeX.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir="/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.o -MF CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.o.d -o CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.o -c "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/utils/config.cpp"

CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/utils/config.cpp" > CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.i

CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/src/utils/config.cpp" -o CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.s

# Object files for target HyperTradeX
HyperTradeX_OBJECTS = \
"CMakeFiles/HyperTradeX.dir/src/main.cpp.o" \
"CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.o" \
"CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.o" \
"CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.o" \
"CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.o" \
"CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.o" \
"CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.o"

# External object files for target HyperTradeX
HyperTradeX_EXTERNAL_OBJECTS =

HyperTradeX: CMakeFiles/HyperTradeX.dir/src/main.cpp.o
HyperTradeX: CMakeFiles/HyperTradeX.dir/src/binance/binance_api.cpp.o
HyperTradeX: CMakeFiles/HyperTradeX.dir/src/binance/binance_ws_client.cpp.o
HyperTradeX: CMakeFiles/HyperTradeX.dir/src/websocket/websocket_server.cpp.o
HyperTradeX: CMakeFiles/HyperTradeX.dir/src/models/orderbook.cpp.o
HyperTradeX: CMakeFiles/HyperTradeX.dir/src/utils/logger.cpp.o
HyperTradeX: CMakeFiles/HyperTradeX.dir/src/utils/config.cpp.o
HyperTradeX: CMakeFiles/HyperTradeX.dir/build.make
HyperTradeX: CMakeFiles/HyperTradeX.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir="/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_8) "Linking CXX executable HyperTradeX"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/HyperTradeX.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/HyperTradeX.dir/build: HyperTradeX
.PHONY : CMakeFiles/HyperTradeX.dir/build

CMakeFiles/HyperTradeX.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/HyperTradeX.dir/cmake_clean.cmake
.PHONY : CMakeFiles/HyperTradeX.dir/clean

CMakeFiles/HyperTradeX.dir/depend:
	cd "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX" "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX" "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/build" "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/build" "/mnt/d/ME/Work/Codeverse/Coding/C++/Projects C++/HyperTradeX/build/CMakeFiles/HyperTradeX.dir/DependInfo.cmake" "--color=$(COLOR)"
.PHONY : CMakeFiles/HyperTradeX.dir/depend

