#pragma once

#include "Render/VertexArray.h"

namespace VoxelEngine
{
	class VulkanVertexArray : public VertexArray
	{
	public:	
		VulkanVertexArray() = default;
		virtual ~VulkanVertexArray() = default;

		virtual void Bind() const override;
		virtual void Unbind() const override;

		virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer) override;
		virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) override;
		virtual void AddVertexAttribDivisor(const uint32_t index, const uint32_t divisor) override;

		virtual inline const std::shared_ptr<VertexBuffer>& GetVertexBuffer() const override { return m_VertexBuffer; }
		virtual inline const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

		void IncreaseVertexBufferIndex() { m_VertexBufferIndex++; }

    inline const uint32_t GetVertexBufferIndex() const { return m_VertexBufferIndex; }

	private:
    uint32_t m_VertexBufferIndex = 0;

		std::shared_ptr<VertexBuffer> m_VertexBuffer;
		std::shared_ptr<IndexBuffer> m_IndexBuffer;
	};
}