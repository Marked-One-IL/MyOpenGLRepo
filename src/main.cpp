#include <iostream>
#include <filesystem>
#include <Window.hpp>
#include <Shader.hpp>
#include <Common.hpp>
#include <format>

#include <stb_image.h>
#include <glm/glm.hpp>

// #define READY_TO_DISTRIBUTE

int main()
{
    try
    {
#ifndef READY_TO_DISTRIBUTE
        std::filesystem::current_path(PROJECT_ROOT);
#endif

        Window::create(1000, 1000, "LearnOpenGL");
        Shader shader("triangle.vs", "triangle.fs");

        float vertices[] = {
            // position          // color
           -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // red
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // green
            0.0f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f  // blue
        };
        
        unsigned int VAO = 0;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        unsigned int VBO = 0;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        glEnableVertexAttribArray(0); // layout (location = 0)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(1); // layout (location = 1)
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));

        // Reset
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);

        while (Window::isOpen())
        {
            Window::updateKeys();
            if (Window::getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                Window::close();
            }

            glClearColor(0.16f, 0.16f, 0.16f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.use();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            Window::updateFrame();
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }

    return 0;
}