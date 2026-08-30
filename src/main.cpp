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

        glm::vec2 offset (0.0f, 0.0f);
        float size = 1.0f;
        float degrees = 0.0f;

        const float STEP = 0.01f;
        const float SIZE_INCREASE = 0.01f;
        const float DEGREES_INCREASE = 1.0f;
        while (Window::isOpen())
        {
            Window::updateKeys();
            Window::fill(glm::vec3(0.16f, 0.16f, 0.16f));

            if (Window::getKey(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
                Window::close();
            }

            if (Window::getKey(GLFW_KEY_W) == GLFW_PRESS) {
                offset.y -= STEP;
            }
            if (Window::getKey(GLFW_KEY_S) == GLFW_PRESS) {
                offset.y += STEP;
            }
            if (Window::getKey(GLFW_KEY_A) == GLFW_PRESS) {
                offset.x -= STEP;
            }
            if (Window::getKey(GLFW_KEY_D) == GLFW_PRESS) {
                offset.x += STEP;
            }

            if (Window::getKey(GLFW_KEY_UP) == GLFW_PRESS) {
                size += SIZE_INCREASE;
            }
            if (Window::getKey(GLFW_KEY_DOWN) == GLFW_PRESS) {
                size -= SIZE_INCREASE;
                if (size <= 0.0f) {
                    size = 0.0f;
                }
            }
            if (Window::getKey(GLFW_KEY_LEFT) == GLFW_PRESS) {
                degrees += DEGREES_INCREASE;
                if (degrees >= 360.0f) {
                    degrees -= 360.0f;
                }        
            }
            if (Window::getKey(GLFW_KEY_RIGHT) == GLFW_PRESS) {
                degrees -= DEGREES_INCREASE;
                if (degrees <= -360.0f) {
                    degrees += 360.0f;
                }  
            }

            texture2.draw(glm::vec2(0.0f, 0.0f), 1.5f, 0.0f);
            texture.draw(offset, size, degrees);

            std::cout << degrees << '\n';

            Window::updateFrame();
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }

    return 0;
}