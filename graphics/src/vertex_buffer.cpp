#include "../include/vertex_buffer.hpp"
/* VAO IMPLEMENTATION
 *******************************************************************************
 */
VAO::VAO()
{
	glGenVertexArrays(1, &m_id);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &m_id);
}

void VAO::bind()
{
	glBindVertexArray(m_id);
}

void VAO::unbind()
{
	glBindVertexArray(0);
}

const GLuint& VAO::ID() const
{
	return m_id;
}

/* VBO IMPLEMENTATION
 *******************************************************************************
 */
VBO::VBO(const size_t& size_of_data, const void* data, const GLenum& buffer_usage): BufferObject(GL_ARRAY_BUFFER)
{
	this->bind();
	glBufferData(this->m_target, size_of_data, data, buffer_usage);
	this->unbind();  // Allow code like: 'vbo1 = VBO(data);' to be possible without breaking the state machine with dangling bindings.
}

VBO::VBO(const VBO& other, const GLenum& buffer_usage): BufferObject(GL_ARRAY_BUFFER)
{
	// Get size of data of the other VBO object.
	other.bind();
	int size_of_other;	// for simplicity, now handle only max to 4 GiB size (GL <3.2), but remember to complete this. (see here: https://stackoverflow.com/a/22078021)
	glGetBufferParameteriv(other.m_target, GL_BUFFER_SIZE, &size_of_other);

	// Allocate enough memory.
	this->bind();
	this->allocateMemory(size_of_other);
	// Copy this VBO with the other one.
	*this = other;
	// Unbind this VBO since it is the user that must specify when to bind the current object before using it for user-specific operations.
	this->unbind();
}

VBO& VBO::operator=(const VBO& other)
{
	if (this == &other) return *this;

	//note: add "if empty" check
	other.bind();
	int size_of_other;
	glGetBufferParameteriv(other.m_target, GL_BUFFER_SIZE, &size_of_other);

	this->bind();
	glBindBuffer(GL_COPY_READ_BUFFER, other.m_id);
	glBindBuffer(GL_COPY_WRITE_BUFFER, this->m_id);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, 0, 0, size_of_other);
	this->unbind();

	return *this;
}

void VBO::copyTo(const VBO& other, const copy_args& args)
{
	if (this == &other)	return;

	int size_data_to_copy = args.size_data_to_copy;
	// if 0 defaults to copy everything.
	if (size_data_to_copy == 0)
	{
		this->bind();
		glGetBufferParameteriv(this->m_target, GL_BUFFER_SIZE, &size_data_to_copy);
	}

	glBindBuffer(GL_COPY_READ_BUFFER, this->m_id);
	glBindBuffer(GL_COPY_WRITE_BUFFER, other.m_id);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, args.read_from, args.write_from, size_data_to_copy);

	return;
}

void VBO::copyFrom(const VBO& other, const copy_args& args)
{
	if (this == &other) return;

	int size_data_to_copy = args.size_data_to_copy;
	// if 0 defaults to copy everything.
	if (size_data_to_copy == 0)
	{
		other.bind();
		glGetBufferParameteriv(other.m_target, GL_BUFFER_SIZE, &size_data_to_copy);
	}

	glBindBuffer(GL_COPY_READ_BUFFER, other.m_id);
	glBindBuffer(GL_COPY_WRITE_BUFFER, this->m_id);
	glCopyBufferSubData(GL_COPY_READ_BUFFER, GL_COPY_WRITE_BUFFER, args.read_from, args.write_from, size_data_to_copy);

	return;
}

void VBO::setData(const size_t& size_of_data, const void* data, const GLenum& buffer_usage)
{
	this->bind();
	glBufferData(this->m_target, size_of_data, data, buffer_usage);
	this->unbind();

	return;
}

void VBO::formatVertexAttribute(const GLuint& index, const GLint& number_of_components, const GLsizei& stride, const void* offset, const formatVertexAttribute_args& args)
{
	glVertexAttribPointer(index, number_of_components, args.data_type, args.is_normalized, stride, (void*)offset);
	glEnableVertexAttribArray(index);
}
