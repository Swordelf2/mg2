#ifndef APP_H
#define APP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Shader.h"
#include "graphics/Mesh.h"

class App
{
public:
    App() = default;

public:
    int Execute();

public:
    static double deltaTime;

private:
    int Init();
    void Update();
    void Render();
    
private:
    int                                          m_screenWidth;
    int                                          m_screenHeight;
    GLFWwindow *                                 m_window;
    bool                                         m_running = true;
    double                                       m_prevTime;

    Mesh *                                       m_mesh;
    Shader *                                     m_shader;

    static void APIENTRY debugCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar *message,
        const void *userParam);
};

#endif
