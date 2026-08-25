#include <Window.hpp>
#include <stdexcept>
#include <cstdlib>

Window::WindowHandle::~WindowHandle(void)
{
    if (this->window) {
        glfwDestroyWindow(this->window);
    }
    glfwTerminate();
}
Window::WindowHandle Window::m_windowHandle;

void Window::create(int width, int height, const char *title)
{
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW window");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    Window::m_windowHandle.window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (nullptr == Window::m_windowHandle.window) {
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(Window::m_windowHandle.window);
}
bool Window::isOpen(void)
{
    return !glfwWindowShouldClose(Window::m_windowHandle.window);
}
void Window::close(void)
{
    glfwSetWindowShouldClose(Window::m_windowHandle.window, true);
}
void Window::update(void)
{
    glfwSwapBuffers(Window::m_windowHandle.window);
    glfwPollEvents();
}
int Window::getKey(int key)
{
    return glfwGetKey(Window::m_windowHandle.window, key);
}