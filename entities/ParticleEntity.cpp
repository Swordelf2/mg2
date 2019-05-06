#include "ParticleEntity.h"
#include "../App.h"
#include <cmath>

ParticleEntity::ParticleEntity(glm::vec3 startPos, glm::vec3 moveDir,
        Mesh *mesh, Shader *shader, Texture *texture) :
    RotateEntity(mesh, shader, texture),
    m_moveDir(moveDir)
{
    m_position = startPos;
    m_moveSpeed = App::GetRand(9.0, 13.0);
    m_rotSpeed *= 7.0;
    m_scale *= 0.15;

    std::list<ParticleEntity *> &parList = App::app->m_particles;
    m_listIt = parList.insert(parList.begin(), this);

        // #009688 • #35a79c - greens both
        // transparency set here
    glm::vec4 colorPalette[7] = {
        {0xfe/255.0, 0x4a/255.0, 0x49/255.0, 1.0},
        {0x2a/255.0, 0xb7/255.0, 0xca/255.0, 1.0},
        {0xfe/255.0, 0xd7/255.0, 0x66/255.0, 1.0},
        {0xf6/255.0, 0xab/255.0, 0xb6/255.0, 1.0},
        {0x3d/255.0, 0x1e/255.0, 0x6d/255.0, 1.0},
        {0x00/255.0, 0x96/255.0, 0x88/255.0, 1.0},
        {0x0a/255.0, 0x49/255.0, 0xaa/255.0, 1.0}
    };
    m_basicColor = colorPalette[rand() % 7];
}

void ParticleEntity::Update()
{
    RotateEntity::Update();
    m_position += m_moveDir * static_cast<float>(m_moveSpeed * App::app->GetDeltaTime());
}

void ParticleEntity::Draw(const glm::mat4 &pv) const
{
    m_shader->SetUniform("basicColor", m_basicColor);
    RotateEntity::Draw(pv);
}