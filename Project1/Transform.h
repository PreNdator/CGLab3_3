#pragma once
#include <iostream>
#include <cmath>
#include <array>
#include "AffineTransform3D.h"
#include <glm/common.hpp>

class Transform {
public:
    Transform() : m_position(glm::vec3(0.0f)), m_rotationX(0.0f), m_rotationY(0.0f), m_scale(0.5f) {}

    void setPosition(const glm::vec3& position) {
        m_position = position;
    }

    void setRotationX(const float& angle) {
        m_rotationX = angle;
    }
    void setRotationY(const float& angle) {
        m_rotationY = angle;
    }

    void setScale(float scale) {
        m_scale = scale;
    }

    glm::vec3 position() const {
        return m_position;
    }

    float rotationX() const {
        return m_rotationX;
    }
    float rotationY() const {
        return m_rotationY;
    }

    float scale() const {
        return m_scale;
    }
    
    glm::mat4 transformationMatrix() const {

        return AffineTransform3D::translate(m_position) *
            AffineTransform3D::rotateY(m_rotationY) *
            AffineTransform3D::rotateX(m_rotationX)*
            AffineTransform3D::scale(m_scale);
    }

private:
    glm::vec3 m_position;
    float m_rotationY;
    float m_rotationX;
    float m_scale;
};

