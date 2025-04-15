# Top most CMakeLists.txt
#
# Configures global project, adds subdirectories 

# For now this the makefiles are just for TESTING!
# With the actual version 1.0 some complete CMakeFiles.txt will come.

cmake_minimum_required(VERSION 3.10)
project(fcput
		LANGUAGES CXX C)	

# Make sure that OpenGL basic libraries are found.
find_package(OpenGL REQUIRED)

# Add requirements and features (better to define them in single subdirectories).
#add_library(compiler_flags INTERFACE)
#target_compile_features(compiler_flags INTERFACE cxx_std_17)

add_subdirectory(graphics)	# Name of subproject 1
add_subdirectory(computational)	# Name of subproject 2
