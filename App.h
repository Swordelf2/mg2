#ifndef APP_H
#define APP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Entity.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"

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
    std::vector<Entity *>                        m_entities;
    void InitEntities();

    // Meshes
    enum {
        MESH_CUBE = 0
    };
    std::vector<Mesh>                            m_meshes;
    void InitMeshes();

    // Shaders
    enum {
        SHADER_BASIC = 0
    };
    std::vector<Shader>                          m_shaders;
    void InitShaders();

    // Textures
    enum {
        TEXTURE_PURPLE = 0
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
