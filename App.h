#ifndef APP_H
#define APP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Shader.h"

class App
{
public:
    App() = default;

public:
    int Execute();

private:
    int Init();
    void Update();
    void Render();


    
private:
    GLFWwindow *m_window;
    bool m_running = true;

    Shader m_shader;


    static void APIENTRY debugCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar *message,
        const void *userParam);
};

#endif
