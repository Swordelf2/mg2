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

const App * App::app;

App::~App()
{
    for (Entity *entity : m_entities) {
        delete entity;
    }
}

int App::Execute()
{
    if (Init() == -1) {
        return -1;
    }

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    glClearColor(0x1e / 255.0, 0x39 / 255.0, 0x63 / 255.0, 1.0);

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

double App::GetDeltaTime() const
{
    return m_deltaTime;
}

double App::GetTime() const
{
    return m_time;
}

void App::Update()
{
    /* Update deltatime */
    m_prevTime = m_time;
    m_time = glfwGetTime();
    m_deltaTime = m_time - m_prevTime;
    
    for (Entity *entity : m_entities) {
        entity->Update();
    }
    glfwPollEvents();
}

void App::Render()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // projection
    glm::mat4 pv = glm::perspective(static_cast<float>(glm::radians(45.0)),
            static_cast<float>(m_screenWidth) / m_screenHeight,
            0.1f, 100.0f);

    // view
    pv = glm::translate(pv, glm::vec3(0.0, 0.0, -6.0));

    // transform
    for (Entity *entity : m_entities) {
        entity->Draw(pv);
    }

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

    m_time = m_prevTime = glfwGetTime();
    m_deltaTime = 0.0;

    app = this;

    InitMeshes();
    InitShaders();
    InitTextures();

    InitEntities();

    return 0;
}

void App::InitEntities()
{
    // cube
    Entity *entity = new Entity(&m_meshes[MESH_CUBE],
            &m_shaders[SHADER_BASIC],
            &m_textures[TEXTURE_PURPLE]);
    m_entities.push_back(entity);
}

void App::InitMeshes()
{
    std::vector<GLushort> emptyInds = {};
    std::vector<Vertex> vertices = {
        {{-0.5f, -0.5f, -0.5f},  {0.0f, 0.0f}},
        {{0.5f, -0.5f, -0.5f},  {1.0f, 0.0f}},
        {{0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f},  {0.0f, 0.0f}},

        {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
        {{0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}},
        {{0.5f,  0.5f,  0.5f},  {1.0f, 1.0f}},
        {{0.5f,  0.5f,  0.5f},  {1.0f, 1.0f}},
        {{-0.5f,  0.5f,  0.5f},  {0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},

        {{-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
        {{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
        {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},

        {{0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
        {{0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
        {{0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
        {{0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},

        {{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},
        {{0.5f, -0.5f, -0.5f},  {1.0f, 1.0f}},
        {{0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}},
        {{0.5f, -0.5f,  0.5f},  {1.0f, 0.0f}},
        {{-0.5f, -0.5f,  0.5f},  {0.0f, 0.0f}},
        {{-0.5f, -0.5f, -0.5f},  {0.0f, 1.0f}},

        {{-0.5f,  0.5f, -0.5f},  {0.0f, 1.0f}},
        {{0.5f,  0.5f, -0.5f},  {1.0f, 1.0f}},
        {{0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
        {{0.5f,  0.5f,  0.5f},  {1.0f, 0.0f}},
        {{-0.5f,  0.5f,  0.5f},  {0.0f, 0.0f}},
        {{-0.5f,  0.5f, -0.5f},  {0.0f, 1.0}}
    };
    m_meshes.emplace_back(vertices, emptyInds);

    vertices = {
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
    m_meshes.emplace_back(vertices, emptyInds);
}

void App::InitShaders()
{
    m_shaders.emplace_back("graphics/shaders/test.vert", "graphics/shaders/test.frag");
    m_shaders[0].SetUniform("texture0", 0);
}

void App::InitTextures()
{
    m_textures.emplace_back("res/purple.jpg");
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
