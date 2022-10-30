#pragma once
#include "../pch.h"

template <typename T>
class Locator final 
{
public:
	static void Set(std::unique_ptr<T> pService) 
	{
		m_pService = std::move(pService); 
	}

	static T* Get() { return m_pService.get(); }

	static void Cleanup() 
	{ 
		m_pService.reset();
	}
private:
	static std::unique_ptr<T> m_pService;
};