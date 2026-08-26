#include <iostream>
#include <filesystem>
#include <Window.hpp>

#include <stb_image.h>
#include <glm/glm.hpp>

// #define READY_TO_DISTRIBUTE

int main()
{
#ifndef READY_TO_DISTRIBUTE
    std::filesystem::current_path(PROJECT_ROOT);
#endif

    Window::create(800, 600, "LearnOpenGL");

    float triangle_vertices[] = 
    {
       -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };




    //unsigned int VBO;
    //glGenBuffers(1, &VBO);
    //glBindBuffer(GL_ARRAY_BUFFER, VBO);
    //glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

    while (Window::isOpen())
    {
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (Window::getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            Window::close();
        }

        Window::update();
    }

    return 0;
}