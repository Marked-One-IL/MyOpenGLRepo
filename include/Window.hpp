#pragma once
#include <GLFW/glfw3.h>

class Window
{
public:
    static void create(int width, int height, const char *title);
    static bool isOpen(void);
    static void close(void);
    static void update(void);
    static int getKey(int key);

private:
    class WindowHandle
    {
    public:
        ~WindowHandle(void);
        GLFWwindow *window = nullptr;
    };
    static WindowHandle m_windowHandle;
};