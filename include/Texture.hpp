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

    void use();
    static Shader& getShader();

private:
    static void buildGlobalData();

    static Shader g_shader;
    static Mesh g_mesh;
    GLuint m_texture = 0;

    friend class Window;
};