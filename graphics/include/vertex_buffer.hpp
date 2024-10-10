#ifndef FCPUT_GRAPHICS_VERTEX_BUFFER
#define FCPUT_GRAPHICS_VERTEX_BUFFER

#include "buffer.hpp"

/* Vertex Array Object.
 *
 * OpenGL buffer object that stores all the required information (state) to supply vertex data. 
 */ 
class VAO
{
  private:
    GLuint m_id;

  public:
    /* Default constructor.
     * 
     * Create a Vertex Array Object.
     */
    VAO();

		/* Default destructor.
		 *
		 * Destroy the Vertex Array Object.
		 */
    ~VAO();

    /* Bind this VAO to the current OpenGL context.
		 *
     * In other words, from now on all subsequent vertex attribute calls will be 
     * stored \ will affect the current VAO. 
     */
    void bind();

    /* Unbind this VAO from the current OpenGL context.
     */
    void unbind();

    /* Get the ID of this VAO.
     */
    const GLuint& ID() const;

};	// end of VAO class.

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
class VBO : public BufferObject
{
  public:

    /* Empty constructor. 
     * 
     * Generate a non-initialized VBO object.
     */
    VBO(): BufferObject(GL_ARRAY_BUFFER) {}

    /* Generate and initialize a VBO object with the given array of vertices.
		 *
     * The default argument 'buffer_usage' can be used to directly specify 
     * any of the following values: STREAM_DRAW, STREAM_READ, STREAM_COPY, 
     * STATIC_DRAW, STATIC_READ, STATIC_COPY, DYNAMIC_DRAW, DYNAMIC_READ, 
     * DYNAMIC_COPY.
     */
    VBO(const size_t& size_of_data, const void* data, const GLenum& buffer_usage = GL_STATIC_DRAW);

    /* Copy constructor.
     *
     * Generate another VBO object with the same stored data as 'other'.
     */
    VBO(const VBO& other, const GLenum& buffer_usage = GL_STATIC_DRAW);
		
    /* Copy the data of another VBO into this.
     */
    VBO& operator=(const VBO& other);

   
		// Optional arguments for copy methods.
		struct copy_args{
			GLintptr read_from;
			GLintptr write_from;
			GLsizeiptr size_data_to_copy;
		
			copy_args(): read_from{0}, write_from{0}, size_data_to_copy{0} {}
		};

   /* Copy the data of the current VBO into another one.
    */
   void copyTo(const VBO& other, const copy_args& args = copy_args());

    /* Copy the data of another VBO into this one.
     */
    void copyFrom(const VBO& other, const copy_args& args = copy_args());

    /* Set VBO data and optionally its usage.
     */
    void setData(const size_t& size_of_data, const void* data, const GLenum& buffer_usage = GL_STATIC_DRAW);

		// Optional arguments for the vertex attribut format method. 
   	struct formatVertexAttribute_args{
			GLenum data_type;
			GLboolean is_normalized;

			formatVertexAttribute_args(): data_type{GL_FLOAT}, is_normalized{GL_FALSE} {}
		};
    
		/* Format vertex attribute.
		 *
     * Format some vertex data in order to set how the vertex shader should interpret it (per vertex attribute).
     */
		void formatVertexAttribute(const GLuint& index, const GLint& number_of_components, const GLsizei& stride, const void* offset, const formatVertexAttribute_args& args = formatVertexAttribute_args());

};	// end of VBO class.

#endif  // FCPUT_GRAPHICS_VERTEX_BUFFER
