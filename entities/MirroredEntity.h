#ifndef ENTITIES_MIRROREDENTITY_H
#define ENTITIES_MIRROREDENTITY_H

#include "RotateEntity.h"

class MirroredEntity : public RotateEntity
{
public:
    MirroredEntity(double startAngle, int hoverDir, Mesh *mesh = nullptr,
            Shader *shader = nullptr, Texture *texture = nullptr);
    virtual ~MirroredEntity() = default;

    virtual void Update();
    virtual void Draw(const glm::mat4 &pv) const;

private:
    glm::vec3                                           m_startPos;
    double                                              m_circleAngle;
    double                                              m_radius;

    int                                                 m_hoverDir;
};

#endif
