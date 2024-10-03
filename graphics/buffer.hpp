#ifndef FCP_BUFFER
#define FCP_BUFFER

#include <glad\glad.h>
#include <vector>
// Generic buffer object that can be bound to a generic target.
// Can be used as a parent class for the other buffer objects.
template <typename T>
class BufferObject
{
  protected:
    GLuint m_id;
    std::vector<T> m_data;
    GLenum m_target;
    
  public:
    BufferObject(GLenum target = 0): m_target{target}
    {
      glGenBuffers(1, &m_id);
    }

    BufferObject(const std::vector<T>& data, GLenum target = 0): m_data{data}, m_target{target}
    { 
      glGenBuffers(1, &m_id);
    }

    ~BufferObject()
    {
      glDeleteBuffers(1, &m_id);
    }

    /*
     * Bind this buffer object to the current OpenGL context.
     */
    void bind() const
    {
      glBindBuffer(m_target, m_id);
    }

    /*
     * Unbind this buffer object from the current OpenGL context.
     */
    void unbind() const
    {
      glBindBuffer(m_target, 0);
    }

    /*
     * Get buffer object's ID.
     */
    GLuint ID() const
    {
      return m_id;
    }

    /*
     * Allocate 'size_of_data' bytes of memory.
     */
    void allocateMemory(GLsizeiptr size_of_data)
    {
      glBufferData(m_target, size_of_data, nullptr, GL_STATIC_DRAW);
    }

    /*
     * Update the buffer's memory.
     */
    void updateMemory(GLintptr from_byte, const std::vector<T>& data)
    {
      glBufferSubData(m_target, from_byte, sizeof(data.data()), &data.data());
    }
};

// Generate 'n' buffer objects
template <typename T>
const std::vector<BufferObject<T>>& genBufferObjects(int n)
{
  std::vector<BufferObject<T>> temp;
  for(int i{ 0 }; i < n; i++)
    temp.push_back(BufferObject());
  return temp;
}

#endif  // FCP_BUFFER