#pragma once
#include "Base.h"
#include <type_traits>
#include <typeinfo>
#include <unordered_map>

class Component;
class GameObject final : public Base
{
public:
    GameObject(Base* pParent, const std::string_view objectName);
    virtual ~GameObject() override = default;
    GameObject(const GameObject&) = delete;
    GameObject(GameObject&&) noexcept  = delete;
    GameObject& operator=(const GameObject&) = delete;
    GameObject& operator=(GameObject&&) noexcept  = delete;
    
    template <typename T, typename... Args, typename =  std::enable_if_t<std::is_base_of<Component, T>::value>> 
    T* AddComponent(Args&&... args);

	template <typename T, typename =  std::enable_if_t<std::is_base_of<Component, T>::value>> 
    T* GetComponent() const;

	template <typename T, typename =  std::enable_if_t<std::is_base_of<Component, T>::value>> 
    void RemoveComponent();

protected:
    friend class Base;
    virtual void Render() const override;
    virtual void Update() override;
    
private:
    std::unordered_map<const std::type_info*, Component*> m_pComponents;
    Base* m_pParent;

    friend class Scene;
};

#pragma region TemplateImplementations
template <typename T, typename... Args, typename> 
T* GameObject::AddComponent(Args&&... args)
{
    const auto pComp = new T(this, std::forward<Args>(args)...);
	m_pComponents[&typeid(T)] = pComp;
	return pComp;
}

template <typename T, typename> 
T* GameObject::GetComponent() const
{
	const auto d = &typeid(T);

	if (m_pComponents.contains(d))
		return static_cast<T*>(m_pComponents.at(d));

	// component does not exist
	return nullptr;
}

template <typename T, typename>
void GameObject::RemoveComponent()
{
	T* comp = static_cast<T*>(m_pComponents.at(&typeid(T)));

	SafeDelete(comp);

	m_pComponents.erase(&typeid(T));
}
#pragma endregion