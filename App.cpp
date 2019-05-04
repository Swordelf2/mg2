#include <GL/glew.h>

#include "App.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include "graphics/Shader.h"

int App::Execute()
{
    if (Init() == -1) {
        return -1;
    }

    /* Test code */
    GLuint vao, vbo;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLfloat positions[] = {
        -0.5, -0.5,
        0.5, -0.5,
        0.0, 0.5
    };

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    shader.Load("graphics/shaders/test.vert", "graphics/shaders/test.frag");
    /* Test code ends here*/

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

    /* Test code */
    shader.Use();
    glDrawArrays(GL_TRIANGLES, 0, 3);

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

#pragma GCC diagnostic ignored "-Wunused-parameter"
void App::debugCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar *message,
        const void *userParam)
{
    std::cerr << "OpenGL debug. Message: " << std::endl <<
        std::string(message, length) << std::endl;
}
#pragma GCC diagnostic pop
