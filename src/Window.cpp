#include <Window.hpp>
#include <Common.hpp>
#include <Texture.hpp>
#include <filesystem>
#include <stb_image.h>
#include <stdexcept>
#include <cstdlib>
#include <iostream>

Window::GlobalDestructor Window::g_globalDestructor;

void Window::create(int width, int height, const char *title)
{
#ifndef READY_TO_DISTRIBUTE
        Common::clearScreen();
        std::filesystem::current_path(PROJECT_ROOT);
#endif


    if (!glfwInit()) {
        throw Common::RuntimeFailure("Failed to initialize GLFW window");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    Window::g_globalDestructor.window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (nullptr == Window::g_globalDestructor.window) {
        throw Common::RuntimeFailure("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(Window::g_globalDestructor.window);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw Common::RuntimeFailure("Failed to initialize GLAD");
    }

    glViewport(0, 0, width, height);
    glfwSetFramebufferSizeCallback(Window::g_globalDestructor.window, Window::window_resize_callback);
    Texture::constructGlobalData();
    stbi_set_flip_vertically_on_load(true);
}
bool Window::isOpen()
{
    return !glfwWindowShouldClose(Window::g_globalDestructor.window);
}
void Window::close()
{
    glfwSetWindowShouldClose(Window::g_globalDestructor.window, true);
}
void Window::updateKeys()
{
    glfwPollEvents();
}
void Window::updateFrame()
{
    glfwSwapBuffers(Window::g_globalDestructor.window);
}
void Window::fillScreen(glm::vec3 color)
{
    glClearColor(static_cast<GLfloat>(color.x), static_cast<GLfloat>(color.y), static_cast<GLfloat>(color.z), static_cast<GLfloat>(1.0f));
    glClear(GL_COLOR_BUFFER_BIT);
}
int Window::getFps()
{
    static int count = 0;
    static int fps = 0;
    static double lastTime = 0.0; // Will be always have an integer like value for better results.

    if (glfwGetTime() - lastTime >= 1.0)
    {
        fps = count;
        count = 0;
        lastTime += 1.0;
    }
    count++;

    return fps;
}
int Window::getKey(int key)
{
    return glfwGetKey(Window::g_globalDestructor.window, key);
}

Window::GlobalDestructor::~GlobalDestructor()
{
    Texture::destructGlobalData();
    if (this->window) {
        glfwDestroyWindow(this->window);
    }
    glfwTerminate();
}
void Window::window_resize_callback(GLFWwindow *window, int width, int height)
{
    glViewport(0, 0, width, height);
}