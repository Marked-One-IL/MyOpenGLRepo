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
    static void fillScreen(glm::vec3 color);
    static int getFps();
    static int getKey(int key);

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
};