#include <iostream>
#include <filesystem>
#include <format>
#include <Window.hpp>
#include <Shader.hpp>
#include <Common.hpp>
#include <glm/glm.hpp>
#include <stb_image.h>

int main()
{
    try
    {
#ifndef READY_TO_DISTRIBUTE
        Common::clearScreen();
        std::filesystem::current_path(PROJECT_ROOT);
#endif

        Window::create(1000, 1000, "LearnOpenGL");
        Shader shader("triangle.vert", "triangle.frag");

        float vertices[] = {
            // Triangle 1
           -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
           -0.5f,  0.5f, 0.0f,

            // Extra point.
            0.5f,  0.5f, 0.0f,
        };
        // Reuse of the points instead of drawing 2 traingles.
        unsigned int indices[] = {
            0, 1, 2,
            1, 3, 2
        };

        // Shape config.
        unsigned int VAO = 0;
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        // Shape buffer.
        unsigned int VBO = 0;
        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
        
        // Shape points indices (Optional but this allows re-use of points).
        unsigned int EBO = 0;
        glGenBuffers(1, &EBO);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // Shape config (How to interpret data).
        glEnableVertexAttribArray(0); // layout (location = 0)
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

        int count = 1;
        const int LIMIT = 120;
        while (Window::isOpen())
        {
            Window::updateKeys();
            if (Window::getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                Window::setClose(true);
            }

            glClearColor(0.16f, 0.16f, 0.16f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.use();
            glBindVertexArray(VAO);

            if (Window::getKey(GLFW_KEY_SPACE) == GLFW_PRESS) {
                glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0); // Draw left+right triangles (square).
            }
            else if (count < LIMIT) {
                glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)0); // Draw left triangle.
                count++;
            } 
            else if (count < LIMIT * 2) {
                glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(3 * sizeof(unsigned int))); // Draw right triangle.
                count++;
            }
            else {
                count = 1;
            }

            Window::updateFrame();
        }

        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }

    return 0;
}