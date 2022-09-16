#include "GameObject.h"

#include "components/Component.h"
#include "components/RenderComponent.h"

GameObject::GameObject(Base* pParent, const std::string_view objectName) 
    : Base(objectName)
    , m_pParent(pParent)
{
}

void GameObject::Render() const
{
	if (RenderComponent* comp = GetComponent<RenderComponent>())
		comp->Render();

	// calls Render on child objects
	Base::Render();
}

void GameObject::Update()
{
	for (const auto& [type, pComponent] : m_pComponents)
		pComponent->Update();

	// calls Update on child objects
	Base::Update();
}