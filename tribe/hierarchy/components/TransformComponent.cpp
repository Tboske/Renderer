#include "TransformComponent.h"
#include "../GameObject.h"

TransformComponent::TransformComponent(GameObject* pGo,  const glm::vec3& pos)
    : Component(pGo)
    , m_RelativePosition(pos)
{   
}

void TransformComponent::Update()
{

}

void TransformComponent::SetPosition(const glm::vec3& position)
{
    m_RelativePosition = position;
}

void TransformComponent::SetAbsolutePosition(const glm::vec3 &absolutePosition)
{
    m_RelativePosition = absolutePosition - m_AbsolutePosition;
}

void TransformComponent::UpdateAbsolutePosition(const glm::vec3& absolutePosition)
{
    m_AbsolutePosition = absolutePosition;
}