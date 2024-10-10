#include "../include/element_buffer.hpp"

/* EBO IMPLEMENTATION
 *******************************************************************************
 */
EBO::EBO(const size_t& size_of_data, const void* data, const GLenum& buffer_usage): BufferObject(GL_ELEMENT_ARRAY_BUFFER)
{
  this->bind();
  glBufferData(this->m_target, size_of_data, data, buffer_usage);
  this->unbind();  // Allow code like: 'ebo1 = EBO(data);' to be possible without breaking the state machine with dangling bindings.
}

EBO::EBO(const EBO& other, const GLenum& buffer_usage): BufferObject(GL_ELEMENT_ARRAY_BUFFER)
{
	// Get size of data of the other EBO object.
	other.bind();
	int size_of_other;	// for simplicity, now handle only max to 4 GiB.
	glGetBufferParameteriv(other.m_target, GL_BUFFER_SIZE, &size_of_other);

	// Allocate enough memory.
  this->bind();
	this->allocateMemory(size_of_other);
	// Copy this EBO with the other one.
	*this = other;

  this->unbind();
}

EBO& EBO::operator=(const EBO& other)
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

void EBO::copyTo(const EBO& other, const copy_args& args)
{
  if (this == &other) return;

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

void EBO::copyFrom(const EBO& other, const copy_args& args)
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

void EBO::setData(const size_t& size_of_data, const void* data, const GLenum& buffer_usage)
{
	this->bind();
	glBufferData(this->m_target, size_of_data, data, buffer_usage);
	this->unbind();

	return;
}
