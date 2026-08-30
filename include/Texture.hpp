#pragma once
#include <Shader.hpp>
#include <Mesh.hpp>
#include <Window.hpp>
#include <glad/glad.h>

class Texture
{
public:
    Texture(const char *texturePath);
    ~Texture();

    void construct(const char *texturePath);
    void destruct();

    void use();
    static Shader& getShader();

private:
    static void constructGlobalData();
    static void destructGlobalData();

    static Shader g_shader;
    static Mesh g_mesh;
    GLuint m_texture = 0;

    friend class Window; // Construct and destruct global data.
};