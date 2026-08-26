#pragma once
#include <glad/glad.h>
#include <stdexcept>
#include <array>

namespace Shaders
{
    template <std::size_t N>
    class Compiled
    {
    public:
        Compiled(const char *vertexShader, const char *fragmentShader, std::array<float, N> vertices);
        ~Compiled(void);

    private:
        unsigned int m_vertexShader;
        unsigned int m_fragmentShader;
        unsigned int m_VBO = 0;
        std::array<float, N> m_vertices;
    };
}

template <std::size_t N>
inline Shaders::Compiled<N>::Compiled(const char *vertexShader, const char *fragmentShader, std::array<float, N> vertices) :
    m_vertexShader(glCreateShader(GL_VERTEX_SHADER)), m_fragmentShader(glCreateShader(GL_FRAGMENT_SHADER)), m_vertices(vertices)
{
    glGenBuffers(1, &this->m_VBO);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * this->m_vertices.size(), this->m_vertices, GL_STATIC_DRAW);

    int successStatus;
    char infoLog[512];

    glShaderSource(this->m_vertexShader, 1, &vertexShader, nullptr);
    glCompileShader(this->m_vertexShader);
    glGetShaderiv(this->m_vertexShader, GL_COMPILE_STATUS, &successStatus);
    if (!successStatus) {
        glGetProgramInfoLog(this->m_vertexShader, sizeof(infoLog), nullptr, infoLog);
        throw std::runtime_error(infoLog);
    }

    glShaderSource(this->m_fragmentShader, 1, &fragmentShader, nullptr);
    glCompileShader(this->m_fragmentShader);
    glGetShaderiv(this->m_fragmentShader, GL_COMPILE_STATUS, &successStatus);
    if (!successStatus) {
        glGetProgramInfoLog(this->m_fragmentShader, sizeof(infoLog), nullptr, infoLog);
        throw std::runtime_error(infoLog);
    }

    
}

template <std::size_t N>
Shaders::Compiled<N>::~Compiled(void)
{
    glDeleteShader(this->m_vertexShader);
    glDeleteShader(this->m_fragmentShader);
}