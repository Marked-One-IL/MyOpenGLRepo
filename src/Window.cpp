#include <Window.hpp>
#include <Common.hpp>
#include <Texture.hpp>
#include <stb_image.h>
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

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw Common::RuntimeFailure("Failed to initialize GLAD");
    }

    glViewport(0, 0, Window::g_height, Window::g_height);
    glfwSetFramebufferSizeCallback(Window::g_windowWrapper.window, Window::window_resize_callback);
    Texture::buildGlobalData();
    stbi_set_flip_vertically_on_load(true);
}
bool Window::isOpen()
{
    return !glfwWindowShouldClose(Window::g_windowWrapper.window);
}
void Window::close()
{
    glfwSetWindowShouldClose(Window::g_windowWrapper.window, true);
}
void Window::updateKeys()
{
    glfwPollEvents();
}
void Window::updateFrame()
{
    glfwSwapBuffers(Window::g_windowWrapper.window);
}
int Window::getWidth()
{
    return Window::g_width;
}
int Window::getHeight()
{
    return Window::g_height;
}
int Window::getKey(int key)
{
    return glfwGetKey(Window::g_windowWrapper.window, key);
}

Window::WindowWrapper::~WindowWrapper()
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