#pragma once
#include "../../pch.h"
#include "Component.h"

class TransformComponent final : public Component
{
public:
    TransformComponent(GameObject* pGo, const glm::vec3& pos);
    virtual ~TransformComponent() override = default;
    TransformComponent(const TransformComponent&) = delete;
    TransformComponent(TransformComponent&&) noexcept  = delete;
    TransformComponent& operator=(const TransformComponent&) = delete;
    TransformComponent& operator=(TransformComponent&&) noexcept  = delete;
    
    virtual void Update() override;
    
    void SetPosition(const glm::vec3& position);
    void SetAbsolutePosition(const glm::vec3& absolutePosition);

    glm::vec3 GetAbsolutePosition() const { return m_AbsolutePosition + m_RelativePosition; }
    glm::vec3& GetRelativePosition() { return m_RelativePosition; }

protected:
    void UpdateAbsolutePosition(const glm::vec3& absolutePosition);

private:
    glm::vec3 m_AbsolutePosition;
    glm::vec3 m_RelativePosition;
};