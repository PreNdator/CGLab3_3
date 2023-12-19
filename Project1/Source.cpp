#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <chrono>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include "Vao.h"
#include "Shader.h"
#include "Ebo.h"
#include "ModelLoader.h"
#include "GLModel.h"
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>

GLModel* model;
Shader *shader;
glm::mat4 perspective;
float fov = 70;
float near = 0.1f;
float far = 100.0f;
bool rotationMode = false;
bool translationMode = false;
float speedX = 0;
float speedY = 0;
float stop_coeff = 0.999f;
float rotation_speed = 0.001;
float scaleFactor = 0.1f;

//GLFWwindow  *window;

static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
        rotationMode = true;
    else if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE)
        rotationMode = false;

    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
        translationMode = true;
    else if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_RELEASE)
        translationMode = false;
}

static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{

    if (yoffset > 0.0)
        model->setScale(model->scale() + scaleFactor);
    else if (yoffset < 0.0 && model->scale() > scaleFactor)
        model->setScale(model->scale() - scaleFactor);
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
    static double lastX = xpos;
    static double lastY = ypos;

    if (rotationMode)
    {
        double deltaX = xpos - lastX;
        double deltaY = ypos - lastY;
        speedX += deltaY*rotation_speed;
        speedY += deltaX*rotation_speed;
        
    }
    

    if (translationMode)
    {
        double deltaX = xpos - lastX;
        double deltaY = ypos - lastY;

        model->setPosition(model->position() + glm::vec3(deltaX * 0.01, -deltaY * 0.01, 0.0));
    }

    lastX = xpos;
    lastY = ypos;
}


static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);

    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_D:
            model->setPosition(model->position() + glm::vec3(0.1, 0, 0));
            break;
        case GLFW_KEY_A:
            model->setPosition(model->position() - glm::vec3(0.1, 0, 0));
            break;
        case GLFW_KEY_W:
            model->setPosition(model->position() + glm::vec3(0, 0.1, 0));
            break;
        case GLFW_KEY_S:
            model->setPosition(model->position() - glm::vec3(0, 0.1, 0));
            break;
        case GLFW_KEY_C:
            model->setPosition(model->position() + glm::vec3(0, 0, 0.1));
            break;
        case GLFW_KEY_V:
            model->setPosition(model->position() - glm::vec3(0, 0, 0.1));
            break;
        case GLFW_KEY_P:
            model->setScale(model->scale() + 0.1);
            break;
        case GLFW_KEY_O:
            model->setScale(model->scale() - 0.1);
            break;
    }
}

// Когда пользователь меняет размер окна, окно просмотра также должно быть скорректировано, требуя функцию обратного вызова
void framebuffer_size_callback(GLFWwindow* window,int width,int height){
         // Первые два параметра функции glViewport управляют положением нижнего левого угла окна, а третий и четвертый параметры контролируют ширину и высоту окна рендеринга
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0,0,width,height);
    perspective = glm::perspective(fov, (float)width/(float)height, near, far);
    shader->setMat4("perspective", perspective);
}

// Объявляем функцию, чтобы определить, нажата ли конкретная клавиша
void processInput(GLFWwindow * window){
         // Проверка, нажимает ли пользователь клавишу возврата (Esc) (если не нажата, glfwGetKey вернет GLFW_RELEASE, если нажата, GLFW_PRESS)
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int main(int argc, char** argv)
{ // Инициализация GLFW
    glfwInit();

    // Установить номер основной версии OpenGL (Major) и номер вспомогательной версии (Minor) в 3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // Использование режима ядра (Core-profile)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Создать объект окна
    GLFWwindow* window = glfwCreateWindow(800, 600, "GLFW + GLAD", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }

    // Уведомить GLFW, чтобы установить контекст нашего окна в качестве основного контекста текущего потока
    glfwMakeContextCurrent(window);

    // GLAD используется для управления указателем функции OpenGL, нам нужно инициализировать GLAD перед вызовом любой функции OpenGL
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // Зарегистрируем определенную функцию обратного вызова и сообщаем GLFW вызывать эту функцию при каждом изменении размера окна
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetKeyCallback(window, key_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);

    ModelLoader loader;

    shader = new Shader(vertex_shader, fragment_shader);
    std::string filePath = "data.txt";

    if (!loader.isLoad(filePath)) {
        throw std::runtime_error("Failed to load model from file: " + std::string(filePath));
        return -1;
    }

    model = new GLModel(loader.getVertices(), loader.getIndices());
    perspective = glm::perspective(fov, 800.0f / 600.0f, near, far);
    // Визуализация цикла
    while (!glfwWindowShouldClose(window)) {
        speedX *= stop_coeff;
        speedY *= stop_coeff;
        //model->setRotationX(model->rotationX() - speedX);
        model->setRotationY(model->rotationY() - speedY);

        // Проверить, нажата ли конкретная клавиша, и обрабатывать ее каждый кадр
        processInput(window);

        // функция glClearColor - это функция установки состояния, используемая для установки цвета, используемого для очистки экрана
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        // Функция glClear - это функция использования состояния, которая использует текущее состояние для очистки экрана с указанным цветом
        glClear(GL_COLOR_BUFFER_BIT);

        shader->setMat4("perspective", perspective);
        model->bind(*shader);
        glDrawElements(GL_TRIANGLES, model->nVertices()*3, GL_UNSIGNED_INT, 0);
        model->release();

                 // Функция glfwSwapBuffers будет обмениваться цветовыми буферами
        glfwSwapBuffers(window);
        // Функция glfwPollEvents проверяет, запущены ли какие-либо события
        glfwPollEvents();
    }


    // Освободить все ресурсы, выделенные ранее
    glfwTerminate();

    return 0;
}