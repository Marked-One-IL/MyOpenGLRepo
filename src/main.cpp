#include <iostream>
#include <filesystem>
#include <Window.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <glm/glm.hpp>

// #define READY_TO_DISTRIBUTE

int main()
{
#ifndef READY_TO_DISTRIBUTE
    std::filesystem::current_path(PROJECT_ROOT);
#endif

    Window::create(800, 600, "LearnOpenGL");

    float triangle_vertices[] = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f, 0.5f, 0.0f
    };

    while (Window::isOpen())
    {
        if (Window::getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            Window::close();
        }

        Window::update();
    }

    return 0;
}