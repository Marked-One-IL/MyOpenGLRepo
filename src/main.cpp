#include <iostream>
#include <filesystem>
#include <format>
#include <Window.hpp>
#include <Shader.hpp>
#include <Mesh.hpp>
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

        GLfloat vertices[] = {
            // Positions         // Color
           -0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, // Red
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, // Green
           -0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, // Blue
            0.5f,  0.5f, 0.0f,   0.5f, 0.5f, 0.5f, // Some color I forgor
        };
        GLuint indices[] = {
            0, 1, 2,
            1, 3, 2
        };

        Window::create(1000, 1000, "LearnOpenGL");
        Shader shader("triangle.vert", "triangle.frag");
        Mesh mesh(vertices, sizeof(vertices), indices, sizeof(indices));

        mesh.setLocation(0, 3, 0, 6);
        mesh.setLocation(1, 3, 3, 6);

        int count = 1;
        const int LIMIT = 120;
        while (Window::isOpen())
        {
            Window::updateKeys();
            if (Window::getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                Window::close();
            }

            glClearColor(0.16f, 0.16f, 0.16f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.use();

            if (Window::getKey(GLFW_KEY_SPACE) == GLFW_PRESS) {
                mesh.use(0, 6); // Draw left+right triangles (square).
            }
            else if (count < LIMIT) {
                mesh.use(0, 3); // Draw left triangle.
                count++;
            } 
            else if (count < LIMIT * 2) {
                mesh.use(3, 3); // Draw right triangle.
                count++;
            }
            else {
                count = 1;
            }

            Window::updateFrame();
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }

    return 0;
}