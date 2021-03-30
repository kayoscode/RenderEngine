#ifndef INCLUDE_VERTEX_ARRAY_OBJECT_H
#define INCLUDE_VERTEX_ARRAY_OBJECT_H

#include "DataList.h"

class VertexArrayObject {
    public:
        VertexArrayObject(int bufferCount) :
            bufferCount(bufferCount),
            buffers(new DataList*[bufferCount]),
            indexBuffer(nullptr)
        {
            for(int i = 0; i < bufferCount; i++) {
                buffers[i] = nullptr;
            }
        }

        void bufferData(int attribute, float* data, int count, int stepPerVertex);
        void bufferIndices(int* indices, int count);

        ~VertexArrayObject();

        int* getIndices() {
            return indexBuffer;
        }

        DataList** getBufferData() {
            return buffers;
        }

        int getBufferCount() {
            return bufferCount;
        }

        int getIndicesCount() {
            return indexCount;
        }

    private:
        int bufferCount;
        DataList** buffers;
        int* indexBuffer;
        int indexCount;
};

#endif