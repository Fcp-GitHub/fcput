# CMakeLists.txt for test code
#
# Build all the test files

# test.cpp
add_executable(test test.cpp ${GLAD_SRC})
target_link_libraries(test PUBLIC vbo glfw)# compile_flags)
target_include_directories(test PUBLIC "${PROJECT_CURRENT_BINARY_DIR}")
set_target_properties(test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FCPUT_GRAPHICS_DIR}/testing)

# triangle_test.cpp
add_executable(triangle triangle_test.cpp ${GLAD_SRC})
target_link_libraries(triangle PUBLIC vbo glfw)# compile_flags)
target_include_directories(triangle PUBLIC "${PROJECT_CURRENT_BINARY_DIR}")
set_target_properties(triangle PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FCPUT_GRAPHICS_DIR}/testing)
