#pragma once
#include "../pch.h"


class GameObject;
class Base
{
public:
    virtual ~Base() = default;
    Base(const Base&) = delete;
    Base(Base&&) noexcept  = delete;
    Base& operator=(const Base&) = delete;
    Base& operator=(Base&&) noexcept  = delete;    

    GameObject* AddChild(const std::string_view name);
    void AddChild(std::shared_ptr<GameObject> pGameObject);
	GameObject* GetChild(const std::string_view name) const;
    
    

    const std::string_view& GetName() const { return m_Name; };


protected:
    std::vector<std::shared_ptr<GameObject>> m_pChildren;
	std::string_view m_Name;
    
    virtual void Update();
    virtual void Render() const;

    // make sure the Base class can't be constructed
    Base(const std::string_view);
};