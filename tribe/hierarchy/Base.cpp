#include "Base.h"
//#include "GameObject.h"

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

}

GameObject* Base::GetGameObject(const std::string_view objectName) const
{
    const auto& fountIt = std::ranges::find(m_pChildren, [&objectName](GameObject const& name)
    {
        return name == objectName;
    });

    if (foundIt == m_pChildren.cend())
        throw "Couldn't find provided objectname in m_pChildren."
        
    return foundIt->Get();
}