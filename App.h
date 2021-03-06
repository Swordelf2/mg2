#ifndef APP_H
#define APP_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "graphics/Entity.h"
#include "graphics/Mesh.h"
#include "graphics/Shader.h"
#include "graphics/Texture.h"
#include "entities/Background.h"
#include "entities/MirrorEntity.h"


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

    glm::vec3                                    m_viewPos;

    // Entities
    Background *                                 m_background = nullptr;
    MirrorEntity *                               m_mirror = nullptr;
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
        TEXTURE_SPACE,
        TEXTURE_RAINBOW,
        TEXTURE_COLORFUL
    };
    std::vector<Texture>                         m_textures;
    void InitTextures();

    // Input
    enum {
        INPUT_1 = 0,
        INPUT_2,
        INPUT_3,
        INPUT_4,
        INPUT_W,
        INPUT_S,
        INPUT_LAST
    };
    bool                                         m_input[INPUT_LAST] = {false};

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
    void InitScene4();

private:
    int                                          m_screenWidth;
    int                                          m_screenHeight;
    GLFWwindow *                                 m_window;
    int                                          m_curScene;

    bool                                         m_running = true;
    double                                       m_time;
    double                                       m_prevTime;
    double                                       m_deltaTime;


    /* Input */
    static void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);

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
