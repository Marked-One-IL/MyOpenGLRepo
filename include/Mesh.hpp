#pragma once
#include <glad/glad.h>
#include <cstddef>

class Texture;

class Mesh
{
public:
    Mesh  (const GLfloat *vertices, std::size_t verticesSize, const GLuint *indices, std::size_t indicesSize);
    Mesh  (void) = default;
    ~Mesh (void);

    void setLocation (GLuint location, std::size_t singleElementCount, std::size_t offsetCount, std::size_t strideCount);
    void use         (std::size_t offsetCount, std::size_t indicesCount);

private:
    void construct (const GLfloat *vertices, std::size_t verticesSize, const GLuint *indices, std::size_t indicesSize);
    void destruct  (void);

    GLuint m_vao = 0;
    GLuint m_vbo = 0;
    GLuint m_ebo = 0;

    friend class Texture;
};