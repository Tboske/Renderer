#pragma once
#include "Component.h"

class RenderComponent final : public Component
{
public:
    RenderComponent(GameObject* pGo);
    virtual ~RenderComponent() override;
    RenderComponent(const RenderComponent&) = delete;
    RenderComponent(RenderComponent&&) noexcept  = delete;
    RenderComponent& operator=(const RenderComponent&) = delete;
    RenderComponent& operator=(RenderComponent&&) noexcept  = delete;
    
    virtual void Update() override {};
    void Render() const;
    
private:
    
};