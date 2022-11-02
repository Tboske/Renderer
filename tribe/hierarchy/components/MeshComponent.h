#pragma once
#include "pch.h"
#include "Component.h"

struct VertexPosColTex
{
    glm::vec3 position;
    glm::vec3 colors;
    glm::vec2 texCoords;
};

class MeshComponent final : public Component
{
public:
    MeshComponent(GameObject* pGo);
    virtual ~MeshComponent() override = default;
    MeshComponent(const MeshComponent&) = delete;
    MeshComponent(MeshComponent&&) noexcept  = delete;
    MeshComponent& operator=(const MeshComponent&) = delete;
    MeshComponent& operator=(MeshComponent&&) noexcept  = delete;
    
    void Update() override;
    
private:
    std::array<VertexPosColTex, 4> m_Vertices;
};