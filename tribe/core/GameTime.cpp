#include "GameTime.h"
#include <GLFW/glfw3.h>


void GameTime::Update()
{
    const auto& currentTime = glfwGetTime();

    m_Delta = currentTime - m_Time;
    m_Time = currentTime;

    m_Fps = int(1.f / m_Delta);
}

double GameTime::GetSleepTime() const
{
    return m_Time + (1.0 / m_FpsTarget) - glfwGetTime();
}