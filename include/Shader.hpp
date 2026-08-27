#pragma once
#include <string>
#include <glad/glad.h>
#include <optional>

class Shader
{
public:
    Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
    ~Shader(void);

    void use(void);

private:
    unsigned int compileShader(const char *shaderPath, GLenum mode);
    std::optional<std::string> getShaderError(unsigned int shader, GLenum mode, const char* shaderPath);

    unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader);
    std::optional<std::string> getProgramError(unsigned int program, const char *vertexShaderPath, const char *fragmentShaderPath);

    unsigned int m_program = 0;
};