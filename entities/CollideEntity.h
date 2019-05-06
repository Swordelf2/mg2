#ifndef ENTITIES_COLLIDEENTITY_H
#define ENTITIES_COLLIDEENTITY_H

#include "RotateEntity.h"

class CollideEntity : public RotateEntity
{
public:
    CollideEntity(glm::vec3 startPos, glm::vec3 moveDir, Mesh *mesh = nullptr,
            Shader *shader = nullptr, Texture *texture = nullptr);
    virtual ~CollideEntity() = default;

    virtual void Update();

    void Collide(glm::vec3 otherPos);

private:
    glm::vec3                                           m_startPos;
    glm::vec3                                           m_moveDir;
    double                                              m_moveSpeed;
};

#endif