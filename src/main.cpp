#include <iostream>
#include <filesystem>
#include <format>
#include <Window.hpp>
#include <Shader.hpp>
#include <Mesh.hpp>
#include <Texture.hpp>
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
        Texture texture("image.png");
        Texture texture2("image2.jpg");

        glm::vec2 pos (0.0f, 0.0f);
        const float STEP = 0.01f;
        const int fps = 0;
        while (Window::isOpen())
        {
            Window::updateKeys();
            if (Window::getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                Window::close();
            }

            glClearColor(0.16f, 0.16f, 0.16f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            texture2.use();

            if (Window::getKey(GLFW_KEY_W) == GLFW_PRESS) {
                pos.y -= STEP;
            }
            if (Window::getKey(GLFW_KEY_S) == GLFW_PRESS) {
                pos.y += STEP;
            }
            if (Window::getKey(GLFW_KEY_A) == GLFW_PRESS) {
                pos.x -= STEP;
            }
            if (Window::getKey(GLFW_KEY_D) == GLFW_PRESS) {
                pos.x += STEP;
            }

            Shader &shader = Texture::getShader();

            shader.setUniformVec2("pos", glm::vec2(0.0f, 0.0f));
            texture2.use();

            shader.setUniformVec2("pos", pos);
            texture.use();

            std::cout << Window::getFps() << '\n';

            Window::updateFrame();
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }

    return 0;
}