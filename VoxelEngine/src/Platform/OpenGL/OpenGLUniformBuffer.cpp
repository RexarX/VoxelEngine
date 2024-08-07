#include "OpenGLUniformBuffer.h"

#include <glad/glad.h>

namespace VoxelEngine
{
	OpenGLUniformBuffer::OpenGLUniformBuffer(const uint32_t size, const uint32_t binding)
	{
		glCreateBuffers(1, &m_RendererID);
		glNamedBufferData(m_RendererID, size, nullptr, GL_DYNAMIC_DRAW);
		glBindBufferBase(GL_UNIFORM_BUFFER, m_Binding, m_RendererID);

		++m_Binding;
	}

	OpenGLUniformBuffer::~OpenGLUniformBuffer()
	{
		glDeleteBuffers(1, &m_RendererID);
	}

	void OpenGLUniformBuffer::SetData(const void* data, const uint32_t size, const uint32_t offset)
	{
		glNamedBufferSubData(m_RendererID, offset, size, data);
	}
}