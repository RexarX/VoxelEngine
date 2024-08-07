#pragma once

#include "VulkanStructs.h"

#include "Render/GraphicsContext.h"

#ifdef VE_DEBUG
	constexpr bool enableValidationLayers = true;
#else
	constexpr bool enableValidationLayers = false;
#endif

struct GLFWwindow;

constexpr uint32_t FRAME_OVERLAP = 2;

namespace VoxelEngine
{
	class VulkanContext : public GraphicsContext
	{
	public:
		VulkanContext(GLFWwindow* windowHandle);

		virtual void Init() override;
		virtual void Shutdown() override;
		virtual void Update() override;
		virtual void SwapBuffers() override;
		virtual void ClearBuffer() override;
		virtual void SetViewport(const uint32_t width, const uint32_t height) override;

		virtual void InitImGui() override;
		virtual void ShutdownImGui() override;
		virtual void Begin() override;
		virtual void End() override;

		virtual void SetVSync(const bool enabled) override;
		virtual void SetResized(const bool resized) override { m_Resized = resized; }

		virtual void SetImGuiState(const bool enabled) override { m_ImGuiEnabled = enabled; }

		void Build();

		void ImmediateSubmit(std::function<void(vk::CommandBuffer cmd)>&& function);

		void AddPipeline(const uint32_t id);

		static inline VulkanContext& Get() { return *m_Context; }
		inline DeletionQueue& GetDeletionQueue() { return m_DeletionQueue; }

		inline DrawQueue& GetDrawQueue() { return m_DrawQueue; }

		inline FrameData& GetCurrentFrame() { return m_Frames[m_FrameNumber % FRAME_OVERLAP]; };
		inline vk::Device& GetDevice() { return m_Device; }
		inline VmaAllocator& GetAllocator() { return m_Allocator; }
		inline AllocatedImage& GetDrawImage() { return m_DrawImage; }
		inline AllocatedImage& GetDepthImage() { return m_DepthImage; }

		inline Pipeline& GetPipeline(const uint32_t id) { return m_Pipelines[id]; }

		inline const vk::Sampler GetSamplerNearest() { return m_SamplerNearest; }
		inline const vk::Sampler GetSamplerLinear() { return m_SamplerLinear; }

	private:
		const std::vector<const char*> validationLayers = {
			"VK_LAYER_KHRONOS_validation"
		};

		const std::vector<const char*> deviceExtensions = {
			VK_KHR_SWAPCHAIN_EXTENSION_NAME,
			VK_KHR_DYNAMIC_RENDERING_EXTENSION_NAME,
			VK_KHR_SYNCHRONIZATION_2_EXTENSION_NAME,
			VK_KHR_BUFFER_DEVICE_ADDRESS_EXTENSION_NAME,
			VK_KHR_PUSH_DESCRIPTOR_EXTENSION_NAME
		};

		DeletionQueue m_DeletionQueue;

		DrawQueue m_DrawQueue;

		FrameData m_Frames[FRAME_OVERLAP];
		uint32_t m_FrameNumber = 0;

		static VulkanContext* m_Context;

		VmaAllocator m_Allocator;

		vk::Instance m_Instance;

		vk::Device m_Device;

		VkDebugUtilsMessengerEXT m_Callback;

		vk::SurfaceKHR m_Surface;

		vk::PhysicalDevice m_PhysicalDevice;

		vk::Queue m_GraphicsQueue;
		vk::Queue m_PresentQueue;

		vk::SwapchainKHR m_SwapChain;
		vk::Extent2D m_SwapChainExtent;
		std::vector<vk::Image> m_SwapChainImages;
		std::vector<vk::ImageView> m_SwapChainImageViews;
		vk::Format m_SwapChainImageFormat;

		vk::Extent2D m_DrawExtent;

		DescriptorAllocator m_ImGuiDescriptorAllocator;

		AllocatedImage m_DrawImage;
		AllocatedImage m_DepthImage;

		std::unordered_map<uint32_t, Pipeline> m_Pipelines;

		vk::CommandPool m_ImCommandPool;
		vk::CommandBuffer m_ImCommandBuffer;
		vk::Fence m_ImFence;

		vk::Sampler m_SamplerNearest;
		vk::Sampler m_SamplerLinear;

	private:
		void CreateInstance();
		void SetupDebugCallback();
		void CreateSurface();
		void PickPhysicalDevice();
		void CreateLogicalDevice();
		void CreateAllocator();
		void CreateSwapChain();
		void CreateImageViews();
		void CreateCommands();
		void CreateSyncObjects();

		void CreateSamplers();
		
		void RecreateSwapChain();

		void DrawGeometry(const vk::CommandBuffer cmd);
		void DrawImGui(const vk::ImageView view);

		void transition_image(const vk::CommandBuffer cmd, const vk::Image image,
													const vk::ImageLayout currentLayout, const vk::ImageLayout newLayout);

		vk::SemaphoreSubmitInfo semaphore_submit_info(const vk::PipelineStageFlags2 stageMask,
																									const vk::Semaphore semaphore) const;

		vk::ImageCreateInfo image_create_info(const vk::Format format, const vk::ImageUsageFlags usageFlags,
																					const vk::Extent3D extent) const;
		vk::ImageViewCreateInfo imageview_create_info(const vk::Image image, const vk::Format format,
																									const vk::ImageAspectFlags aspectFlags) const;
		void copy_image_to_image(const vk::CommandBuffer cmd, const vk::Image source, const vk::Image destination,
														 const vk::Extent2D srcSize, const vk::Extent2D dstSize) const;

		bool IsDeviceSuitable() const;
		QueueFamilyIndices FindQueueFamilies() const;
		const std::vector<const char*> GetRequiredExtensions() const;
		bool CheckDeviceExtensionSupport() const;
		bool CheckValidationLayerSupport() const;

		VkResult CreateDebugUtilsMessengerEXT(const VkDebugUtilsMessengerCreateInfoEXT* pCreateInfo,
																					const VkAllocationCallbacks* pAllocator);
		void DestroyDebugUtilsMessengerEXT(const VkAllocationCallbacks* pAllocator) const;

		vk::SurfaceFormatKHR ChooseSwapSurfaceFormat(const std::vector<vk::SurfaceFormatKHR>& availableFormats) const;
		vk::PresentModeKHR ChooseSwapPresentMode(const std::vector<vk::PresentModeKHR>& availablePresentModes) const;
		vk::Extent2D ChooseSwapExtent(const vk::SurfaceCapabilitiesKHR& capabilities) const;
		SwapChainSupportDetails QuerySwapChainSupport() const;

	private:
		bool m_Resized = false;
		bool m_Vsync = true;
		bool m_ImGuiEnabled = false;

		GLFWwindow* m_WindowHandle;
	};
}