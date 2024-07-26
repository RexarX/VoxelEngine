#pragma once

#include "Renderer/RenderQueue.h"

namespace Helios
{
  class ResourceManager
  {
  public:
    ResourceManager() = default;
    virtual ~ResourceManager() = default;

    virtual void InitializeResources(const std::vector<Renderable>& renderables) = 0;
    virtual void UpdateResources(const RenderQueue& renderQueue) = 0;

    virtual inline std::unique_ptr<ResourceManager> Clone() const = 0;

    static std::unique_ptr<ResourceManager> Create();
  };
}