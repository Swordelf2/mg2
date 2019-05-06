#include "CollideEntity.h"
#include "ParticleEntity.h"
#include "../App.h"
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

CollideEntity::CollideEntity(glm::vec3 startPos, glm::vec3 moveDir,
        Mesh *mesh, Shader *shader, Texture *texture) :
    RotateEntity(mesh, shader, texture),
    m_startPos(startPos),
    m_moveDir(moveDir)
{
    m_position = m_startPos;
    m_moveSpeed = App::GetRand(2.5, 4.0);
    m_rotSpeed *= 2.5;
    m_scale *= 0.35;
}

void CollideEntity::Update()
{
    RotateEntity::Update();
    m_position += m_moveDir * static_cast<float>(m_moveSpeed * App::app->GetDeltaTime());
    // Collision
    for (Entity *entity : App::app->m_entities) {
        if (entity == this) {
            continue;
        }
        glm::vec3 diff = entity->GetPosition() - m_position;
        if (diff.x * diff.x + diff.y * diff.y <= 0.01) {
            glm::vec3 myPos = m_position;
            Collide(entity->GetPosition());
            dynamic_cast<CollideEntity *>(entity)->Collide(myPos);
        }
    }
    if (m_position.x < -16.0 || m_position.x > 16.0) {
        m_position = m_startPos;
    }
}

void CollideEntity::Collide(glm::vec3 otherPos)
{
    glm::vec3 collDir = glm::normalize(m_position - otherPos);
    int parType;
    int parCount;
    if (m_mesh == &App::app->m_meshes[App::MESH_CUBE]) {
        parType = App::MESH_SQUARE;
        parCount = 6;
    } else {
        parType = App::MESH_TRIANGLE;
        parCount = 4;
    }

    for (int i = 0; i < parCount; ++i) {
        float angle = App::GetRand(glm::radians(-30.0), glm::radians(30.0));
        glm::mat4 t(1.0);
        t = glm::rotate(t, angle, glm::vec3(0.0, 0.0, 1.0));
        glm::vec3 newDir = t * glm::vec4(collDir, 1.0);
        new ParticleEntity(m_position, newDir,
                &App::app->m_meshes[parType],
                &App::app->m_shaders[App::SHADER_BASIC],
                nullptr);
    }
    m_position = m_startPos;
    m_moveSpeed = App::GetRand(2.5, 4.0);
}