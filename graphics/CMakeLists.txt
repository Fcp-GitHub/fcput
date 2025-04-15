# Graphics top CMakeLists.txt
#
# Add the libraries to be built.
cmake_minimum_required(VERSION 3.10)

project(
	graphics
	DESCRIPTION "Utilities for graphical tasks (color space conversions, mesh rendering, ...)"
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
set(FCPUT_GRAPHICS_DIR ${CMAKE_CURRENT_LIST_DIR})

# Add requirements and features
add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_17)

# Source and header files.

# Generic buffer header
add_library(buffer src/buffer.cpp)
target_include_directories(buffer INTERFACE include)
target_link_libraries(buffer PUBLIC compiler_flags)

# VAO and VBO
add_library(vbo src/vertex_buffer.cpp)
target_include_directories(vbo INTERFACE include)
target_link_libraries(vbo PUBLIC buffer compiler_flags)

# EBO
add_library(ebo src/element_buffer.cpp)
target_include_directories(ebo INTERFACE include)
target_link_libraries(ebo PUBLIC buffer compiler_flags)


# Single header files.

# Mesh
add_library(mesh INTERFACE)
target_include_directories(mesh INTERFACE include)
target_link_libraries(mesh INTERFACE compiler_flags)

# Error library
add_library(errors INTERFACE)
target_include_directories(errors INTERFACE include)
target_link_libraries(errors INTERFACE compiler_flags)

# Third party libraries.

# GLFW
# This needs some proper work in order to make use of already existing GLFW's CMake scripts.

# Set some cached GLFW's configuration variables.
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "Build GLFW example files")
set(GLFW_BUILD_TESTS OFF CACHE BOOL "Build GLFW test files")
set(GLFW_BUILD_DOCS OFF CACHE BOOL "Build GLFW docs")
set(GLFW_INSTALL OFF CACHE BOOL "Install GLFW")

# Variables used to configure GLAD.
set(GLAD_INCLUDE_DIR "")	# set where to get GLAD's include files.
set(GLAD_SRC "")	# set where to get GLAD's source files.

# Execute GLFW's CMake scripts.
add_subdirectory(3rd_party/glfw)

# Make the user choose whether to use GLFW's GLAD or the one he has installed.
option(FCPUT_USE_GLFW_GLAD "Use GLFW's version of GLAD" OFF)

if(FCPUT_USE_GLFW_GLAD)
	# GLFW uses the header-only version of GLAD.
	set(GLAD_INCLUDE_DIR "${GLFW_SOURCE_DIR}/deps/glad/gl.h")
	set(GLAD_SRC "INTERFACE")
else()
	set(GLAD_INCLUDE_DIR "3rd_party/glad")
	set(GLAD_SRC "3rd_party/glad/src/glad.c")
endif()

# GLAD
add_library(glad ${GLAD_SRC})
target_include_directories(glad INTERFACE ${GLAD_INCLUDE_DIR})
# Redefine GLAD_SRC in order to reuse the same variable in testing scripts.
if(FCPUT_USE_GLFW_GLAD)
	set(GLAD_SRC "")	# don't add anything to compilation if header-only option has been chosen.
else()
	set(GLAD_SRC "${CMAKE_CURRENT_LIST_DIR}/3rd_party/glad/src/glad.c")	# set to full path.
endif()


# Subdirectory for testing
add_subdirectory(testing)
