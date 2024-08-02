#include "Renderer/Mesh.h"
#include "Renderer/RendererAPI.h"

#include "Renderer/Vulkan/VulkanMesh.h"

namespace Helios
{
  DynamicVertex::DynamicVertex(const VertexLayout& layout)
    : m_Layout(layout)
  {
    m_Data.resize(layout.GetStride());
  }

  std::shared_ptr<Mesh> Mesh::Create(const MeshType type, const std::vector<std::byte>& vertices,
                                     const uint32_t vertexCount, const std::vector<uint32_t>& indices)
  {
		switch (RendererAPI::GetAPI())
		{
		case RendererAPI::API::None: CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
		case RendererAPI::API::Vulkan: return std::make_shared<VulkanMesh>(type, vertices, vertexCount, indices);
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
  }

  std::shared_ptr<Mesh> Mesh::Create(const MeshType type, const uint32_t vertexCount, const uint32_t indexCount)
  {
    switch (RendererAPI::GetAPI())
    {
    case RendererAPI::API::None: CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;
    case RendererAPI::API::Vulkan: return std::make_shared<VulkanMesh>(type, vertexCount, indexCount);
    }

    CORE_ASSERT(false, "Unknown RendererAPI!");
    return nullptr;
  }
}