#include "GraphicsContext.h"
#include "Renderer.h"

#include "vepch.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include "Platform/Vulkan/VulkanContext.h"

namespace VoxelEngine
{
	std::unique_ptr<GraphicsContext> GraphicsContext::Create(void* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::API::None:    CORE_ASSERT(false, "RendererAPI::None is currently not supported!"); return nullptr;
		case RendererAPI::API::OpenGL:  return std::make_unique<OpenGLContext>(static_cast<GLFWwindow*>(window));
    case RendererAPI::API::Vulkan:  return std::make_unique<VulkanContext>(static_cast<GLFWwindow*>(window));
		}

		CORE_ASSERT(false, "Unknown RendererAPI!");
		return nullptr;
	}
}