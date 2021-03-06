#include "Entity.h"
#include "../App.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>

Entity::Entity(Mesh *mesh, Shader *shader, Texture *texture) :
    m_mesh(mesh),
    m_shader(shader),
    m_texture(texture)
{
}

void Entity::Update()
{
}

void Entity::Draw(const glm::mat4 &pv) const
{
    if (!m_mesh || !m_shader) {
        std::cerr << "Error: drawing without mesh or shader!" << std::endl;
        return;
    }
    glm::mat4 t = glm::translate(pv, m_position);
    t = glm::scale(t, m_scale);
    t = glm::rotate(t, m_angle, m_rotAxis);
    m_shader->SetUniform("fullTransform", t);
    m_shader->Use();
    if (m_texture) {
        m_texture->Bind();
    }
    m_mesh->Draw();
}

void Entity::SetScale(const glm::vec3 &scale)
{
    m_scale = scale;
}

glm::vec3 Entity::GetPosition() const
{
    return m_position;
}

Mesh *Entity::GetMesh() const
{
    return m_mesh;
}

void Entity::Move(glm::vec3 moveVec)
{
    m_position += moveVec;
}