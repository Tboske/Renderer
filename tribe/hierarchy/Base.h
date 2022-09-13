#pragma once
#include "../pch.h"


class GameObject;
class Base
{
public:
    Base(const std::string_view);
    virtual ~Base() = default;
    Base(const Base&) = delete;
    Base(Base&&) noexcept  = delete;
    Base& operator=(const Base&) = delete;
    Base& operator=(Base&&) noexcept  = delete;    

    GameObject* AddGameObject(const std::string_view name);
	GameObject* GetGameObject(const std::string_view name) const;


    const std::string_view GetName() const { return m_Name; };


protected:
    std::vector<std::shared_ptr<GameObject>> m_pChildren;
	std::string_view m_Name;
    
    virtual void Update();
    virtual void Render() const;
};