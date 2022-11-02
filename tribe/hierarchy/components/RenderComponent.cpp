#include "RenderComponent.h"
#include "Component.h"
#include "TransformComponent.h"
// #include "render/Renderer.h"

RenderComponent::RenderComponent(GameObject* pGo, TransformComponent* pTransform, Renderer* pRenderer)
    : Component(pGo)
    , m_pTransform(pTransform)
    , m_pRenderer(pRenderer)
{
}

RenderComponent::~RenderComponent()
{
    m_pTransform = nullptr;
}

void RenderComponent::Render() const
{
    
}