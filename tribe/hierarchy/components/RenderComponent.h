#pragma once
#include "../../pch.h"
#include "Component.h"

class TransformComponent;
class RenderComponent final : public Component
{
public:
    RenderComponent(GameObject* pGo, TransformComponent* pTransform);
    virtual ~RenderComponent() override;
    RenderComponent(const RenderComponent&) = delete;
    RenderComponent(RenderComponent&&) noexcept  = delete;
    RenderComponent& operator=(const RenderComponent&) = delete;
    RenderComponent& operator=(RenderComponent&&) noexcept  = delete;
    
    virtual void Update() override {};
    void Render() const;
    
private:
    TransformComponent* m_pTransform;

    glm::vec2 m_Center;
};