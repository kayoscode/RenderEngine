#ifndef INCLUDE_LOADER_H
#define INCLUDE_LOADER_H

#include "defs.h"
#include <vector>
#include <string>

class IndexedModel {
    public:
        int indexCount;
        int* indices = nullptr;
        float* positions = nullptr;
        float* normals = nullptr;
        float* uvs = nullptr;

        int positionsCount;
        int normalsCount;
        int uvsCount;

    ~IndexedModel() {
        delete[] indices;
        delete[] positions;
        delete[] normals;
        delete[] uvs;
    }
};

bool loadIndexedModel(const std::string& filePath, IndexedModel& model);

#endif