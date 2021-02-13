#ifndef INCLUDE_SHADER_PROGRAM_H
#define INCLUDE_SHADER_PROGRAM_H

#include "VertexShader.h"
#include "FragmentShader.h"

//binds a vertex shader to a fragment shader allowing the passing of attributes between the two
class ShaderProgram {
    public:
        ShaderProgram(VertexShader* vs, FragmentShader* fs) 
            :vs(vs),
            fs(fs)
        {
            vs->initShader();
            fs->initShader();
        }

        void prepare() {
            vs->prepare();
            fs->prepare();
        }

        void executeVertexShader(DataList** attributesIn, int attributeLocation, Vector4& out) {
            vs->execute(attributesIn, nullptr, attributeLocation, out);
        }

    private:
        VertexShader* vs;
        FragmentShader* fs;
};

#endif