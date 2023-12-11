#pragma once
#pragma once
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <glm/common.hpp>

struct Vertex {
    unsigned int positionIndex;
    unsigned int textureCoordIndex;
    unsigned int normalIndex;
};

class ModelLoader {
public:
    bool isLoad(const std::string& path) {
        std::ifstream file(path);
        if (!file.is_open()) {
            throw std::runtime_error("Failed to open file: " + path);
            return false;
        }

        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            std::string type;
            ss >> type;

            if (type == "v") {
                glm::vec3 vertex;
                if (parceVertices(ss, vertex)) {
                    vertices.push_back(vertex);
                }
                else {
                    file.close();
                    throw std::runtime_error("Error parsing vertex in line: " + line);
                    return false;
                }
            }
            else if (type == "vt") {
                glm::vec2 textureCoord;
                if (parceTextureCoords(ss, textureCoord)) {
                    textureCoords.push_back(textureCoord);
                }
                else {
                    file.close();
                    throw std::runtime_error("Error parsing texture coordinates in line: " + line);
                    return false;
                }
            }
            else if (type == "vn") {
                glm::vec3 normal;
                if (parceNormal(ss, normal)) {
                    normals.push_back(normal);
                }
                else {
                    file.close();
                    throw std::runtime_error("Error parsing normal in line: " + line);
                    return false;
                }
            }
            else if (type == "f") {
                if (!parceFace(ss)) {
                    file.close();
                    throw std::runtime_error("Error parsing face in line: " + line);
                    return false;
                }
            }
        }

        file.close();
        return true;
    }

    std::vector<glm::uvec3> getIndices() {
        std::vector<glm::uvec3> indices;
        for (int i = 0; i < verticesData.size(); i += 3) {
            glm::uvec3 index;
            index.x = verticesData[i].positionIndex;
            index.y = verticesData[i + 1].positionIndex;
            index.z = verticesData[i + 2].positionIndex;
            indices.push_back(index);
        }
        return indices;
    }


    const std::vector<glm::vec3>& getVertices() const {
        return vertices;
    }

private:
    bool parceVertices(std::stringstream& ss, glm::vec3& vertex) {
        return bool(ss >> vertex.x >> vertex.y >> vertex.z);
    }

    bool parceTextureCoords(std::stringstream& ss, glm::vec2& textureCoord) {
        return bool(ss >> textureCoord.x >> textureCoord.y);
    }

    bool parceNormal(std::stringstream& ss, glm::vec3& normal) {
        return bool(ss >> normal.x >> normal.y >> normal.z);
    }

    bool parceFace(std::stringstream& ss) {
        std::string Str;
        while (ss >> Str) {
            Vertex vertex;
            std::stringstream SS(Str);
            char slash;

            SS >> vertex.positionIndex >> slash >> vertex.textureCoordIndex >> slash >> vertex.normalIndex;
            --vertex.positionIndex;
            --vertex.textureCoordIndex;
            --vertex.normalIndex;
            if (vertex.positionIndex >= 0 && vertex.textureCoordIndex >= 0 && vertex.normalIndex >= 0) {
                
                verticesData.push_back(vertex);
            }
            else {
                return false;
            }
        }

        return true;
    }

    std::vector<glm::vec3> vertices;
    std::vector<glm::vec2> textureCoords;
    std::vector<glm::vec3> normals;
    std::vector<Vertex> verticesData;
};