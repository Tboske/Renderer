#pragma once

class GameObject;
class Component
{
public:
	Component(GameObject* pGo)
		: m_pParent(pGo)
	{
	}
	virtual ~Component()
	{
		m_pParent = nullptr; // these objects are deleted by the parent
	}

	virtual void Update() = 0;

	GameObject* GetParent() const
	{
		return m_pParent;
	}

private:
	GameObject* m_pParent;
};