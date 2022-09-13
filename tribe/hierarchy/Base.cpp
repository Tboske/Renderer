#include "Base.h"
#include "GameObject.h"

Base::Base(const std::string_view name)
    : m_Name(std::move(name))
{

}

void Base::Update()
{
    
}

void Base::Render() const
{
    
}

GameObject* Base::AddGameObject(const std::string_view objectName)
{

    return nullptr;
}

GameObject* Base::GetGameObject(const std::string_view objectName) const
{
    const auto& foundIt = std::ranges::find_if(m_pChildren, [&objectName](const std::shared_ptr<GameObject>& object)
    {
        return object->GetName() == objectName;
    });

    if (foundIt == m_pChildren.cend())
        throw "Couldn't find provided objectname in m_pChildren.";
        
    return foundIt->get();
}