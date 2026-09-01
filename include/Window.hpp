#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window
{
public:
    static void create(int width, int height, const char *title);
    static bool isOpen();
    static void close();
    static void updateKeys();
    static void updateFrame();
    static void fill(glm::vec3 color);
    static int getFps();
    static int getKey(int key);
    static bool canProcessLogic();

private:
    // All global objects that are OpenGL related must be deconstructed explicitly in this class.
    // This ensures that global deconstructions are deterministic.
    struct GlobalDestructor
    {
        ~GlobalDestructor();
    };
    static GlobalDestructor g_globalDestructor;
    static GLFWwindow *g_window;

    static void window_resize_callback(GLFWwindow *window, int width, int height);
    friend class Window::GlobalDestructor;
};