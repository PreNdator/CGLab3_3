#pragma once
#include "Buffer.h"
#include <vector>

class VAO : public Buffer {
public:
    VAO() : _id(0) {}
    VAO(GLuint id) : _id(id) {}

    void create() override {
        glGenVertexArrays(1, &_id);
        glGenBuffers(1, &_id);
    }

    void destroy() override {
        glDeleteVertexArrays(1, &_id);
        glDeleteBuffers(1, &_id);
    }

    void release() {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
    }

    void bind() override {
        glBindBuffer(GL_ARRAY_BUFFER, _id);
        glBindVertexArray(_id);
    }

    template<typename T>
    void setData(const std::vector<T>& data) {
        create();
        bind();

        glBufferData(GL_ARRAY_BUFFER, sizeof(T) * data.size(), data.data(), GL_STATIC_DRAW);
    }

    void setAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) {
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        glEnableVertexAttribArray(index);
    }

    void allocate(void* data, unsigned int size) {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

private:
    GLuint _id;
};