#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

class Window
{
public:
    static void create  (int width, int height, const char *title);
    static void destroy (void);

    static bool isOpen          (void);
    static void close           (void);
    static void updateKeys      (void);
    static void updateFrame     (void);
    static bool canProcessLogic (void);
    static int  getFps          (void);
    static int  getKey          (int key);
    static void fill            (glm::vec3 color);

private:
    static GLFWwindow *g_window;

    static void window_resize_callback(GLFWwindow *window, int width, int height);
};