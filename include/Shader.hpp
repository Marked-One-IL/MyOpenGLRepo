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
    static GLuint compileShader(const char *shaderPath, GLenum mode);
    static std::optional<std::string> getShaderError(GLuint shader, GLenum mode, const char* shaderPath);

    static GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);
    static std::optional<std::string> getProgramError(GLuint program, const char *vertexShaderPath, const char *fragmentShaderPath);

    GLint getUniform(const char *name);

    GLuint m_program = 0;
};