# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.26

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
CMAKE_COMMAND = "C:/Users/Gabriel Luan/Desktop/cmake/bin/cmake.exe"

# The command to remove a file.
RM = "C:/Users/Gabriel Luan/Desktop/cmake/bin/cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:/Users/Gabriel Luan/Desktop/Projects/numeric_integration"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:/Users/Gabriel Luan/Desktop/Projects/numeric_integration/build"

# Include any dependencies generated for this target.
include CMakeFiles/numeric_integration.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/numeric_integration.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/numeric_integration.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/numeric_integration.dir/flags.make

CMakeFiles/numeric_integration.dir/main.c.obj: CMakeFiles/numeric_integration.dir/flags.make
CMakeFiles/numeric_integration.dir/main.c.obj: C:/Users/Gabriel\ Luan/Desktop/Projects/numeric_integration/main.c
CMakeFiles/numeric_integration.dir/main.c.obj: CMakeFiles/numeric_integration.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:/Users/Gabriel Luan/Desktop/Projects/numeric_integration/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/numeric_integration.dir/main.c.obj"
	C:/ProgramData/chocolatey/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/numeric_integration.dir/main.c.obj -MF CMakeFiles/numeric_integration.dir/main.c.obj.d -o CMakeFiles/numeric_integration.dir/main.c.obj -c "C:/Users/Gabriel Luan/Desktop/Projects/numeric_integration/main.c"

CMakeFiles/numeric_integration.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/numeric_integration.dir/main.c.i"
	C:/ProgramData/chocolatey/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "C:/Users/Gabriel Luan/Desktop/Projects/numeric_integration/main.c" > CMakeFiles/numeric_integration.dir/main.c.i

CMakeFiles/numeric_integration.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/numeric_integration.dir/main.c.s"
	C:/ProgramData/chocolatey/bin/gcc.exe $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "C:/Users/Gabriel Luan/Desktop/Projects/numeric_integration/main.c" -o CMakeFiles/numeric_integration.dir/main.c.s

# Object files for target numeric_integration
numeric_integration_OBJECTS = \
"CMakeFiles/numeric_integration.dir/main.c.obj"

# External object files for target numeric_integration
numeric_integration_EXTERNAL_OBJECTS =

numeric_integration.exe: CMakeFiles/numeric_integration.dir/main.c.obj
numeric_integration.exe: CMakeFiles/numeric_integration.dir/build.make
numeric_integration.exe: CMakeFiles/numeric_integration.dir/linkLibs.rsp
numeric_integration.exe: CMakeFiles/numeric_integration.dir/objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:/Users/Gabriel Luan/Desktop/Projects/numeric_integration/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable numeric_integration.exe"
	"C:/Users/Gabriel Luan/Desktop/cmake/bin/cmake.exe" -E rm -f CMakeFiles/numeric_integration.dir/objects.a
	C:/ProgramData/chocolatey/bin/ar.exe qc CMakeFiles/numeric_integration.dir/objects.a @CMakeFiles/numeric_integration.dir/objects1.rsp
	C:/ProgramData/chocolatey/bin/gcc.exe -g -Wl,--whole-archive CMakeFiles/numeric_integration.dir/objects.a -Wl,--no-whole-archive -o numeric_integration.exe -Wl,--out-implib,libnumeric_integration.dll.a -Wl,--major-image-version,0,--minor-image-version,0 @CMakeFiles/numeric_integration.dir/linkLibs.rsp

# Rule to build all files generated by this target.
CMakeFiles/numeric_integration.dir/build: numeric_integration.exe
.PHONY : CMakeFiles/numeric_integration.dir/build

CMakeFiles/numeric_integration.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/numeric_integration.dir/cmake_clean.cmake
.PHONY : CMakeFiles/numeric_integration.dir/clean

CMakeFiles/numeric_integration.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "C:/Users/Gabriel Luan/Desktop/Projects/numeric_integration" "C:/Users/Gabriel Luan/Desktop/Projects/numeric_integration" "C:/Users/Gabriel Luan/Desktop/Projects/numeric_integration/build" "C:/Users/Gabriel Luan/Desktop/Projects/numeric_integration/build" "C:/Users/Gabriel Luan/Desktop/Projects/numeric_integration/build/CMakeFiles/numeric_integration.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/numeric_integration.dir/depend

