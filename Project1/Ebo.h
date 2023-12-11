#pragma once
#include "Buffer.h"


class IndexBuffer : public Buffer {
public:
    IndexBuffer() : _id(0) {}
    IndexBuffer(GLuint id) : _id(id) {}

    void create() override {
        glGenBuffers(1, &_id);
    }

    void destroy() override {
        glDeleteBuffers(1, &_id);
    }

    virtual void release() {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void bind() override {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    }

    void setAttributePointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const GLvoid* pointer) {
        glVertexAttribPointer(index, size, type, normalized, stride, pointer);
        glEnableVertexAttribArray(index);
    }

    void allocate(void* data, unsigned int size) {
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
    }

private:
    GLuint _id;
};