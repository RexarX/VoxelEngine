#pragma once

#include "Renderer/RendererAPI.h"

#include "pch.h"

namespace Helios
{
  class GraphicsContext
  {
  public:
    GraphicsContext(void* window);
    ~GraphicsContext();

    void Init();
    void Shutdown();
    void Update();
    void BeginFrame();
    void EndFrame();
    void Record(const RenderQueue& queue);
    void SetViewport(const uint32_t width, const uint32_t height,
                     const uint32_t x = 0, const uint32_t y = 0);

    void InitImGui();
    void ShutdownImGui();
    void BeginFrameImGui();
    void EndFrameImGui();

    void SetVSync(const bool enabled);
    void SetResized(const bool resized);
    void SetImGuiState(const bool enabled);

    static std::shared_ptr<GraphicsContext>& Create(void* window);
    static std::shared_ptr<GraphicsContext>& Get();

  private:
    static std::shared_ptr<GraphicsContext> m_Instance;

    void* m_Window;
    std::unique_ptr<RendererAPI> m_RendererAPI;
  };
}