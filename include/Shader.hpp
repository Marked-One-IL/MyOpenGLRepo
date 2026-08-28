#pragma once
#include <string>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <optional>
#include <map>
#include <utility>

class Shader
{
public:
    Shader(const char *vertexShaderPath, const char *fragmentShaderPath);
    ~Shader(void);

    void use(void);

    void setUniformVec3(const char *name, glm::vec3 v);
    void setUniformFloat(const char *name, float v);
    void setUniformUint(const char *name, unsigned int v);
    void setUniformInt(const char *name, int v);
    void setUniformBool(const char *name, bool v);

private:
    static unsigned int compileShader(const char *shaderPath, GLenum mode);
    static std::optional<std::string> getShaderError(unsigned int shader, GLenum mode, const char* shaderPath);

    static unsigned int createProgram(unsigned int vertexShader, unsigned int fragmentShader);
    static std::optional<std::string> getProgramError(unsigned int program, const char *vertexShaderPath, const char *fragmentShaderPath);

    int getUniform(const char *name);

    unsigned int m_program = 0;
};