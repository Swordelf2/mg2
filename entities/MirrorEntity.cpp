#include "MirrorEntity.h"

MirrorEntity::MirrorEntity(Mesh *mesh, Shader *shader, Texture *texture) :
    Entity(mesh, shader, texture)
{

    m_basicColor = glm::vec4(
            0xad/255.0, 0xee/255.0, 0xff/255.0, 0.5);
    m_scale *= 100.0;
    m_rotAxis = {1.0, 0.0, 0.0};
    m_angle = glm::radians(90.0);
    m_position = {0.0, 0.0, -5.0};
}

void MirrorEntity::Draw(const glm::mat4 &pv) const
{
    m_shader->SetUniform("basicColor", m_basicColor);
    Entity::Draw(pv);
}
