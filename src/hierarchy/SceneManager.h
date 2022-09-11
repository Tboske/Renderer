#pragma once


#include <vector>
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	SceneManager(const SceneManager&)                = delete;
	SceneManager(SceneManager&&) noexcept            = delete;
	SceneManager& operator=(const SceneManager&)     = delete;
	SceneManager& operator=(SceneManager&&) noexcept = delete;

    


private:
	std::vector<int> m_Objects;
};