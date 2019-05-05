#include "RotateEntity.h"
#include "../App.h"
#include <cmath>

RotateEntity::RotateEntity(double rotSpeed, glm::vec3 rotAxis, Mesh *mesh, Shader *shader, Texture *texture) :
    Entity(mesh, shader, texture),
    m_rotSpeed(rotSpeed)
{
    m_rotAxis = rotAxis;
}

RotateEntity::RotateEntity(Mesh *mesh, Shader *shader, Texture *texture) :
    Entity(mesh, shader, texture)
{
    m_rotSpeed = App::GetRand(1.5, 6.0);
    m_rotAxis = glm::normalize(glm::vec3(
        App::GetRand(-1.0, 1.0), App::GetRand(-1.0, 1.0), App::GetRand(-1.0, 1.0)));
}

void RotateEntity::Update()
{
    m_angle += m_rotSpeed * App::app->GetDeltaTime();
    if (m_angle > 2 * M_PI) {
        m_angle -= 2.0 * M_PI;
    }
    if (m_angle < 0.0) {
        m_angle += 2.0 * M_PI;
    }
}