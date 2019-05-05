#ifndef GRAPHICS_MESH_H
#define GRAPHICS_MESH_H

#include <GL/glew.h>
#include <vector>

#include "Vertex.h"
#include "Texture.h"
#include "Shader.h"

class Mesh
{
public:
    Mesh(const std::vector<Vertex> &vertices, const std::vector<GLushort> &indices,
            Texture *texture = nullptr, Shader *shader = nullptr);
    ~Mesh();

    void Draw();

private:
    void LoadVertices(const std::vector<Vertex> &vertices, const std::vector<GLushort> &indices);

private:
    GLuint                                      m_vao;
    GLuint                                      m_vbo;
    GLuint                                      m_ebo = 0;
    GLsizei                                     m_elCount;

    Texture *                                   m_texture;
    Shader *                                    m_shader;
};

#endif