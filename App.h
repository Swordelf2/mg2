#ifndef APP_H
#define APP_H

#include <GLFW/glfw3.h>

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
    GLFWwindow *window;
    bool running = true;


    static void APIENTRY debugCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar *message,
        const void *userParam);
};

#endif
