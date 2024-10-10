#ifndef FCPUT_GRAPHICS_ELEMENT_BUFFER
#define FCPUT_GRAPHICS_ELEMENT_BUFFER

#include "buffer.hpp"

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
class EBO : public BufferObject
{
  public:

    /* Empty constructor. 
     * 
     * Generate a non-initialized VBO object.
     */
    EBO(): BufferObject(GL_ELEMENT_ARRAY_BUFFER) {}

    /* Generate and initialize an EBO object with the given array of indices.
		 *
     * The default argument 'buffer_usage' can be used to directly specify 
     * any of the following values: STREAM_DRAW, STREAM_READ, STREAM_COPY, 
     * STATIC_DRAW, STATIC_READ, STATIC_COPY, DYNAMIC_DRAW, DYNAMIC_READ, 
     * DYNAMIC_COPY.
     */
    EBO(const size_t& size_of_data, const void* data, const GLenum& buffer_usage = GL_STATIC_DRAW);
		
    /* Copy constructor.
     *
     * Generate another EBO object with the same stored data as 'other'.
     */
    EBO(const EBO& other, const GLenum& buffer_usage = GL_STATIC_DRAW);

    /* Copy the data of another EBO into this.
     */
    EBO& operator=(const EBO& other);
    
		// Forward declaration (avoid possible compilation errors).
		struct copy_args;
#ifndef FCPUT_GRAPHICS_VERTEX_BUFFER
		// Optional arguments for copy methods.
		struct copy_args{
			GLintptr read_from;
			GLintptr write_from;
			GLsizeiptr size_data_to_copy;

			copy_args(): read_from{0}, write_from{0}, size_data_to_copy{0} {}
		};
#endif

    /* Copy the data of the current EBO into another one.
     */
    void copyTo(const EBO& other, const copy_args& args = copy_args());

    /* Copy the data of another EBO into this one.
     */
    void copyFrom(const EBO& other, const copy_args& args = copy_args());

    /* Set EBO data and optionally its usage.
     */
    void setData(const size_t& size_of_data, const void* data, const GLenum& buffer_usage = GL_STATIC_DRAW);

};	// end of EBO class.

#endif	// FCPUT_GRAPHICS_ELEMENT_BUFFER
