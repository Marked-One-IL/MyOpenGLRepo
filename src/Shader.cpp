#include <Shader.hpp>
#include <Common.hpp>
#include <stdexcept>
#include <filesystem>
#include <format>

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    this->construct(vertexShaderPath, fragmentShaderPath);
}
Shader::~Shader()
{
    if (this->m_program) {
        glDeleteProgram(this->m_program);
    }
}

void Shader::construct(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    GLuint vertexShader = Shader::compileShader(vertexShaderPath, GL_VERTEX_SHADER);
    if (auto e = Shader::getShaderError(vertexShader, GL_VERTEX_SHADER, vertexShaderPath)) {
        glDeleteShader(vertexShader);
        throw Common::RuntimeFailure(e.value());
    }

    GLuint fragmentShader = Shader::compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
    if (auto e = Shader::getShaderError(fragmentShader, GL_FRAGMENT_SHADER, fragmentShaderPath)) {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        throw Common::RuntimeFailure(e.value());
    }

    this->m_program = Shader::createProgram(vertexShader, fragmentShader);
    if (auto e = Shader::getProgramError(this->m_program, vertexShaderPath, fragmentShaderPath))
    {
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(this->m_program);
        this->m_program = 0;
        throw Common::RuntimeFailure(e.value());
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
} 
void Shader::use()
{
    glUseProgram(this->m_program);
}

void Shader::setUniformVec3(const char *name, glm::vec3 v)
{
    glUniform3f(this->getUniform(name), static_cast<GLfloat>(v.x), static_cast<GLfloat>(v.y), static_cast<GLfloat>(v.z));
}
void Shader::setUniformVec2(const char *name, glm::vec2 v)
{
    glUniform2f(this->getUniform(name), static_cast<GLfloat>(v.x), static_cast<GLfloat>(v.y));
}
void Shader::setUniformFloat(const char *name, float v)
{
    glUniform1f(this->getUniform(name), static_cast<GLfloat>(v));
}
void Shader::setUniformUint(const char *name, unsigned int v)
{
    glUniform1ui(this->getUniform(name), static_cast<GLuint>(v));
}
void Shader::setUniformInt(const char *name, int v)
{
    glUniform1i(this->getUniform(name), static_cast<GLint>(v));
}
void Shader::setUniformBool(const char *name, bool v)
{
    glUniform1i(this->getUniform(name), static_cast<GLint>(v));
}

GLuint Shader::compileShader(const char *shaderPath, GLenum mode)
{
    std::string shaderCode = Common::readFile(std::filesystem::path("assets") / "shaders" / shaderPath);
    const char *shaderCodeCstr = shaderCode.c_str();
    GLuint shader = glCreateShader(mode);
    glShaderSource(shader, 1, &shaderCodeCstr, nullptr);
    glCompileShader(shader);
    return shader;
}
std::optional<std::string> Shader::getShaderError(GLuint shader, GLenum mode, const char* shaderPath)
{
    GLint success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        GLint logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::string error(static_cast<std::size_t>(logLength), '\0');
        glGetShaderInfoLog(shader, logLength, nullptr, &error[0]);
        return std::format("Failed to compile {} shader '{}':\n{}", mode == GL_VERTEX_SHADER ? "vertex" : "fragment", shaderPath, error);
    }

    return std::nullopt;
}

GLuint Shader::createProgram(GLuint vertexShader, GLuint fragmentShader)
{
    GLuint program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    return program;
}
std::optional<std::string> Shader::getProgramError(GLuint program, const char *vertexShaderPath, const char *fragmentShaderPath)
{
    GLint success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        GLint logLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::string error(static_cast<std::size_t>(logLength), '\0');
        glGetProgramInfoLog(program, logLength, nullptr, &error[0]);
        return std::format("Failed to link {} and {}:\n{}", vertexShaderPath, fragmentShaderPath, error);
    }

    return std::nullopt;
}

GLint Shader::getUniform(const char *name)
{
    GLint location = glGetUniformLocation(this->m_program, name);
    LOGICAL_FAILURE(location != -1, "Could not get the location of uniform '{}'", name);
    return location;
}