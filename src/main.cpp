#include <iostream>
#include <cmath>
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
        Utils::initializeRuntime();
        Window::construct(1000, 1000, "LearnOpenGL");
        Texture texture("image.png");
        Texture texture2("image2.jpg");

        glm::vec2 offset (0.0f, 0.0f);
        float size = 1.0f;
        float degrees = 0.0f;

        const float STEP = 0.02f;
        const float SIZE_INCREASE = 0.02f;
        const float DEGREES_INCREASE = 2.0f;
        while (Window::isOpen())
        {
            Window::updateKeys();
            Window::fill(glm::vec3(0.16f, 0.16f, 0.16f));

            if (Window::canProcessLogic())
            {
                if (Window::isKeyPressed(GLFW_KEY_ESCAPE)) {
                    Window::close();
                }

                if (Window::isKeyPressed(GLFW_KEY_W)) {
                    offset.y += STEP;
                }
                if (Window::isKeyPressed(GLFW_KEY_S)) {
                    offset.y -= STEP;
                }
                if (Window::isKeyPressed(GLFW_KEY_A)) {
                    offset.x -= STEP;
                }
                if (Window::isKeyPressed(GLFW_KEY_D)) {
                    offset.x += STEP;
                }

                if (Window::isKeyPressed(GLFW_KEY_UP)) {
                    size += SIZE_INCREASE;
                }
                if (Window::isKeyPressed(GLFW_KEY_DOWN)) {
                    size -= SIZE_INCREASE;
                    if (size <= 0.0f) {
                        size = 0.0f;
                    }
                }
                if (Window::isKeyPressed(GLFW_KEY_LEFT)) {
                    degrees += DEGREES_INCREASE;
                    degrees = std::fmod(degrees, 360.0f);
                }
                if (Window::isKeyPressed(GLFW_KEY_RIGHT)) {
                    degrees -= DEGREES_INCREASE;
                    degrees = std::fmod(degrees, 360.0f);
                }
            }
            texture2.draw(glm::vec2(0.0f, 0.0f), glm::vec2(1.5f, 1.5f), 0.0f);
            texture.draw(offset, glm::vec2(size, size), degrees);

            Window::setTitle("fps: {}", Window::getFps());
            Window::updateFrame();
        }
    }
    catch (const std::exception &e)
    {
        std::cout << e.what();
    }

    Window::destruct();
    return 0;
}