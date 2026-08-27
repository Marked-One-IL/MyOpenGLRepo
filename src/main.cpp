#include <iostream>
#include <filesystem>
#include <Window.hpp>
#include <Shader.hpp>

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
        // first triangle
        -0.5f, -0.5f, 0.0f, // bottom-left
        0.5f, -0.5f, 0.0f,  // bottom-right
        0.5f,  0.5f, 0.0f,  // top-right

        // second triangle
        -0.5f, -0.5f, 0.0f, // bottom-left
        0.5f,  0.5f, 0.0f,  // top-right
        -0.5f,  0.5f, 0.0f  // top-left
        }; 

        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0); 
        glBindVertexArray(0);

        while (Window::isOpen())
        {
            glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.use();
            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            if (Window::getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                Window::close();
            }

            Window::update();
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }

    return 0;
}