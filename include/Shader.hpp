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
    static unsigned int compileShader(const char *shaderPath, GLenum mode);
    static std::optional<std::string> getShaderError(unsigned int shader, GLenum mode, const char* shaderPath);

    static unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader);
    static std::optional<std::string> getProgramError(unsigned int program, const char *vertexShaderPath, const char *fragmentShaderPath);

    int getUniform(const char *name);

    unsigned int m_program = 0;
};