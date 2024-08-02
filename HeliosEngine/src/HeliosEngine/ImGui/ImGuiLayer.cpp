#include "ImGuiLayer.h"

#include "HeliosEngine/Application.h"

namespace Helios
{
  ImGuiLayer::ImGuiLayer()
    : Layer("ImGuiLayer")
  {
  }

	void ImGuiLayer::OnAttach()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
		io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;
		io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports;
		float fontSize = 16.0f;
		io.Fonts->AddFontFromFileTTF((HELIOSENGINE_DIR + "Assets/Fonts/DroidSans.ttf").c_str(), fontSize);
		io.FontDefault = io.Fonts->AddFontFromFileTTF((HELIOSENGINE_DIR + "Assets/Fonts/Cousine-Regular.ttf").c_str(), fontSize);
		
		ImGui::StyleColorsDark();
		
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 0.75f;
		}

		Application::Get().GetWindow().InitImGui();
	}

	void ImGuiLayer::OnDetach()
	{
		Application::Get().GetWindow().ShutdownImGui();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::OnEvent(Event& e)
	{
		if (m_BlockEvents) {
			ImGuiIO& io = ImGui::GetIO();
			e.Handled |= e.IsInCategory(EventCategoryMouse) & io.WantCaptureMouse;
			e.Handled |= e.IsInCategory(EventCategoryKeyboard) & io.WantCaptureKeyboard;
		}
	}

	void ImGuiLayer::Begin()
	{
		Application::Get().GetWindow().BeginFrameImGui();

		ImGui::NewFrame();
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport(), ImGuiDockNodeFlags_PassthruCentralNode);
	}

	void ImGuiLayer::End()
	{
		Window& window = Application::Get().GetWindow();

		ImGuiIO& io = ImGui::GetIO();
		ImGui::GetIO().DisplaySize = ImVec2((float)window.GetWidth(), (float)window.GetHeight());

		window.EndFrameImGui();
	}

	inline const uint32_t ImGuiLayer::GetActiveWidgetID() const noexcept
	{
    return ImGui::GetActiveID();
	}
}