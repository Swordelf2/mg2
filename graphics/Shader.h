#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

#include <GL/glew.h>
#include <string>

class Shader
{
public:
    Shader() = default;

    void Load(const std::string &vertPath, const std::string &fragPath);
    void Use();

    ~Shader();

private:
    GLuint id = 0;

private:
    static GLuint CompileShader(const std::string &source, GLenum type);
};

#endif
