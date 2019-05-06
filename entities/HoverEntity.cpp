#include "HoverEntity.h"
#include "../App.h"
#include <cmath>

HoverEntity::HoverEntity(Mesh *mesh, Shader *shader, Texture *texture) :
    RotateEntity(mesh, shader, texture)
{
    m_spawnTime = App::app->GetTime();
    double angle = App::GetRand(0.0, M_PI);
    m_hoverAxis = glm::vec3(cos(angle), sin(angle), 0.0);
    m_hoverSpeed = App::GetRand(2.0, 4.0);
    m_hoverLength = App::GetRand(0.6, 0.9);

    m_startPosition = glm::vec3(App::GetRand(-10.0, 10.0), App::GetRand(-5.5, 5.5), 
            App::GetRand(-9.0, 1.5));

        // #009688 • #35a79c - greens both
        // transparency set here
    glm::vec4 colorPalette[7] = {
        {0xfe/255.0, 0x4a/255.0, 0x49/255.0, 0.45},
        {0x2a/255.0, 0xb7/255.0, 0xca/255.0, 0.45},
        {0xfe/255.0, 0xd7/255.0, 0x66/255.0, 0.45},
        {0xf6/255.0, 0xab/255.0, 0xb6/255.0, 0.45},
        {0x3d/255.0, 0x1e/255.0, 0x6d/255.0, 0.45},
        {0x00/255.0, 0x96/255.0, 0x88/255.0, 0.45},
        {0x0a/255.0, 0x49/255.0, 0xaa/255.0, 0.45}
    };
    m_basicColor = colorPalette[rand() % 7];
    m_scale *= 0.6;
}

void HoverEntity::Update()
{
    RotateEntity::Update();
    m_position = m_startPosition + m_hoverAxis * static_cast<float>(m_hoverLength *
            sin((App::app->GetTime() - m_spawnTime) * m_hoverSpeed));
}

void HoverEntity::Draw(const glm::mat4 &pv) const
{
    if (!m_texture) {
        m_shader->SetUniform("basicColor", m_basicColor);
    }
    RotateEntity::Draw(pv);
}