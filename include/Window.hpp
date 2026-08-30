#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    static void create(int width, int height, const char *title);
    static bool isOpen();
    static void close();
    static void updateKeys();
    static void updateFrame();
    static int getWidth();
    static int getHeight();
    static int getKey(int key);
    static int getFps();

private:
    // All global objects must be deconstructed explicitly in this class.
    // This ensures that global deconstructions are deterministic.
    struct GlobalDestructor
    {
        ~GlobalDestructor();
        GLFWwindow *window = nullptr;
    };
    static GlobalDestructor g_globalDestructor;

    static void window_resize_callback(GLFWwindow *window, int width, int height);
    static int g_width;
    static int g_height;
};