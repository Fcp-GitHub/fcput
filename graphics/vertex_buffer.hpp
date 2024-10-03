#ifndef FCP_VERTEX_BUFFER
#define FCP_VERTEX_BUFFER

#include "buffer.hpp"

#include <vector>

/*
 * Vertex Array Object.
 *
 * OpenGL buffer object that stores all the required information (state) to supply vertex data. 
 */ 
class VAO
{
  private:
    GLuint m_id;

  public:
    /*
     * Default constructor.
     * 
     * Create a Vertex Array Object.
     */
    VAO()
    {
      glGenVertexArrays(1, &m_id);
    }

    /*
     * Bind this VAO to the current OpenGL context.
     * In other words, from now on all subsequent vertex attribute calls will be 
     * stored / will affect the current VAO. 
     */
    void bind()
    {
      glBindVertexArray(m_id);
    }

    /*
     * Unbind this VAO from the current OpenGL context.
     */
    void unbind()
    {
      glBindVertexArray(0);
    }

    /*
     * Get the ID of this VAO.
     */
    GLuint ID()
    {
      return m_id;
    }

    ~VAO()
    {
      glDeleteVertexArrays(1, &m_id);
    }
};

/* Vertex Buffer Object (VBO).
 *
 * OpenGL's buffer object used to store a number of vertices directly in the GPU's memory.
 * This is done via a number of methods that are implemented for this class, but every operation
 * will have effect on this VBO *only if* it was correctly bound beforehand. Refer to the explanations 
 * of the different methods to know how to use it.
 * 
 * Technically, VBOs offer a substantial increase in performance compared with the old OpenGL's 
 * 'immediate rendering mode'.
 */
template <typename T>
class VBO : public BufferObject<T>
{
  public:
    /*
     * Empty constructor. 
     * 
     * Generate a non-initialized VBO object.
     */
    VBO(): BufferObject<T>(GL_ARRAY_BUFFER) {}

    /*
     * Generate and initialize a VBO object with the given array of vertices.
     * The default argument 'buffer_usage' can be used to directly specify 
     * any of the following values: STREAM_DRAW, STREAM_READ, STREAM_COPY, 
     * STATIC_DRAW, STATIC_READ, STATIC_COPY, DYNAMIC_DRAW, DYNAMIC_READ, 
     * DYNAMIC_COPY.
     */
    VBO(const std::vector<T>& data, GLenum buffer_usage = GL_STATIC_DRAW): BufferObject<T>(data, GL_ARRAY_BUFFER)
    {
      this->bind();
      glBufferData(this->m_target, data.size() * sizeof(T), &data.front(), buffer_usage);
      this->unbind();  // Allow code like: 'vbo1 = VBO(data);' to be possible without breaking the state machine with dangling bindings.
    }

    /*
     * Copy constructor.
     *
     * Generate another VBO object with the same stored data as 'other'.
     */
    VBO(const VBO<T>& other, GLenum buffer_usage = GL_STATIC_DRAW): BufferObject<T>(other.m_data, GL_ARRAY_BUFFER)
    {
      this->bind();
      glBufferData(this->m_target, this->m_data.size() * sizeof(T), &this->m_data.front(), buffer_usage);
      this->unbind();  // Allow code like: 'vbo1 = VBO(data);' to be possible without breaking the state machine with dangling bindings.
    }

    /*
     * Copy the data of another VBO into this.
     *
     * If the left buffer is empty it needs to be bound before using this operator!
     * If the left buffer is not empty it is not mandatory to bind it before using this operator.
     * 
     * At the end of its operations this operator leaves the left buffer bound to GL_ARRAY_BUFFER!
     */
    VBO& operator= (const VBO<T>& other)
    {
      if (this == &other) return *this;
      
      if (this->m_data.empty())
      {
        // The user must have bound the buffer object before.
        glBufferData(this->m_target, other.m_data.size() * sizeof(T), &other.m_data.front(), GL_STATIC_DRAW);
      } else {
        glBindBuffer(GL_COPY_READ_BUFFER, other.m_id);
        glBindBuffer(GL_COPY_WRITE_BUFFER, this->m_id);
        glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, other.m_data.size() * sizeof(T));
        this->bind(); // assuming that the VBO was bound before the call to this method
      }

      return *this;
    }

    /*
     * Copy the data of the current VBO into another one.
     *
     * At the end of this method neither of the two employed buffer objects are bound to the GL_ARRAY_BUFFER target.
     */
    void copyTo(const VBO<T>& other, GLintptr read_from = 0, GLintptr write_from = 0, GLsizeiptr size_of_data = 0)
    {
      if (this == &other)
        return;

      if (size_of_data == 0)
        size_of_data = this->m_data.size() * sizeof(T);

      glBindBuffer(GL_COPY_READ_BUFFER, this->m_id);
      glBindBuffer(GL_COPY_WRITE_BUFFER, other.m_id);
      glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, read_from, write_from, size_of_data);
      return;
    }

    /*
     * Copy the data of another VBO into this one.
     *
     * At the end of this method neither of the two employed buffer objects are bound to the GL_ARRAY_BUFFER target.
     */
    void copyFrom(const VBO<T>& other, GLintptr read_from = 0, GLintptr write_from = 0, GLsizeiptr size_of_data = 0)
    {
      if (this == &other)
        return;
        
      if (size_of_data == 0)
        size_of_data = other.m_data.size() * sizeof(T);

      glBindBuffer(GL_COPY_READ_BUFFER, other.m_id);
      glBindBuffer(GL_COPY_WRITE_BUFFER, this->m_id);
      glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, read_from, write_from, size_of_data);
      return;
    }

    /*
     * Set VBO data and optionally its usage.
     *
     * The buffer has to be bound before this operation!
     */
    void setData(const std::vector<T>& data, GLenum buffer_usage = GL_STATIC_DRAW)
    {
      this->m_data = data;
      glBufferData(this->m_target, data.size() * sizeof(T), &data.front(), buffer_usage);
    }

    /*
     * Format some vertex data in order to set how the vertex shader should interpret it (per vertex attribute).
     *
     * The buffer has to be bound before this operation!
     */
    void formatVertexAttribute(GLuint index, GLint number_of_components, GLenum data_type, GLboolean is_normalized, GLsizei stride, const void* offset)
    {
      glVertexAttribPointer(index, number_of_components, data_type, is_normalized, stride, (void*)(offset));
      glEnableVertexAttribArray(index);
    }

    /*
     * Bind this buffer object to the current OpenGL context.
     */
    void bind() const
    {
      GLint currentlyBoundVBO; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentlyBoundVBO);
      if (currentlyBoundVBO != this->m_id)  // avoid binding repetition.
        BufferObject<T>::bind();
    }

    /*
     * Unbind this buffer object from the current OpenGL context.
     */
    void unbind() const
    {
      GLint currentlyBoundVBO; glGetIntegerv(GL_ARRAY_BUFFER_BINDING, &currentlyBoundVBO);
      if (currentlyBoundVBO == this->m_id)  // avoid unbinding repetition.
        BufferObject<T>::unbind();
    }

    /*
     * Get the data that is currently stored in the buffer.
     *
     * The buffer needs not to be bound before calling this method.
     */
    std::vector<T> getData() const
    {
      return this->m_data;
    }
};

#endif  // FCP_VERTEX_BUFFER