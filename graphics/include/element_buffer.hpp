#ifndef FCPUT_GRAPHICS_ELEMENT_BUFFER
#define FCPUT_GRAPHICS_ELEMENT_BUFFER

#include "buffer.hpp"

#include <vector>

/* Element Buffer Object (EBO).
 *
 * OpenGL's buffer object used to store a number of vertex indices directly in the GPU's memory.
 * This is done via a number of methods that are implemented for this class, but every operation
 * will have effect on this VBO *only if* it was correctly bound beforehand. Refer to the explanations 
 * of the different methods to know how to use it.
 * 
 * 'Indexed rendering' offers a substantial increase in performance in some situations compared with the 
 * so-called 'vertex rendering'.
 */
template <typename T>
class EBO : public BufferObject<T>
{
  public:
    /*
     * Empty constructor. 
     * 
     * Generate a non-initialized VBO object.
     */
    EBO(): BufferObject<T>(GL_ELEMENT_ARRAY_BUFFER) {}

    /*
     * Generate and initialize an EBO object with the given array of indices.
     * The default argument 'buffer_usage' can be used to directly specify 
     * any of the following values: STREAM_DRAW, STREAM_READ, STREAM_COPY, 
     * STATIC_DRAW, STATIC_READ, STATIC_COPY, DYNAMIC_DRAW, DYNAMIC_READ, 
     * DYNAMIC_COPY.
     */
    EBO(const std::vector<T>& data, GLenum buffer_usage = GL_STATIC_DRAW): BufferObject<T>(data, GL_ELEMENT_ARRAY_BUFFER)
    {
      this->bind();
      glBufferData(this->m_target, data.size() * sizeof(T), &data.front(), buffer_usage);
      this->unbind();  // Allow code like: 'ebo1 = EBO(data);' to be possible without breaking the state machine with dangling bindings.
    }

    /*
     * Copy constructor.
     *
     * Generate another EBO object with the same stored data as 'other'.
     */
    EBO(const EBO<T>& other, GLenum buffer_usage = GL_STATIC_DRAW): BufferObject<T>(other.m_data, GL_ELEMENT_ARRAY_BUFFER)
    {
      this->bind();
      glBufferData(this->m_target, this->m_data.size() * sizeof(T), &this->m_data.front(), buffer_usage);
      this->unbind();  // Allow code like: 'ebo1 = EBO(data);' to be possible without breaking the state machine with dangling bindings.    
    }

    /*
     * Copy the data of another EBO into this.
     *
     * If the left buffer is empty it needs to be bound before using this operator!
     * If the left buffer is not empty it is not mandatory to bind it before using this operator.
     * 
     * At the end of its operations this operator leaves the left buffer bound to GL_ELEMENT_ARRAY_BUFFER!
     */
    EBO& operator= (const EBO<T>& other)
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
     * Copy the data of the current EBO into another one.
     *
     * At the end of this method neither of the two employed buffer objects are bound to the GL_ELEMENT_ARRAY_BUFFER target.
     */
    void copyTo(const EBO<T>& other, GLintptr read_from = 0, GLintptr write_from = 0, GLsizeiptr size_of_data = 0)
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
     * Copy the data of another EBO into this one.
     *
     * At the end of this method neither of the two employed buffer objects are bound to the GL_ELEMENT_ARRAY_BUFFER target.
     */
    void copyFrom(const EBO<T>& other, GLintptr read_from = 0, GLintptr write_from = 0, GLsizeiptr size_of_data = 0)
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
     * Set EBO data and optionally its usage.
     *
     * The buffer has to be bound before this operation!
     */
    void setData(const std::vector<T>& data, GLenum buffer_usage = GL_STATIC_DRAW)
    {
      this->m_data = data;
      glBufferData(this->m_target, data.size() * sizeof(T), &data.front(), buffer_usage);
    }

    /*
     * Bind this buffer object to the current OpenGL context.
     */
    void bind() const
    {
      GLint currentlyBoundEBO; glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentlyBoundEBO);
      if (currentlyBoundEBO != this->m_id)  // avoid binding repetition.
        BufferObject<T>::bind();
    }

    /*
     * Unbind this buffer object from the current OpenGL context.
     */
    void unbind() const
    {
      GLint currentlyBoundEBO; glGetIntegerv(GL_ELEMENT_ARRAY_BUFFER_BINDING, &currentlyBoundEBO);
      if (currentlyBoundEBO == this->m_id)  // avoid unbinding repetition.
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

#endif	// FCPUT_GRAPHICS_ELEMENT_BUFFER
