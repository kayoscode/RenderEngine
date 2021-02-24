#ifndef INCLUDE_SHADER_H
#define INCLUDE_SHADER_H

#include "DataList.h"

class Shader {
    public:
        Shader(int uniformCount) : uniforms(uniformCount) {

        }

        virtual void initShader() {
            //bind the uniforms to proper locations
        }

        virtual void prepare() {
            //perform calculations that don't need to be done per pixel to save time
        }

        virtual ~Shader() {

        }

        DataList* getUniforms() {
            return &uniforms;
        }

    protected:
        DataList uniforms;
};

#endif