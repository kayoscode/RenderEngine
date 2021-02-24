
#include "VertexObject.h"

VertexObject::~VertexObject() {
    for(int i = 0 ; i < bufferCount; i++) {
        delete buffers[i];
    }

    delete[] buffers;
}

void VertexObject::bufferData(int attribute, float* data, int count, int stepPerVertex) {
    if(buffers[attribute] == nullptr) {
        buffers[attribute] = new DataList(count);

        for(float* i = data; i < data + count; i += stepPerVertex) {
            buffers[attribute]->bind(i, stepPerVertex);
        }
    }
    else {
        delete buffers[attribute];
        buffers[attribute] = nullptr;
        bufferData(attribute, data, count, stepPerVertex);
    }
}

void VertexObject::bufferIndices(int* ind, int count) {
    if(indexBuffer == nullptr) {
        indexBuffer = new int[count];
        indicesCount = count;

        for(int i = 0; i < count; i++) {
            indexBuffer[i] = ind[i];
        }
    }
    else {
        delete[] indexBuffer;
        bufferIndices(ind, count);
    }
}