#ifndef INCLUDE_SHADER_H
#define INCLUDE_SHADER_H

#include "DataList.h"

class Shader{
    public:
        Shader(int uniformCount) :
            uniforms(uniformCount)
        { }

        virtual void initShader() { 
            //call setin and setout methods to get indices for each attribute (both input and output)
        }

        virtual void prepare() {
            //prepare for the frame: store uniforms in global variables at the beginning of the frame so you don't have to perform a copy for each execute call
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