#include <GL/glew.h>

#include "App.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include "graphics/Shader.h"
#include "graphics/Texture.h"

int App::Execute()
{
    if (Init() == -1) {
        return -1;
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);

    /* Test code */
    GLuint ibo, vao, vbo[3];
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    GLfloat positions[] = {
        0.5, 0.5,
        -0.5, 0.5,
        -0.5, -0.5,
        0.5, -0.5
    };

    GLfloat colors[] = {
        1.0, 0.0, 0.0,
        0.0, 1.0, 0.0,
        0.0, 0.0, 1.0,
        1.0, 1.0, 0.0
    };

    GLfloat texCoords[] = {
        1.0, 1.0,
        0.0, 1.0,
        0.0, 0.0,
        1.0, 0.0
    };

    GLubyte indices[] = {
        0, 1, 2,
        2, 3, 0
    };

    glGenBuffers(3, vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texCoords), texCoords, GL_STATIC_DRAW);
    glVertexAttribPointer(2, 2, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(2);

    glGenBuffers(1, &ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glActiveTexture(GL_TEXTURE0);
    Texture texture;
    texture.Load("res/heart.png");
    texture.Bind();
    m_shader.Load("graphics/shaders/test.vert", "graphics/shaders/test.frag");
    m_shader.SetUniform("my_sampler", 0);

    glClearColor(1.0, 0.0, 1.0, 0.0);
    /* Test code ends here*/

    while (m_running) {
        Update();
        Render();

        if (glfwWindowShouldClose(m_window) == GL_TRUE) {
            m_running = false;
        }
    }

    glfwDestroyWindow(m_window);
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
    m_shader.Use();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_BYTE, nullptr);

    glfwSwapBuffers(m_window);
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
    m_window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!m_window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(m_window);

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
    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION) {
        std::cerr << "OpenGL debug. Message: " << std::endl <<
            std::string(message, length) << std::endl;
    }
}
#pragma GCC diagnostic pop
