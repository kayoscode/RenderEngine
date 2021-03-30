
#include "Loader.h"
#include <fstream>
#include <iostream>
#include <unordered_map>

#define IS_FLOAT_CHAR(i) ((i >= '0' && i <= '9') || (i == '.') || (i == '-'))

struct Vertex {
    int pos, norm, uv;

    Vertex(int pos = -1, int norm = -1, int uv = -1) 
        :pos(pos), norm(norm), uv(uv)
    {}

    Vertex(const Vertex& v) 
        :pos(v.pos), norm(v.norm), uv(v.uv)
    {}

    Vertex& operator=(const Vertex& v) {
        this->pos = v.pos;
        this->norm = v.norm;
        this->uv = v.uv;
        return *this;
    }

    bool operator==(const Vertex& v) const {
        return pos == v.pos && norm == v.norm && uv == v.uv;
    }
};

class VertexHash {
    public:
        size_t operator()(const Vertex& v) const {
            return std::hash<int>()(v.pos) ^ std::hash<int>()(v.norm) ^ std::hash<int>()(v.uv);
        }
};

std::vector<std::string> split(const std::string& s, char ch) {
    std::vector<std::string> ret;
    std::string l;

    for(int i = 0; i < s.size(); i++) {
        if(s[i] == ch) {
            ret.push_back(l);
            l = "";
        }
        else {
            l += s[i];
        }
    }

    if(l.size() > 0) ret.push_back(l);

    return ret;
}

bool loadFloat(std::string& line, int& index, float& flt) {
    while(!IS_FLOAT_CHAR(line[index]) && index < line.size()) {
        index++;
    }

    if(!IS_FLOAT_CHAR(line[index])) return false;

    size_t newIndex = 0;
    flt = std::stof(line.substr(index), &newIndex);
    index += newIndex;
    return index != newIndex;
}

bool loadFloats(std::string& line, std::vector<float>& list, uint32_t count) {
    int index = 2;

    for(int i = 0; i < count; i++) {
        float l = 0;
        if(!loadFloat(line, index, l)) return false;
        list.push_back(l);
    }

    return true;
}

bool loadFace(std::string& line, std::vector<int>& indices, std::vector<float>& positions, std::vector<float>& normals, 
    std::vector<float>& uvs, std::unordered_map<Vertex, int, VertexHash>& vertices) {
    Vertex vertex1, vertex2, vertex3;
    std::vector<std::string> faceSplit = split(line, ' ');

    if(faceSplit.size() < 4) return false;

    std::vector<std::string> v1 = split(faceSplit[1], '/');
    std::vector<std::string> v2 = split(faceSplit[2], '/');
    std::vector<std::string> v3 = split(faceSplit[3], '/');

    if(v1.size() != v2.size() || v1.size() != v3.size() || v1.size() == 0) return false;

    if(v1.size() == 1) {
        vertex1.pos = std::stoi(v1[0]) - 1;
        vertex2.pos = std::stoi(v2[0]) - 1;
        vertex3.pos = std::stoi(v3[0]) - 1;
    }
    else if(v1.size() == 2) {
        vertex1.pos = std::stoi(v1[0]) - 1;
        vertex2.pos = std::stoi(v2[0]) - 1;
        vertex3.pos = std::stoi(v3[0]) - 1;

        vertex1.uv = std::stoi(v1[1]) - 1;
        vertex2.uv = std::stoi(v2[1]) - 1;
        vertex3.uv = std::stoi(v3[1]) - 1;
    }
    else if(v1.size() == 3) {
        if(v1[1].size() == 0) {
            vertex1.pos = std::stoi(v1[0]) - 1;
            vertex2.pos = std::stoi(v2[0]) - 1;
            vertex3.pos = std::stoi(v3[0]) - 1;

            vertex1.norm = std::stoi(v1[2]) - 1;
            vertex2.norm = std::stoi(v2[2]) - 1;
            vertex3.norm = std::stoi(v3[2]) - 1;
        }
        else {
            vertex1.pos = std::stoi(v1[0]) - 1;
            vertex2.pos = std::stoi(v2[0]) - 1;
            vertex3.pos = std::stoi(v3[0]) - 1;

            vertex1.uv = std::stoi(v1[1]) - 1;
            vertex2.uv = std::stoi(v2[1]) - 1;
            vertex3.uv = std::stoi(v3[1]) - 1;

            vertex1.norm = std::stoi(v1[2]) - 1;
            vertex2.norm = std::stoi(v2[2]) - 1;
            vertex3.norm = std::stoi(v3[2]) - 1;
        }
    }

    if(vertices.find(vertex1) == vertices.end()) {
        vertices[vertex1] = vertices.size();
    }

    if(vertices.find(vertex2) == vertices.end()) {
        vertices[vertex2] = vertices.size();
    }

    if(vertices.find(vertex3) == vertices.end()) {
        vertices[vertex3] = vertices.size();
    }

    indices.push_back(vertices[vertex1]);
    indices.push_back(vertices[vertex2]);
    indices.push_back(vertices[vertex3]);

    return true;
}

bool loadIndexedModel(const std::string& filePath, IndexedModel& model) {
    std::ifstream file(filePath);
    std::string line;

    std::vector<float> positions, normals, uvs;
    std::vector<int> indices;
    std::unordered_map<Vertex, int, VertexHash> vertices;

    while(getline(file, line)) {
        if(line.size() > 2) {
            if(line[0] == 'v' && line[1] == ' ') {
                if(!loadFloats(line, positions, 3)) return false;
            }
            else if(line[0] == 'v' && line[1] == 't') {
                if(!loadFloats(line, uvs, 2)) return false;
            }
            else if(line[0] == 'v' && line[1] == 'n') {
                if(!loadFloats(line, normals, 3));
            }
            else if(line[0] == 'f') {
                if(!loadFace(line, indices, positions, normals, uvs, vertices)) return false;
            }
        }
    }

    //std::cout << vertices.size() << "\n";
    model.indices = new int[indices.size()];
    model.positions = new float[vertices.size() * 3];
    model.normals = new float[vertices.size() * 3];
    model.uvs = new float[vertices.size() * 2];

    model.positionsCount = vertices.size() * 3;
    model.normalsCount = vertices.size() * 3;
    model.uvsCount = vertices.size() * 2;

    //loop through every vertex and write to each index the correct values from 
    for(std::unordered_map<Vertex, int>::iterator i = vertices.begin(); i != vertices.end(); i++) {
        model.positions[(i->second * 3) + 0] = positions[(i->first.pos * 3) + 0];
        model.positions[(i->second * 3) + 1] = positions[(i->first.pos * 3) + 1];
        model.positions[(i->second * 3) + 2] = positions[(i->first.pos * 3) + 2];

        model.normals[(i->second * 3) + 0] = normals[(i->first.norm * 3) + 0];
        model.normals[(i->second * 3) + 1] = normals[(i->first.norm * 3) + 1];
        model.normals[(i->second * 3) + 2] = normals[(i->first.norm * 3) + 2];

        model.uvs[(i->second * 2) + 0] = uvs[(i->first.uv * 2) + 0];
        model.uvs[(i->second * 2) + 1] = uvs[(i->first.uv * 2) + 1];
    }

    //finally copy over the indices
    model.indexCount = indices.size();
    for(int i = 0; i < indices.size(); i++) {
        model.indices[i] = indices[i];
    }

    file.close();
    return true;
}