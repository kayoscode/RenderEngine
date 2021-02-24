#ifndef INCLUDE_VERTEX_SHADER_H
#define INCLUDE_VERTEX_SHADER_H

#include "Shader.h"

class VertexShader : public Shader {
    public:
        VertexShader(int uniformCount, int maxPassCount) :
            Shader(uniformCount),
            maxPassCount(maxPassCount)
        {}

        virtual void execute(DataList** attributesIn, DataList* attributesOut, int attributeLocation, Vector4& input) {

        }

        virtual ~VertexShader() {

        }

        int getOutputCount() {
            return maxPassCount;
        }

    private:
        int maxPassCount;
};

#endif