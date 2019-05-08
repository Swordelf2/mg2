#include "MirroredEntity.h"
#include "../App.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

MirroredEntity::MirroredEntity(double startAngle, int hoverDir,
        Mesh *mesh, Shader *shader, Texture *texture) :
    RotateEntity(mesh, shader, texture),
    m_circleAngle(startAngle),
    m_hoverDir(hoverDir)
{
    m_startPos = {0, 1.9, 0.0};
    m_rotSpeed = App::GetRand(3.0, 5.0);
    m_radius = 4.5;
    m_scale *= 0.5;
}

void MirroredEntity::Update()
{
    RotateEntity::Update();

    m_circleAngle += 3.5 * App::app->GetDeltaTime() * glm::radians(10.0);
    m_position = m_startPos + static_cast<float>(m_radius) * glm::vec3(
            static_cast<float>(std::sin(m_circleAngle)),
            0.0f,
            static_cast<float>(std::cos(m_circleAngle))) +
        1.30f * static_cast<float>(std::sin(4.0 * App::app->GetTime())) *
            glm::vec3(0.0f, static_cast<float>(m_hoverDir), 0.0f);
}

void MirroredEntity::Draw(const glm::mat4 &pv) const
{
    RotateEntity::Draw(pv);

    // Draw reflection
    glm::mat4 pvs = glm::scale(pv, glm::vec3(1.0f, -1.0f, 1.0f));
    RotateEntity::Draw(pvs);
}
