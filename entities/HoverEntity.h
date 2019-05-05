#ifndef ENTITIES_HOVERENTITY_H
#define ENTITIES_HOVERENTITY_H

#include "RotateEntity.h"

class HoverEntity : public RotateEntity
{
public:
    HoverEntity(Mesh *mesh = nullptr, Shader *shader = nullptr, Texture *texture = nullptr);
    virtual ~HoverEntity() = default;

    virtual void Update();
    virtual void Draw(const glm::mat4 &pv) const;

private:
    double                                              m_spawnTime;
    glm::vec3                                           m_hoverAxis;
    double                                              m_hoverSpeed;
    double                                              m_hoverLength;
    glm::vec3                                           m_startPosition;
    glm::vec4                                           m_basicColor;
};

#endif