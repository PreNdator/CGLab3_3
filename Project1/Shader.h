#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shader
{
public:
    Shader(const char* vertex_shader, const char* fragment_shader) {
        GLuint vs = compileShader(GL_VERTEX_SHADER, vertex_shader);
        GLuint fs = compileShader(GL_FRAGMENT_SHADER, fragment_shader);

       _shaderId = glCreateProgram();
        glAttachShader(_shaderId, vs);
        glAttachShader(_shaderId, fs);
        glLinkProgram(_shaderId);

       // glDeleteShader(vs);
       // glDeleteShader(fs);
    }

    void use() const {
        glUseProgram(_shaderId);
    }

    void setInt(const char* name, int value) const {
        glUniform1i(glGetUniformLocation(_shaderId, name), value);
    }

    void setFloat(const char* name, float value) const {
        glUniform1f(glGetUniformLocation(_shaderId, name), value);
    }

    void setVec2(const char* name, const glm::vec2& value) const {
        glUniform2fv(glGetUniformLocation(_shaderId, name), 1, &value[0]);
    }

    void setVec3(const char* name, const glm::vec3& value) const {
        glUniform3fv(glGetUniformLocation(_shaderId, name), 1, &value[0]);
    }

    void setMat4(const char* name, const glm::mat4& mat) const {
        glUniformMatrix4fv(glGetUniformLocation(_shaderId, name), 1, GL_FALSE, glm::value_ptr(mat));
    }

    void setVec4(const char* name, const glm::vec4& value) const {
        glUniform4fv(glGetUniformLocation(_shaderId, name), 1, &value[0]);
    }

private:

    GLuint compileShader(GLenum type, const char* source) const {
        GLuint shader = glCreateShader(type);
        const GLchar* src = source;
        glShaderSource(shader, 1, &src, NULL);
        glCompileShader(shader);

        return shader;
    }

	unsigned int _shaderId;
};


