#include <iostream>
#include <filesystem>
#include <format>
#include <Window.hpp>
#include <Shader.hpp>
#include <Mesh.hpp>
#include <Texture.hpp>
#include <Utils.hpp>
#include <glm/glm.hpp>
#include <stb_image.h>

int main()
{
    try
    {
        Utils::runtimeSetup();
        Window::create(1000, 1000, "LearnOpenGL");
        Texture texture("image.png");
        Texture texture2("image2.jpg");

        glm::vec2 pos (0.0f, 0.0f);
        const float STEP = 0.01f;
        while (Window::isOpen())
        {
            Window::updateKeys();
            Window::fillScreen(glm::vec3(0.16f, 0.16f, 0.16f));

            if (Window::getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                Window::close();
            }

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

            texture2.draw(glm::vec2(0.0f, 0.0f));
            texture.draw(pos);   

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