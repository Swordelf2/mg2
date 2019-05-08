#ifndef ENTITIES_MIRRORENTITY_H
#define ENTITIES_MIRRORENTITY_H

#include "../graphics/Entity.h"

class MirrorEntity : public Entity {
public:
    MirrorEntity(Mesh *mesh = nullptr, Shader *shader = nullptr, Texture *texture = nullptr);
    virtual ~MirrorEntity() = default;

    virtual void Draw(const glm::mat4 &pv) const;

    glm::vec4                                    m_basicColor;
};

#endif
