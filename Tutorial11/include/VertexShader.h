#ifndef INCLUDE_VERTEX_SHADER_H
#define INCLUDE_VERTEX_SHADER_H

#include "Shader.h"

class VertexShader : public Shader {
    public:
        VertexShader(int uniformCount) :
            Shader(uniformCount)
        {}

        virtual void execute(DataList** attributesIn, DataList** attributesOut, int attributeLocation, Vector4& input) {

        }

        virtual ~VertexShader() {

        }
};

#endif