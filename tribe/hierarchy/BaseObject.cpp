#include "BaseObject.h"
//#include "GameObject.h"

BaseObject::BaseObject(const std::string_view name)
    : m_Name(std::move(name))
{

}

void BaseObject::Update()
{
    
}

void BaseObject::Render() const
{
    
}

GameObject* BaseObject::AddGameObject(const std::string_view objectName)
{

}

GameObject* BaseObject::GetGameObject(const std::string_view objectName) const
{
    const auto& fountIt = std::ranges::find(m_pChildren, [&objectName](GameObject const& name)
    {
        return name == objectName;
    });

    if (foundIt == m_pChildren.cend())
        throw "Couldn't find provided objectname in m_pChildren."
        
    return foundIt->Get();
}