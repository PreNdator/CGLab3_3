#pragma once
#include "DrawableObject.h"
#include <vector>
#include <string>
#include "Vao.h"
#include "Ebo.h"
#include "ModelLoader.h"

const char* vertex_shader =
"#version 400\n"
"layout (location = 0) in vec3 vPos;"
"layout (location = 1) in vec2 texPos;"
"layout (location = 2) in vec3 normal;"
"out vec3 ourColor;"
"void main()"
"{"
"   gl_Position = vec4(vPos, 1.0);"
"   ourColor = vec3(0.5,0.5,0);"
"}";
const char* fragment_shader =
"#version 400\n"
"out vec4 frag_colour;"
"in vec3 ourColor;"
"void main() {"
" frag_colour = vec4(ourColor, 1.0);"
"}";

class GLModel : public DrawableObject {
public:
    GLModel(std::vector<glm::vec3> vertexData, std::vector<glm::uvec3> indexData):verticies(vertexData), indices(indexData),shader(vertex_shader, fragment_shader) {
        vao.create();
        ebo.create();

        vao.bind();
        ebo.bind();
        ebo.allocate(indices.data(), sizeof(glm::uvec3) * indices.size());

        vao.allocate(verticies.data(), sizeof(glm::vec3) * verticies.size());
        release();
    }

    void bind() override {
        
        vao.bind();
        ebo.bind();
        shader.use();
    }

    void release() override {
        vao.release();
        ebo.release();
    }

    int nVertices() override {
        return indices.size();
    }


private:
    VertexBuffer vao;
    IndexBuffer ebo;
    Shader shader;


    std::vector<glm::vec3> verticies;
    std::vector<glm::uvec3> indices;
};