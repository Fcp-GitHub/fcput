#include "../include/vertex_buffer.hpp"
#include "../3rd_party/glfw/include/GLFW/glfw3.h"

#include <iostream>

int init();

// need an OpenGL context to begin testing...
int main(void)
{
  std::cout << init() << '\n';
  
  float data[] = {1.4, 1.5, 1.6};
  std::cout << "here\n";
  VBO<double> vbo; 
  std::cout << "here\n";
  std::cout << "vbo ID: " << vbo.ID() << '\n';
  
  glfwTerminate();
  return 0;
}

int init()
{
  // Initialize GLFW.
    glfwInit();
    // GLFW hints for context and window object.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Window object.
    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        // Error check.
        std::cerr << "Failed to create GLFW window." << std::endl;
        glfwTerminate();
        return -1;
    }
    // Make the context of the 'window' window the OpenGL_main context in the current thread.
    glfwMakeContextCurrent(window);

    // Load function pointers for OpenGL with GLAD.
    if (!gladLoadGLLoader( (GLADloadproc)glfwGetProcAddress ) )
    {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        glfwTerminate();
        return -1;
    }

    return 0;
}
