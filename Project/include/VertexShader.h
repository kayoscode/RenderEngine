#ifndef INCLUDE_VERTEX_SHADER_H
#define INCLUDE_VERTEX_SHADER_H

#include "Shader.h"

class VertexShader : public Shader {
    public:
        VertexShader(int uniformCount, int attributesOutCount) :
            Shader(uniformCount),
            outputCount(attributesOutCount)
        {}

        virtual void execute(DataList** attributesIn, DataList* attributesOut, int attributeLocation, Vector4& output) {

        }

        virtual ~VertexShader() {

        }

        int getOutputCount() {
            return outputCount;
        }

    private:
        int outputCount;
};

#endif