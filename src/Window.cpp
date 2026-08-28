#include <Window.hpp>
#include <Common.hpp>
#include <stdexcept>
#include <cstdlib>
#include <iostream>

int Window::g_width = 0;
int Window::g_height = 0;
Window::WindowWrapper Window::g_windowWrapper;

void Window::create(int width, int height, const char *title)
{
    Window::g_width = width;
    Window::g_height = height;

    if (!glfwInit()) {
        throw Common::RuntimeFailure("Failed to initialize GLFW window");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    Window::g_windowWrapper.window = glfwCreateWindow(Window::g_width, Window::g_height, title, nullptr, nullptr);
    if (nullptr == Window::g_windowWrapper.window) {
        throw Common::RuntimeFailure("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(Window::g_windowWrapper.window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw Common::RuntimeFailure("Failed to initialize GLAD");
    }

    glViewport(0, 0, Window::g_height, Window::g_height);
    glfwSetFramebufferSizeCallback(Window::g_windowWrapper.window, Window::window_resize_callback);
}
bool Window::isOpen(void)
{
    return !glfwWindowShouldClose(Window::g_windowWrapper.window);
}
void Window::setClose(bool state)
{
    glfwSetWindowShouldClose(Window::g_windowWrapper.window, state);
}
void Window::updateKeys(void)
{
    glfwPollEvents();
}
void Window::updateFrame(void)
{
    glfwSwapBuffers(Window::g_windowWrapper.window);
}
int Window::getKey(int key)
{
    return glfwGetKey(Window::g_windowWrapper.window, key);
}
int Window::getWidth(void)
{
    return Window::g_width;
}
int Window::getHeight(void)
{
    return Window::g_height;
}

Window::WindowWrapper::~WindowWrapper(void)
{
    if (this->window) {
        glfwDestroyWindow(this->window);
    }
    glfwTerminate();
}
void Window::window_resize_callback(GLFWwindow *window, int width, int height)
{
    Window::g_width = width;
    Window::g_height = height;
    glViewport(0, 0, Window::g_height, Window::g_height);
}