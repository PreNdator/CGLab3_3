#pragma once
#include "DrawableObject.h"
#include <vector>
#include <string>
#include "Vao.h"
#include "Ebo.h"
#include "ModelLoader.h"
#include "Transform.h"

const char* vertex_shader =
"#version 400\n"
"layout (location = 0) in vec3 vPos;"
"uniform mat4 perspective;"
"uniform mat4 transformation;"
"out vec3 ourColor;"
"void main()"
"{"
"   gl_Position = perspective*transformation*vec4(vPos, 1.0);"
"   ourColor = vec3(vPos.x,0,vPos.y);"
"}";
const char* fragment_shader =
"#version 400\n"
"out vec4 frag_colour;"
"in vec3 ourColor;"
"void main() {"
" frag_colour = vec4(ourColor, 1.0);"
"}";

class GLModel : public DrawableObject, public Transform {
public:
    GLModel(std::vector<glm::vec3> vertexData, std::vector<glm::uvec3> indexData):verticies(vertexData), indices(indexData) {
        vao.create();
        ebo.create();

        vao.bind();
        ebo.bind();
        ebo.allocate(indices.data(), sizeof(glm::uvec3) * indices.size());
        
        vao.allocate(verticies.data(), sizeof(glm::vec3) * verticies.size());

        release();
    }

    void bind(Shader& shader) override {  
        vao.bind();
        ebo.bind();
        shader.setMat4("transformation", transformationMatrix());
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


    std::vector<glm::vec3> verticies;
    std::vector<glm::uvec3> indices;
};