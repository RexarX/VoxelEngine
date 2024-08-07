#include "RendererAPI.h"

#include "vepch.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"
#include "Platform/Vulkan/VulkanRendererAPI.h"

namespace VoxelEngine
{
	RendererAPI::API RendererAPI::s_API = RendererAPI::API::Vulkan;

	std::unique_ptr<RendererAPI> RendererAPI::Create()
	{
		switch (s_API)
		{
		case RendererAPI::API::None:    CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_unique<OpenGLRendererAPI>();
		case RendererAPI::API::Vulkan:  return std::make_unique<VulkanRendererAPI>();
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}