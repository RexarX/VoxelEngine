#include "Application.h"

#include "vepch.h"

#include "Render/Renderer.h"
#include "Render/RendererAPI.h"
#include "Vulkan/VulkanContext.h"

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace VoxelEngine
{
	Application* Application::m_Instance = nullptr;

	Application::Application()
	{
		CORE_ASSERT(!m_Instance, "Application already exists!");
		m_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));

		Renderer::Init();

		m_ImGuiLayer = new ImGuiLayer();
		PushOverlay(m_ImGuiLayer);
	}
	
	Application::~Application()
	{
		Renderer::Shutdown();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer)
	{
    m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(BIND_EVENT_FN(OnWindowResize));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin(); ) {
			(*--it)->OnEvent(e);
			if (e.Handled) { break; }
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0) {
			m_Window->SetMinimized(true);
			return true;
		}

		m_Window->SetMinimized(false);

		Renderer::OnWindowResize(e.GetWidth(), e.GetHeight());

		return true;
	}

	void Application::Run()
	{
		if (RendererAPI::GetAPI() == RendererAPI::API::Vulkan) { VulkanContext::Get().Build(); }

		double LastFrameUpdate(0.0), LastFrameTime(0.0);

		m_FramerateLimit = 1 / m_Window->GetFramerate();

		m_Timer.Start();

		while (m_Running) {
			m_Timer.Stop();
			m_DeltaTime = m_Timer.GetElapsedSec() - LastFrameUpdate;

			m_Window->PoolEvents();

			if (!m_Window->IsMinimized() && (m_DeltaTime >= m_FramerateLimit ||
																			 m_Window->GetFramerate() == 0.0)) {

				for (Layer* layer : m_LayerStack) {
					layer->OnUpdate(m_DeltaTime);
				}

				if (m_Window->IsImGuiEnabled()) {
					m_ImGuiLayer->Begin();

					for (Layer* layer : m_LayerStack) {
						layer->OnImGuiRender(ImGui::GetCurrentContext());
					}

					m_ImGuiLayer->End();
				}

				m_Window->OnUpdate();

				LastFrameUpdate = m_Timer.GetElapsedSec();
			}
		}
	}
}
