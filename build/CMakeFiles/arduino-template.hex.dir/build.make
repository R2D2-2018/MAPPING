# CMAKE generated file: DO NOT EDIT!
# Generated by "MSYS Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = "/C/Program Files/CMake/bin/cmake.exe"

# The command to remove a file.
RM = "/C/Program Files/CMake/bin/cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /C/ti-software/R2D2/Build-environment/modules/MAPPING

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /C/ti-software/R2D2/Build-environment/modules/MAPPING/build

# Utility rule file for arduino-template.hex.

# Include the progress variables for this target.
include CMakeFiles/arduino-template.hex.dir/progress.make

CMakeFiles/arduino-template.hex: arduino-template.elf
	arm-none-eabi-objcopy -Oihex arduino-template.elf arduino-template.hex

arduino-template.hex: CMakeFiles/arduino-template.hex
arduino-template.hex: CMakeFiles/arduino-template.hex.dir/build.make

.PHONY : arduino-template.hex

# Rule to build all files generated by this target.
CMakeFiles/arduino-template.hex.dir/build: arduino-template.hex

.PHONY : CMakeFiles/arduino-template.hex.dir/build

CMakeFiles/arduino-template.hex.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/arduino-template.hex.dir/cmake_clean.cmake
.PHONY : CMakeFiles/arduino-template.hex.dir/clean

CMakeFiles/arduino-template.hex.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MSYS Makefiles" /C/ti-software/R2D2/Build-environment/modules/MAPPING /C/ti-software/R2D2/Build-environment/modules/MAPPING /C/ti-software/R2D2/Build-environment/modules/MAPPING/build /C/ti-software/R2D2/Build-environment/modules/MAPPING/build /C/ti-software/R2D2/Build-environment/modules/MAPPING/build/CMakeFiles/arduino-template.hex.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/arduino-template.hex.dir/depend

