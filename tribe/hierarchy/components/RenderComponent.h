#pragma once
#include "../../pch.h"
#include "Component.h"

class Renderer;
class TransformComponent;
class RenderComponent final : public Component
{
public:
    RenderComponent(GameObject* pGo, TransformComponent* pTransform, Renderer* pRenderer);
    virtual ~RenderComponent() override;
    RenderComponent(const RenderComponent&) = delete;
    RenderComponent(RenderComponent&&) noexcept  = delete;
    RenderComponent& operator=(const RenderComponent&) = delete;
    RenderComponent& operator=(RenderComponent&&) noexcept  = delete;
    
    virtual void Update() override {};
    void Render() const;
    
private:
    TransformComponent* m_pTransform;
    Renderer* m_pRenderer;

    glm::vec2 m_Center;
};