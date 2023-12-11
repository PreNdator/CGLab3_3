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


    GLModel() {
        vao.create();
        ebo.create();
    }

    void bind() override {
        Shader shader(vertex_shader, fragment_shader);
        vao.bind();
        vao.setAttributePointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        vao.setAttributePointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        vao.setAttributePointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(5 * sizeof(float)));

        vao.allocate(vertexData.data(), sizeof(float) * vertexData.size());
        ebo.bind();
        ebo.allocate(indices.data(), sizeof(glm::uvec3) * indices.size());

        shader.use();
    }



    void release() override {
        vao.release();
        ebo.release();
    }

    int nVertices() override {
        return indices.size();
    }

    void loadModel(const char* filePath) {
        ModelLoader loader;
        if (!loader.isLoad(filePath)) {
            throw std::runtime_error("Failed to load model from file: " + std::string(filePath));
            return;
        }    
        vertexData = loader.getVertices();
        indices = loader.getIndices();
    }

private:
    VAO vao;
    EBO ebo;

    std::vector<float> vertexData;
    std::vector<glm::uvec3> indices;
};