#include <GLFW\glfw3.h>
#include <map>
#include <string>

class Context
{
  private:
    GLFWwindow* m_WindowHandles;  // array of window handles
    std::map<std::string,GLuint*> m_SavedBuffers; // if requested, save and map buffer objects by their type and IDs

  public:
    Context();  // initialize context
    ~Context(); // terminate context
    void WindowHint(int, int);  // set window hint
    void FramebufferSizeCallback(GLFWwindow, GLFWframebuffersizefun);
    // ... callback functions setters
    void Enable(GLenum);  // glEnable()
    void ProcessInput(GLFWwindow);
    void SetClearColor(GLfloat, GLfloat, GLfloat, GLfloat); // glClearColor()
    void SetClearDepth(GLdouble); // glClearDepth()
    void SetClearStencil(GLint); // glClearStencil()
    void ClearBuffers(GLbitfield); // glClear()
    void SwapBuffers(GLFWwindow); // glfwSwapBuffers()
    void PollEvents(void);  // glfwPollEvents()
};