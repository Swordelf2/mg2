#include <GL/glew.h>
#include <string>

#include <iostream>
#include <cstdio>

#define STB_IMAGE_IMPLEMENTATION
#pragma GCC diagnostic ignored "-Wtype-limits"
#include "../deps/stb_image.h"
#pragma GCC diagnostic pop

#include "Texture.h"

void Texture::Load(const std::string &path)
{
    int channels_num;
    stbi_set_flip_vertically_on_load(1);
    unsigned char *image = stbi_load(path.c_str(), &m_width, &m_height, &channels_num, 4);
    std::cout << "first 10 bytes of the image" << std::endl;
    for (int i = 0; i < 10; ++i) {
        printf("%02x ", image[i]);
    }
    std::cout << std::endl;

    glGenTextures(1, &m_id);
    Bind();
    std::cout << "width " << m_width << " height: " << m_height << std::endl;
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);
    std::cout << "here ends\n";

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    /* Optional ? 
    glGenerateMipmap(GL_TEXTURE_2D);
    */

    Unbind();
}

Texture::~Texture()
{
    if (m_id) {
        glDeleteTextures(1, &m_id);
    }
}

void Texture::Bind()
{
    glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::Unbind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}