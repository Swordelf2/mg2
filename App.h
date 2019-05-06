#ifndef APP_H
#define APP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Entity.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "entities/Background.h"


#include <list>

#define M_PI           3.14159265358979323846

/* Forward declarations */
extern std::pair<std::vector<Vertex>, std::vector<GLushort>> ReadMesh(const std::string &path);
class ParticleEntity;

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
    static App *                           app;

    // Entities
    Background *                                 m_background = nullptr;
    std::vector<Entity *>                        m_entities;
    std::list<ParticleEntity *>                  m_particles;

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
        SHADER_BACKGROUND,
        SHADER_TEXTURED
    };
    std::vector<Shader>                          m_shaders;
    void InitShaders();

    // Textures
    enum {
        TEXTURE_PURPLE = 0,
        TEXTURE_SPACE,
        TEXTURE_RAINBOW
    };
    std::vector<Texture>                         m_textures;
    void InitTextures();

public:
    static double GetRand(double l, double r); // generated random value in [l, r)

private:
    int Init();
    void Update();
    void Render();
    
    void ClearEntities();
    void InitScene1();
    void InitScene2();
    void InitScene3();

private:
    int                                          m_screenWidth;
    int                                          m_screenHeight;
    GLFWwindow *                                 m_window;
    int                                          m_curScene;

    bool                                         m_running = true;
    double                                       m_time;
    double                                       m_prevTime;
    double                                       m_deltaTime;



    /* Debug */
    static void APIENTRY debugCallback(GLenum source,
        GLenum type,
        GLuint id,
        GLenum severity,
        GLsizei length,
        const GLchar *message,
        const void *userParam);
};

#endif
