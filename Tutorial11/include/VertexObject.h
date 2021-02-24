
#ifndef INCLUDE_VERTEX_OBJECT_H
#define INCLUDE_VERTEX_OBJECT_H

#include "DataList.h"

class VertexObject {
    public:
        VertexObject(int bufferCount) :
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

        ~VertexObject();

        int* getIndices() const {
            return indexBuffer;
        }

        DataList** getBufferData() {
            return buffers;
        }

        int getBufferCount() {
            return bufferCount;
        }

        int getIndicesCount() {
            return indicesCount;
        }
    
    private:
        int bufferCount;
        DataList** buffers;
        int* indexBuffer;
        int indicesCount;
};

#endif 