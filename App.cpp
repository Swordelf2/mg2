#include <GL/glew.h>

#include "App.h"

#include <GLFW/glfw3.h>
#include <iostream>

int App::Execute()
{
    if (Init() == -1) {
        return -1;
    }

    while (running) {
        Update();
        Render();

        if (glfwWindowShouldClose(window) == GL_TRUE) {
            running = false;
        }
    }

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

void App::Update()
{
    glfwPollEvents();
}

void App::Render()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);
}

int App::Init()
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Init GLEW */
    if (glewInit() != GLEW_OK) {
        std::cerr << "Error!" << std::endl;
    }

    const char *ver = (const char *) glGetString(GL_VERSION);
    std::cout << ver << std::endl;

    // Set the debug callback function
    glEnable(GL_DEBUG_OUTPUT);
    glDebugMessageCallback(App::debugCallback, nullptr);

    return 0;
}

void App::debugCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar *message,
        const void *userParam)
{
    std::cerr << "OpenGL error occurred. Message: " << std::endl <<
        std::string(message, length) << std::endl;
}
