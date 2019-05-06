#ifndef APP_H
#define APP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Entity.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "entities/Background.h"

#define M_PI           3.14159265358979323846

class App
{
public:
    App() = default;
    ~App();

public:
    int Execute();

    double GetDeltaTime() const;
    double GetTime() const;
public:
    static const App *                           app;

public:
    static double GetRand(double l, double r); // generated random value in [l, r)

private:
    int Init();
    void Update();
    void Render();
    
private:
    int                                          m_screenWidth;
    int                                          m_screenHeight;
    GLFWwindow *                                 m_window;
    bool                                         m_running = true;
    double                                       m_time;
    double                                       m_prevTime;
    double                                       m_deltaTime;

    // Entities
    Background *                                 m_background;
    std::vector<Entity *>                        m_entities;
    void InitEntities();

    // Meshes
    enum {
        MESH_TRIANGLE = 0,
        MESH_SQUARE,
        MESH_CUBE,
        MESH_TETR
    };
    std::vector<Mesh>                            m_meshes;
    void InitMeshes();

    // Shaders
    enum {
        SHADER_BASIC = 0,
        SHADER_BACKGROUND
    };
    std::vector<Shader>                          m_shaders;
    void InitShaders();

    // Textures
    enum {
        TEXTURE_PURPLE = 0,
        TEXTURE_SPACE
        TEXTURE_RAINBOW
    };
    std::vector<Texture>                         m_textures;
    void InitTextures();

    static void APIENTRY debugCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar *message,
        const void *userParam);
};

#endif
