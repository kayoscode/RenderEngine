#ifndef INCLUDE_FRAGMENT_SHADER_H
#define INCLUDE_FRAGMENT_SHADER_H

#include "Shader.h"

class FragmentShader : public Shader {
    public:
        FragmentShader(int uniformCount) :
            Shader(uniformCount)
        {}

        virtual char execute(DataList* passAttributes, Vector4& out) {
            return '#';
        }

        virtual ~FragmentShader() {}
};

#endif