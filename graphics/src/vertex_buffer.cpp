#include "../include/vertex_buffer.hpp"

/* VAO IMPLEMENTATION
 *******************************************************************************
 */
VAO::VAO()
{
	glGenVertexArrays(1, &m_id);
}

void VAO::bind()
{
	glBindVertexArray(m_id);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}

GLuint VAO::ID()
{
	return m_id;
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &m_id);
}

/* VBO IMPLEMENTATION
 *******************************************************************************
 */
