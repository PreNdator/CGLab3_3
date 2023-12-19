#pragma once
#include <iostream>
#include <array>
#include <vector>
#include <glm/common.hpp>
#include <glm/gtc/matrix_transform.hpp>




namespace AffineTransform3D {

    const float  PI_F = 3.14159265358979f;

    glm::mat4 rotateX(float angle) {
        float radians = PI_F / 180.0f * angle;
        float cosA = std::cos(radians);
        float sinA = std::sin(radians);

        return glm::mat4(
            1.0, 0.0, 0.0, 0.0,
            0.0, cosA, -sinA, 0.0,
            0.0, sinA, cosA, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
    }

    glm::mat4 rotateY(float angle) {
        float radians = PI_F / 180.0f * angle;
        float cosA = std::cos(radians);
        float sinA = std::sin(radians);


        return glm::mat4(
            cosA, 0.0, sinA, 0.0,
            0.0, 1.0, 0.0, 0.0,
            -sinA, 0.0, cosA, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
    }

    glm::mat4 rotateZ(float angle) {
        float radians = PI_F / 180.0f * angle;
        float cosA = std::cos(radians);
        float sinA = std::sin(radians);

        return glm::mat4(
            cosA, -sinA, 0.0, 0.0,
            sinA, cosA, 0.0, 0.0,
            0.0, 0.0, 1.0, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
    }


    glm::mat4 translate(glm::vec3 translation) {

        return glm::mat4(
            1.0f, 0.0f, 0.0f, 0.0f,
            0.0f, 1.0f, 0.0f, 0.0f,
            0.0f, 0.0f, 1.0f, 0.0f,
            translation.x, translation.y, translation.z, 1.0f
        );
    }

    glm::mat4 scale(float scale) {

        return glm::mat4(
            scale, 0.0, 0.0, 0.0,
            0.0, scale, 0.0, 0.0,
            0.0, 0.0, scale, 0.0,
            0.0, 0.0, 0.0, 1.0
        );
    }

};