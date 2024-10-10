#ifndef FCPUT_GRAPHICS_BUFFER
#define FCPUT_GRAPHICS_BUFFER

#include "../3rd_party/glad/glad.h"

//#include "error.hpp"

// declare size_t type in order to avoid including entire headers. 
using size_t = decltype(sizeof(0));	// taken from: https://en.cppreference.com/w/cpp/types/size_t

// Generic buffer object that can be bound to a generic target.
// Can be used as a parent class for the other buffer objects.
class BufferObject
{
  protected:
    GLuint m_id;
    GLenum m_target;
    
  public:
    BufferObject(GLenum target = 0);

    ~BufferObject();

		/* Destroy the underlying buffer object.
		 */
		void dispose();
    
    /*
     * Bind this buffer object to the current OpenGL context.
     */
    void bind() const;

    /*
     * Unbind this buffer object from the current OpenGL context.
     */
    void unbind() const;
    
    /*
     * Get buffer object's ID.
     */
    const GLuint& ID() const;

    /*
     * Allocate 'size_of_data' bytes of memory.
     */
		struct allocateMemory_args{
			const void* data;
			GLenum usage;

			// Compiler complains if some kind of constructor is not added for some circularity problem in the logic of the specs.
			allocateMemory_args(): data{nullptr}, usage{GL_STATIC_DRAW} {}
		};
    void allocateMemory(GLsizeiptr size_of_data, const allocateMemory_args args = allocateMemory_args());
    

    /*
     * Update the buffer's memory.
     */
    void updateMemory(const GLintptr& from_byte, const size_t& size_of_data, const void* data);

};

#endif  // FCPUT_GRAPHICS_BUFFER
