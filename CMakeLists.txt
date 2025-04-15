# Computational top CMakeLists.txt
#
# Add the libraries to be built.
cmake_minimum_required(VERSION 3.10)

project(
	computational
	DESCRIPTION "Utilities for computational tasks (mesh generation, math, ODE solvers, ...)"
	LANGUAGES C CXX
)

# Check if top level.
if(PROJECT_IS_TOP_LEVEL)
	# Support folders in IDEs.
	set_property(GLOBAL PROPERTY USE_FOLDERS ON)

	# Enable docs generation.
	find_package(Doxygen)
	if(Doxygen_FOUND)
		add_subdirectory(docs)
	else()
		message(STATUS "Doxygen not found, documentation won't be built.")
	endif()
endif()

# Remember current working directory.
set(FCPUT_COMPUTATIONAL_DIR ${CMAKE_CURRENT_LIST_DIR})

# Add requirements and features
add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_17)

# Add 'mesh' subdirectory.
add_subdirectory(mesh)
# Add 'der_diff' subdirectory.
add_subdirectory(der_diff)

# Add subdirectory for testing.
add_subdirectory(testing)
