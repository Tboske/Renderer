#pragma once
#include "pch.h"

class GLFWwindow;
class Window final 
{
public:
    Window(std::string_view windowName);
    ~Window();
    Window(const Window&) = delete;
    Window(Window&&) noexcept  = delete;
    Window& operator=(const Window&) = delete;
    Window& operator=(Window&&) noexcept  = delete;
    
    GLFWwindow* GetWindow() const { return m_pWindow; }
    bool ShouldEnd() const;
    void PollWindowEvents() const;

private:
    glm::ivec2 m_Size{1280, 720};
    
    GLFWwindow* m_pWindow;
};