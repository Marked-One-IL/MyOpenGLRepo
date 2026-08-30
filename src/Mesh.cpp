#include <Mesh.hpp>

Mesh::Mesh(const GLfloat *vertices, std::size_t verticesSize, const GLuint *indices, std::size_t indicesSize)
{
    this->construct(vertices, verticesSize, indices, indicesSize);
}
Mesh::~Mesh()
{
    glDeleteVertexArrays(1, &this->m_vao);
    glDeleteBuffers(1, &this->m_vbo);
    glDeleteBuffers(1, &this->m_ebo);
}

void Mesh::construct(const GLfloat *vertices, std::size_t verticesSize, const GLuint *indices, std::size_t indicesSize)
{
    glGenVertexArrays(1, &this->m_vao);
    glBindVertexArray(this->m_vao);

    glGenBuffers(1, &this->m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
    glBufferData(GL_ARRAY_BUFFER, static_cast<GLsizei>(verticesSize), vertices, GL_STATIC_DRAW);

    glGenBuffers(1, &this->m_ebo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->m_ebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, static_cast<GLsizei>(indicesSize), indices, GL_STATIC_DRAW);
}
void Mesh::setLocation(GLuint location, std::size_t singleElementCount, std::size_t offsetCount, std::size_t strideCount)
{
    glBindVertexArray(this->m_vao);
    glBindBuffer(GL_ARRAY_BUFFER, this->m_vbo);
    glEnableVertexAttribArray(location);

    glVertexAttribPointer(location, static_cast<GLint>(singleElementCount), GL_FLOAT, GL_FALSE,
        static_cast<GLsizei>(strideCount * sizeof(GLfloat)), reinterpret_cast<void*>(offsetCount * sizeof(GLfloat)));
}
void Mesh::use(std::size_t offsetCount, std::size_t indicesCount)
{
    glBindVertexArray(this->m_vao);
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(indicesCount), GL_UNSIGNED_INT, reinterpret_cast<void*>(offsetCount * sizeof(GLuint)));
}