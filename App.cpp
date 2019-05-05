#include <GL/glew.h>

#include "App.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "graphics/Mesh.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>

double App::deltaTime;

int App::Execute()
{
    if (Init() == -1) {
        return -1;
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    /* Test code */
    std::vector<Vertex> vertices = {
        // face 0
        {{-1.0, -1.0,  1.0}, {0.0, 0.0}},
        {{ 1.0, -1.0,  1.0}, {1.0, 0.0}},
        {{ 0.0,  1.0,  0.0}, {0.5, 1.0}},
        //face 1
        {{ 1.0, -1.0,  1.0}, {0.0, 0.0}},
        {{ 0.0, -1.0, -1.0}, {1.0, 0.0}},
        {{ 0.0,  1.0,  0.0}, {0.5, 1.0}},
        //face 2
        {{-1.0, -1.0,  1.0}, {1.0, 0.0}},
        {{ 0.0, -1.0, -1.0}, {0.0, 0.0}},
        {{ 0.0,  1.0,  0.0}, {0.5, 1.0}},
        //face 3
        {{ 1.0, -1.0,  1.0}, {0.0, 0.0}},
        {{-1.0, -1.0,  1.0}, {1.0, 0.0}},
        {{ 0.0, -1.0, -1.0}, {0.5, 1.0}}
    };

    Texture *texture = new Texture("res/container.jpg");
    m_shader = new Shader("graphics/shaders/test.vert", "graphics/shaders/test.frag");
    m_mesh = new Mesh(vertices, {}, texture, m_shader);
    m_shader->SetUniform("my_sampler", 0);

    glClearColor(0x1e / 255.0, 0x39 / 255.0, 0x63 / 255.0, 1.0);
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
    /* Update deltatime */
    double curTime = glfwGetTime();
    deltaTime = curTime - m_prevTime;
    m_prevTime = curTime;

    glfwPollEvents();
}

void App::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Test code */
    // projection
    glm::mat4 t = glm::perspective(static_cast<float>(glm::radians(45.0)),
            static_cast<float>(m_screenWidth) / m_screenHeight,
            0.1f, 100.0f);

    // view
    t = glm::translate(t, glm::vec3(0.0, 0.0, -6.0));
    // transform
    t = glm::translate(t, glm::vec3(std::sin(glfwGetTime()), 0.0, 0.0));
    t = glm::rotate(t, static_cast<float>(glfwGetTime()),
            glm::normalize(glm::vec3(0.0, 1.0, 0.0)));

    m_shader->SetUniform("fullTransform", t);
    m_mesh->Draw();

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
    m_screenWidth = 640;
    m_screenHeight = 480;
    m_window = glfwCreateWindow(m_screenWidth, m_screenHeight, "Hello World", NULL, NULL);
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

    m_prevTime = glfwGetTime();

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
