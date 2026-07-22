#include <q3d/res/resources.hpp>
#include <q3d/log/log.hpp>
#include <sstream>

using namespace q3d;

Resources::ObjData Resources::parseObjFile(std::string_view fileContent) {
    ObjData data;
    std::istringstream iss(fileContent.data());
    std::string line;

    std::vector<glm::vec3> tempPositions;
    std::vector<glm::vec2> tempTexCoords;
    std::vector<glm::vec3> tempNormals;

    while (std::getline(iss, line)) {
        if (line.empty() || line[0] == '#') continue;

        std::istringstream lineStream(line);
        std::string prefix;
        lineStream >> prefix;

        if (prefix == "v") {
            float x, y, z;
            lineStream >> x >> y >> z;
            tempPositions.emplace_back(x, y, z);
        }
        else if (prefix == "vt") {
            float u, v;
            lineStream >> u >> v;
            tempTexCoords.emplace_back(u, v);
        }
        else if (prefix == "vn") {
            float nx, ny, nz;
            lineStream >> nx >> ny >> nz;
            tempNormals.emplace_back(nx, ny, nz);
        }
        else if (prefix == "f") {
            std::string vertexStr;
            while (lineStream >> vertexStr) {
                unsigned int posIdx = 0, texIdx = 0, normIdx;
                bool hasTex = false, hasNorm = false;

                size_t firstSlash = vertexStr.find('/');

                if (firstSlash != std::string::npos) {
                    posIdx = std::stoul(vertexStr.substr(0, firstSlash)) - 1;

                    size_t secondSlash = vertexStr.find('/', firstSlash + 1);
                    if (secondSlash != std::string::npos) {
                        std::string texIdxStr = vertexStr.substr(firstSlash + 1, secondSlash - firstSlash - 1);
                        if (!texIdxStr.empty()) {
                            texIdx = std::stoul(texIdxStr) - 1;
                            hasTex = true;
                        }

                        std::string normIdxStr = vertexStr.substr(secondSlash + 1);
                        if (!normIdxStr.empty()) {
                            normIdx = std::stoul(normIdxStr) - 1;
                            hasNorm = true;
                        }
                    } else {
                        std::string texIdxStr = vertexStr.substr(firstSlash + 1);
                        if (!texIdxStr.empty()) {
                            texIdx = std::stoul(texIdxStr) - 1;
                            hasTex = true;
                        }
                    }
                } else {
                    posIdx = std::stoul(vertexStr) - 1;
                }

                if (posIdx < tempPositions.size()) {
                    data.positions.push_back(tempPositions[posIdx]);

                    if (hasTex && texIdx < tempTexCoords.size()) {
                        data.texCoords.push_back(tempTexCoords[texIdx]);
                    } else {
                        data.texCoords.emplace_back(0.f, 0.f);
                    }

                    if (hasNorm && normIdx < tempNormals.size()) {
                        data.normals.push_back(tempNormals[normIdx]);
                    } else {
                        data.normals.emplace_back(0.f, 1.f, 0.f);
                    }

                    data.indices.push_back(data.positions.size() - 1);
                }
            }
        }
    }

    if (data.positions.empty()) {
        q3d::log::warn("Resources::parseObjFile(): No vertices found in OBJ file!");
    }
    if (data.indices.empty()) {
        q3d::log::warn("Resources::parseObjFile(): No faces found in OBJ file!");
    }

    return data;
}
