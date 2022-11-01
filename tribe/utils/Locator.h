#pragma once
#include "../pch.h"

template <typename T>
class Locator final 
{
public:
	static void Set(T* pService) 
	{
		m_pService = pService; 
	}

	static T* Get() { return m_pService; }

private:
	inline static T* m_pService = nullptr;
};