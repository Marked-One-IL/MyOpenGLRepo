#pragma once
#include <Window.hpp>
#include <Shader.hpp>
#include <Mesh.hpp>
#include <glad/glad.h>
#include <glm/glm.hpp>

class Texture
{
public:
    Texture(const char *texturePath);
    ~Texture();

    void draw(glm::vec2 offset, glm::vec2 size, float degrees);

private:
    void construct(const char *texturePath);
    void destruct();

    static void constructGlobalData();
    static void destructGlobalData();

    static Shader g_shader;
    static Mesh g_mesh;
    GLuint m_texture = 0;

    friend class Window; // Construct and destruct global data.
};