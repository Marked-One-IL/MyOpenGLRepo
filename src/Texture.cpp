#include <Texture.hpp>
#include <Common.hpp>
#include <filesystem>
#include <string>
#include <stb_image.h>

Shader Texture::g_shader;
Mesh Texture::g_mesh;

Texture::Texture(const char *texturePath)
{
    int width = 0, height = 0, nrChannels = 0;
    std::string path = (std::filesystem::path("assets") / "textures" / texturePath).string();
    unsigned char *data = stbi_load(path.c_str(), &width, &height, &nrChannels, STBI_rgb_alpha);
    if (nullptr == data) {
        throw Common::RuntimeFailure("Could not open image '{}'", path);
    }

    glGenTextures(1, &this->m_texture);
    glBindTexture(GL_TEXTURE_2D, this->m_texture);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);
}
Texture::~Texture()
{
    glDeleteTextures(1, &this->m_texture);
}

void Texture::use()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, this->m_texture);
    Texture::g_shader.setUniformInt("textureUnit", 0);
    Texture::g_shader.use();
    Texture::g_mesh.use(0, 6);
}
Shader& Texture::getShader()
{
    return Texture::g_shader;
}

void Texture::buildGlobalData()
{
    static GLfloat vertices[] = {
        // Position         // TexCoord
       -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
       -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
        0.5f,  0.5f, 0.0f,  1.0f, 1.0f
    };
    static GLuint indices[] = {
        0, 1, 2,
        1, 3, 2
    };

    Texture::g_shader.construct("texture.vert", "texture.frag");
    Texture::g_mesh.construct(vertices, sizeof(vertices), indices, sizeof(indices));
    Texture::g_mesh.setLocation(0, 3, 0, 5);
    Texture::g_mesh.setLocation(1, 2, 3, 5);
}