#include <Shader.hpp>
#include <Common.hpp>
#include <stdexcept>
#include <filesystem>
#include <format>

Shader::Shader(const char *vertexShaderPath, const char *fragmentShaderPath)
{
    unsigned int vertexShader = Shader::compileShader(vertexShaderPath, GL_VERTEX_SHADER);
    if (auto e = Shader::getShaderError(vertexShader, GL_VERTEX_SHADER, vertexShaderPath)) {
        glDeleteShader(vertexShader);
        throw Common::RuntimeFailure(e.value());
    }

    unsigned int fragmentShader = Shader::compileShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
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
Shader::~Shader(void)
{
    if (this->m_program) {
        glDeleteProgram(this->m_program);
    }
}

void Shader::use(void)
{
    glUseProgram(this->m_program);
}

unsigned int Shader::compileShader(const char *shaderPath, GLenum mode)
{
    std::string shaderCode = Common::readFile(std::filesystem::path("assets") / "shaders" / shaderPath);
    const char *shaderCodeCstr = shaderCode.c_str();
    unsigned int shader = glCreateShader(mode);
    glShaderSource(shader, 1, &shaderCodeCstr, nullptr);
    glCompileShader(shader);
    return shader;
}
std::optional<std::string> Shader::getShaderError(unsigned int shader, GLenum mode, const char* shaderPath)
{
    int success = 0;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        int logLength = 0;
        glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLength);
        std::string error(static_cast<std::size_t>(logLength), '\0');
        glGetShaderInfoLog(shader, logLength, nullptr, &error[0]);
        return std::format("Failed to compile {} shader '{}':\n{}", mode == GL_VERTEX_SHADER ? "vertex" : "fragment", shaderPath, error);
    }

    return std::nullopt;
}

unsigned int Shader::createProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
    unsigned int program = glCreateProgram();
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    return program;
}
std::optional<std::string> Shader::getProgramError(unsigned int program, const char *vertexShaderPath, const char *fragmentShaderPath)
{
    int success = 0;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success)
    {
        int logLength = 0;
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength);
        std::string error(static_cast<std::size_t>(logLength), '\0');
        glGetProgramInfoLog(program, logLength, nullptr, &error[0]);
        return std::format("Failed to link {} and {}:\n{}", vertexShaderPath, fragmentShaderPath, error);
    }

    return std::nullopt;
}

int Shader::getUniform(const char *name)
{
    int location = glGetUniformLocation(this->m_program, name);
    LOGICAL_FAILURE(location != -1, "Could not get the location of uniform '{}'", name);
    return location;
}