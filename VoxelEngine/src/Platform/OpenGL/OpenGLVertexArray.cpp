#include "OpenGLVertexArray.h"

#include "vepch.h"

#include <glad/glad.h>

namespace VoxelEngine
{
	static GLenum ShaderDataTypeToOpenGLBaseType(const ShaderDataType type)
	{
		switch (type)
		{
		case VoxelEngine::ShaderDataType::Float:    return GL_FLOAT;
		case VoxelEngine::ShaderDataType::Float2:   return GL_FLOAT;
		case VoxelEngine::ShaderDataType::Float3:   return GL_FLOAT;
		case VoxelEngine::ShaderDataType::Float4:   return GL_FLOAT;
		case VoxelEngine::ShaderDataType::Mat3:     return GL_FLOAT;
		case VoxelEngine::ShaderDataType::Mat4:     return GL_FLOAT;
		case VoxelEngine::ShaderDataType::Int:      return GL_INT;
		case VoxelEngine::ShaderDataType::Int2:     return GL_INT;
		case VoxelEngine::ShaderDataType::Int3:     return GL_INT;
		case VoxelEngine::ShaderDataType::Int4:     return GL_INT;
		case VoxelEngine::ShaderDataType::Bool:     return GL_BOOL;
		}

		CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glGenVertexArrays(1, &m_RendererID);
		Bind();
	}

	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_RendererID);
	}

	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_RendererID);
	}

	void OpenGLVertexArray::Unbind() const
	{
		glBindVertexArray(0);
	}

	void OpenGLVertexArray::AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer)
	{
		CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");
		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout) {
			glVertexAttribPointer(m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.type_),
				element.normalized_ ? GL_TRUE : GL_FALSE,
				layout.GetStride(),
				(void*)element.offset_);
			glEnableVertexAttribArray(m_VertexBufferIndex);
			++m_VertexBufferIndex;
		}

		m_VertexBuffer = vertexBuffer;
	}

	void OpenGLVertexArray::SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer)
	{
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}

	void OpenGLVertexArray::AddVertexAttribDivisor(const uint32_t index, const uint32_t divisor)
	{
    glVertexAttribDivisor(index, divisor);
	}
}