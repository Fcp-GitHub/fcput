#include "../include/buffer.hpp"
#include "../include/error.hpp"

BufferObject::BufferObject(GLenum target): m_target{target}
{
	glGenBuffers(1, &m_id);
}

BufferObject::~BufferObject()
{
	// This should not be here, RAII cannot be used fully for OpenGL.
	//glDeleteBuffers(1, &m_id);
}

void BufferObject::dispose()
{
	if (m_id != 0)
		glDeleteBuffers(1, &m_id);
}

void BufferObject::bind() const
{
	if (m_id != 0)
		glBindBuffer(m_target, m_id);
	else throw fcp::bad_binding_error();
}

void BufferObject::unbind() const
{
	glBindBuffer(m_target, 0);
}

const GLuint& BufferObject::ID() const
{
	return m_id;
}

void BufferObject::allocateMemory(GLsizeiptr size_of_data, const allocateMemory_args args)
{
	if (m_id != 0)
		glBufferData(m_target, size_of_data, args.data, args.usage);
	else throw fcp::bad_binding_error();
}

void BufferObject::updateMemory(const GLintptr& from_byte, const size_t& size_of_data, const void* data)
{
	if (m_id != 0)
		glBufferSubData(m_target, from_byte, size_of_data, &data);
	else throw fcp::bad_binding_error();
}

