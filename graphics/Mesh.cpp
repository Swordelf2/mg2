#include "Mesh.h"

Mesh::Mesh(const std::vector<Vertex> &vertices, const std::vector<GLushort> &indices,
        Texture *texture, Shader *shader) :
    m_texture(texture),
    m_shader(shader)
{
    if (indices.empty()) {
        m_elCount = vertices.size();
    } else {
        m_elCount = indices.size();
    }
    LoadVertices(vertices, indices);
}

Mesh::~Mesh()
{
    if (m_ebo) {
        glDeleteBuffers(1, &m_ebo);
    }
    glDeleteBuffers(1, &m_vbo);
    glDeleteVertexArrays(1, &m_vao);
}
    
void Mesh::Draw()
{
    if (m_shader) {
        m_shader->Use();
    }
    if (m_texture) {
        m_texture->Bind();
    }
    glBindVertexArray(m_vao);
    if (m_ebo) {
        glDrawElements(GL_TRIANGLES, m_elCount, GL_UNSIGNED_SHORT, nullptr);
    } else {
        glDrawArrays(GL_TRIANGLES, 0, m_elCount);
    }
}
        

void Mesh::LoadVertices(const std::vector<Vertex> &vertices, const std::vector<GLushort> &indices)
{
    glGenVertexArrays(1, &m_vao);
    glBindVertexArray(m_vao);

    glGenBuffers(1, &m_vbo);
    glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), 
            vertices.data(), GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
            reinterpret_cast<void *>(offsetof(Vertex, pos)));
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(vertices[0]),
            reinterpret_cast<void *>(offsetof(Vertex, texCoords)));

    if (!indices.empty()) {
        glGenBuffers(1, &m_ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]),
                indices.data(), GL_STATIC_DRAW);
    }

    glBindVertexArray(0);
}