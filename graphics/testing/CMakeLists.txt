# CMakeLists.txt for test code
#
# Build all the test files
# test.cpp
add_executable(test test.cpp ${GLAD_SRC})
target_link_libraries(test PUBLIC vbo glfw compiler_flags)
target_include_directories(test PUBLIC ${FCPUT_GRAPHICS_DIR}/include)
set_target_properties(test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FCPUT_GRAPHICS_DIR}/testing)
target_compile_options(test PRIVATE -ggdb)

# triangle_test.cpp
add_executable(triangle triangle_test.cpp ${GLAD_SRC})
target_link_libraries(triangle PUBLIC vbo glfw compiler_flags)
target_include_directories(test PUBLIC ${FCPUT_GRAPHICS_DIR}/include)
set_target_properties(triangle PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${FCPUT_GRAPHICS_DIR}/testing)
