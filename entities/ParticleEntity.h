#ifndef ENTITIES_PARTICLEENTITY_H
#define ENTITIES_PARTICLEENTITY_H

#include "../App.h"
#include "RotateEntity.h"
#include <list>

class ParticleEntity : public RotateEntity
{
public:
    ParticleEntity(glm::vec3 startPos, glm::vec3 moveDir, Mesh *mesh = nullptr,
            Shader *shader = nullptr, Texture *texture = nullptr);
    virtual ~ParticleEntity() = default;

    virtual void Update();
    virtual void Draw(const glm::mat4 &pv) const;

private:
    glm::vec3                                           m_moveDir;
    double                                              m_moveSpeed;

    glm::vec4                                           m_basicColor;

    std::list<ParticleEntity *>::iterator               m_listIt;
};

#endif