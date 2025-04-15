# Mesh module's CMakeLists.txt
#
# Generate meshing libraries.

# Single header files.

# Error library
add_library(errors INTERFACE)
target_include_directories(errors INTERFACE include)
target_link_libraries(errors INTERFACE compiler_flags)

# Grid.
add_library(grid INTERFACE)
target_include_directories(grid INTERFACE include)
target_link_libraries(grid INTERFACE errors compiler_flags)
