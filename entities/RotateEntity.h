#ifndef ENTITIES_ROTATEENTITY_H
#define ENTITIES_ROTATEENTITY_H

#include "../graphics/Entity.h"
class RotateEntity : public Entity
{
public:
    RotateEntity(Mesh *mesh = nullptr, Shader *shader = nullptr, Texture *texture = nullptr);
    RotateEntity(double rotSpeed, glm::vec3 rotAxis, Mesh *mesh = nullptr, Shader *shader = nullptr,
            Texture *texture = nullptr);
    virtual ~RotateEntity() = default;

    virtual void Update();

private:
    double                                       m_rotSpeed;
};

#endif