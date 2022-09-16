#include "RenderComponent.h"
#include "Component.h"
#include "TransformComponent.h"

RenderComponent::RenderComponent(GameObject* pGo, TransformComponent* pTransform)
    : Component(pGo)
    , m_pTransform(pTransform)
{
}

RenderComponent::~RenderComponent()
{
    m_pTransform = nullptr;
}

void RenderComponent::Render() const
{
    
}