#pragma once

// stl includes
#include <iostream>
#include <memory>
#include <string.h>
#include <string_view>
#include <vector>

// library includes
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <spdlog/spdlog.h>


template<class T>
inline void SafeDelete(T* pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete (pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}