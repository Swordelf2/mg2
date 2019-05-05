#include "Entity.h"
#include "../App.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

Entity::Entity(Mesh *mesh, Shader *shader, Texture *texture) :
    m_mesh(mesh),
    m_shader(shader),
    m_texture(texture)
{
}

void Entity::Update()
{
    m_angle = sin(App::app->GetTime());
}

void Entity::Draw(const glm::mat4 &pv) const
{
    if (!m_mesh) {
        return;
    }
    if (m_shader) {
        glm::mat4 t = glm::translate(pv, m_position);
        t = glm::rotate(pv, m_angle, glm::normalize(glm::vec3(1.0, 1.0, 1.0)));
        m_shader->SetUniform("fullTransform", t);
        m_shader->Use();
    }
    if (m_texture) {
        m_texture->Bind();
    }
    m_mesh->Draw();
}