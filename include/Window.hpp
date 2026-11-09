#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <format>

class Window
{
public:
    static void construct (int width, int height, const char *title);
    static void destruct  (void);

    static bool isOpen          (void);
    static void close           (void);
    static void updateKeys      (void);
    static void updateFrame     (void);
    static bool canProcessLogic (void);
    static int  getFps          (void);
    static bool isKeyPressed    (int key);
    static void fill            (glm::vec3 color);
    static void setTitle        (const char *title);

    template <typename... Args>
    static void setTitle (std::format_string<Args...> fmt, Args&&... args);

private:
    static GLFWwindow *g_window;

    static void window_resize_callback(GLFWwindow *window, int width, int height);
};

template <typename... Args>
inline void Window::setTitle(std::format_string<Args...> fmt, Args&&... args)
{
    std::string title = std::format(fmt, std::forward<Args>(args)...);
    glfwSetWindowTitle(Window::g_window, title.data());
}