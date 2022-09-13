#pragma once
#include "../pch.h"


class GameObject;
class BaseObject
{
public:
    BaseObject(const std::string_view name);
    virtual ~BaseObject() = default;
    BaseObject(const BaseObject&) = delete;
    BaseObject(BaseObject&&) noexcept  = delete;
    BaseObject& operator=(const BaseObject&) = delete;
    BaseObject& operator=(BaseObject&&) noexcept  = delete;
    

    GameObject* AddGameObject(const std::string_view name);
	GameObject* GetGameObject(const std::string_view name) const;


    const std::string_view GetName() const { return m_Name; };


protected:
    std::vector<std::shared_ptr<GameObject>> m_pChildren;
	std::string_view m_Name;
    
    virtual void Update();
    virtual void Render() const;
};