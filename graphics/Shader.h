#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

#include <GL/glew.h>
#include <string>

class Shader
{
public:
    Shader(const std::string &vertPath, const std::string &fragPath);

    void Use();

    ~Shader();

private:
    static GLuint CompileShader(const std::string &source, GLenum type);

}
#endif
