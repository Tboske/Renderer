#include "Base.h"
#include "GameObject.h"
#include "imgui.h"

Base::Base(const std::string_view name)
    : m_Name(std::move(name))
{

}

void Base::Update()
{
    // update objects
    for (const auto& pChild : m_pChildren) 
        pChild->Update();
}

void Base::Render() const
{
    for (const auto& pChild : m_pChildren)
        pChild->Render();
}

GameObject* Base::AddChild(const std::string_view objectName)
{
    if (objectName.empty()) 
        throw "Provided objectName is empty";    

    return m_pChildren.emplace_back(std::make_unique<GameObject>(objectName)).get();
}

GameObject* Base::AddChild(std::shared_ptr<GameObject> pGameObject)
{
    if (!pGameObject.get())
        throw "pGameObject was a nullptr";

    m_pChildren.emplace_back(pGameObject);
}

GameObject* Base::GetChild(const std::string_view objectName) const
{
    const auto& foundIt = std::ranges::find_if(m_pChildren, [&objectName](const std::shared_ptr<GameObject>& object)
    {
        return object->GetName() == objectName;
    });

    if (foundIt == m_pChildren.cend())
        throw "Couldn't find provided objectname in m_pChildren.";
        
    return foundIt->get();
}