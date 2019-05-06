#include "GL/glew.h"

#include <utility>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>

#include "graphics/Vertex.h"

std::pair<std::vector<Vertex>, std::vector<GLushort>> ReadMesh(const std::string &path)
{
    std::fstream file;
    std::vector<Vertex> V;
    std::vector<GLushort> I;
    try {
        file.open(path);
        std::stringstream ss;
        ss << file.rdbuf();
        unsigned n;
        ss >> n;
        for (unsigned i = 0; i < n; ++i) {
            glm::vec3 p;
            glm::vec2 tc;
            ss >> p.x >> p.y >> p.z >> tc.x >> tc.y;
            V.push_back({p, tc});
        }
        ss >> n;
        for (unsigned i = 0; i < n; ++i) {
            GLushort ind;
            ss >> ind;
            I.push_back(ind);
        }
    } catch (std::fstream::failure &e) {
        std::cerr << "Could not open mesh file: " << path << std::endl;
        std::cerr << e.what() << std::endl;
    }
    return {V, I};
}