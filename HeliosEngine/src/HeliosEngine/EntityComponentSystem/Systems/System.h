#pragma once

#include "EntityComponentSystem/ForwardDecl.h"
#include "EntityComponentSystem/Entity/Entity.h" 

#include "HeliosEngine/Timestep.h"

#include "Events/Event.h"

#define BIND_EVENT_FN_WITH_REF(fn, reference) std::bind(&fn, this, std::ref(reference), std::placeholders::_1)

namespace Helios
{
  class HELIOSENGINE_API System
  {
  public:
    virtual ~System() = default;

    virtual inline std::unique_ptr<System> Clone() const = 0;

    virtual void OnUpdate(ECSManager& ecs, const Timestep deltaTime) = 0;
    virtual void OnEvent(ECSManager& ecs, Event& event) = 0;

    template <typename... Args>
    const ComponentMask GetRequiredComponents(ECSManager& ecs) const;
  };
}