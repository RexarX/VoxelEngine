#pragma once

#include <glm/glm.hpp>

namespace VoxelEngine
{
  class Frustum
  {
  public:
    Frustum() = default;

    void CreateFrustum(const glm::mat4& viewProjection);

    bool IsCubeInFrustrum(const float size, const glm::vec3& position);

  private:
    float m_Frustum[6][4];
    float m_Normalize;
  };
}