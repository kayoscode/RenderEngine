#ifndef INCLUDE_BASIC_VERTEX_SHADER_H
#define INCLUDE_BASIC_VERTEX_SHADER_H

#include "VertexShader.h"
#include "FragmentShader.h"

class BasicVertexShader : public VertexShader {
    public:
        int location_projectionMatrix;
        int location_viewMatrix;
        int location_transformation;

        Matrix44 projectionMatrix, viewMatrix, transformation;
        Matrix44 finalMatrix;

        BasicVertexShader() :
            VertexShader(1000) 
        {}

        virtual void initShader() {
            location_projectionMatrix = uniforms.bind(projectionMatrix);
            location_viewMatrix = uniforms.bind(viewMatrix);
            location_transformation = uniforms.bind(transformation);
        }

        virtual void prepare() {
            uniforms.get(location_projectionMatrix, projectionMatrix);
            uniforms.get(location_viewMatrix, viewMatrix);
            uniforms.get(location_transformation, transformation);

            finalMatrix = projectionMatrix * viewMatrix * transformation;
        }

        virtual void execute(DataList** attributesIn, DataList** attributesOut, int attributeLocation, Vector4& output) {
            Vector3 pos;
            Vector3 norm;
            Vector2 uv;

            attributesIn[0]->get(attributeLocation, pos);
            attributesIn[1]->get(attributeLocation, uv);
            attributesIn[2]->get(attributeLocation, norm);

            output = finalMatrix * Vector4(pos.x, pos.y, pos.z, 1);
        }
};

#endif