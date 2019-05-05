#ifndef GRAPHICS_SHADER_H
#define GRAPHICS_SHADER_H

#include <GL/glew.h>
#include <string>
#include <unordered_map>
#include <glm/glm.hpp>

class Shader
{
public:
    Shader() = default;
    ~Shader();

    void Load(const std::string &vertPath, const std::string &fragPath);
    void Use();
    void Unuse();
    bool IsUsed() const;

    GLint GetUniLocation(const std::string &uniName);
    void SetUniform(const std::string &name, GLint val);
    void SetUniform(const std::string &name, const glm::mat4 &val);
    
private:
    GLuint                                                  m_id = 0;
    std::unordered_map<std::string, int>                    m_uniLocation;
    static Shader *                                         m_curUsed;

private:
    static GLuint CompileShader(const std::string &source, GLenum type);
};

#endif
