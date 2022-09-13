#pragma once
#include "Base.h"

class GameObject final : public Base
{
public:
    GameObject(const std::string_view objectName);
    virtual ~GameObject() override = default;
    GameObject(const GameObject&) = delete;
    GameObject(GameObject&&) noexcept  = delete;
    GameObject& operator=(const GameObject&) = delete;
    GameObject& operator=(GameObject&&) noexcept  = delete;
    
    
    
private:
    
    
};