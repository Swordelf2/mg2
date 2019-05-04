#ifndef GRAPHICS_TEXTURE_H
#define GRAPHICS_TEXTURE_H

#include <GL/glew.h>
#include <string>

class Texture
{
public:
    Texture() = default;
    ~Texture();

    void Load(const std::string &path);

    void Bind();
    void Unbind();


private:
    int m_width;
    int m_height;
    GLuint m_id = 0;
};

#endif