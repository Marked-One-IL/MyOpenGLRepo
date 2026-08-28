#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    static void create(int width, int height, const char *title);
    static bool isOpen(void);
    static void close(void);
    static void updateKeys(void);
    static void updateFrame(void);
    static int getKey(int key);
    static int getWidth(void);
    static int getHeight(void);

private:
    class WindowWrapper
    {
    public:
        ~WindowWrapper(void);
        GLFWwindow *window = nullptr;
    };
    static WindowWrapper g_windowWrapper;

    static void window_resize_callback(GLFWwindow *window, int width, int height);
    static int g_width;
    static int g_height;
};