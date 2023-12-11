#pragma once
#include "Buffer.h"
#include <vector>

class VertexBuffer : public Buffer {
public:
    VertexBuffer() : _id(0) {}
    VertexBuffer(GLuint id) : _id(id) {}

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
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
    }

    void allocate(void* data, unsigned int size) {
        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

private:
    GLuint _id;
};