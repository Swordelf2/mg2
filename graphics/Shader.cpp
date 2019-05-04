#include <GL/glew.h>

#include <fstream>
#include <sstream>
#include <iostream>

#include "Shader.h"

void Shader::Load(const std::string &vertPath, const std::string &fragPath)
{
    std::string vCode, fCode;
    std::ifstream vFile, fFile;
    try {
        vFile.open(vertPath);
        fFile.open(fragPath);
        std::stringstream vStream, fStream;
        vStream << vFile.rdbuf();
        fStream << fFile.rdbuf();
        vFile.close();
        fFile.close();
        vCode = vStream.str();
        fCode = fStream.str();
    } catch (std::ifstream::failure &e) {
        std::cerr << "Error while opening shader source file: " <<
                std::endl;
        std::cerr << e.what() << std::endl;
    }

    GLuint vId, fId;
    vId = CompileShader(vCode, GL_VERTEX_SHADER);
    fId = CompileShader(fCode, GL_FRAGMENT_SHADER);

    id = glCreateProgram();

    glAttachShader(id, vId);
    glAttachShader(id, fId);
    glLinkProgram(id);

    GLint result;
    glGetProgramiv(id, GL_LINK_STATUS, &result);
    if (result != GL_TRUE) {
        char message[1024];
        glGetProgramInfoLog(id, sizeof(message), nullptr, message);
        std::cerr << "Failed to link shader: " << std::endl;
        std::cerr << vertPath << std::endl << fragPath << std::endl;
        std::cerr << message << std::endl;
    }

    glDeleteShader(vId);
    glDeleteShader(fId);
}


Shader::~Shader()
{
    if (id) {
        glDeleteProgram(id);
    }
}

void Shader::Use()
{
    glUseProgram(id);
}

GLuint Shader::CompileShader(const std::string& source, GLenum type)
{
    unsigned id = glCreateShader(type);
    const char *src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    GLint result;
    glGetShaderiv(id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE) {
        // Get the message
        char message[1024];
        glGetShaderInfoLog(id, sizeof(message), nullptr, message);
        std::cerr << "Failed to compile shader!" <<
                (type == GL_VERTEX_SHADER ? "vertex" : "fragment") <<
                std::endl;
        std::cerr << message << std::endl;
        glDeleteShader(id);
        return 0;
    }

    return id;
}
