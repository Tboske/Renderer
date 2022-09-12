#include "GameTime.h"
#include <GLFW/glfw3.h>


void GameTime::Update()
{
    const auto& currentTime = glfwGetTime();

    m_Delta = currentTime - m_Time;
    m_Time = currentTime;
}
