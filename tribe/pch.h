#pragma once

// stl includes
#include <iostream>
#include <algorithm>
#include <memory>
#include <string.h>
#include <string_view>
#include <vector>
#include <optional>


// library includes
#include <vulkan/vulkan.hpp>
#include <glm/glm.hpp>
#include <imgui.h>
#include <spdlog/spdlog.h>

// engine includes
#include "utils/Locator.h"

template<class T>
inline void SafeDelete(T* pObjectToDelete)
{
	if (pObjectToDelete != nullptr)
	{
		delete (pObjectToDelete);
		pObjectToDelete = nullptr;
	}
}