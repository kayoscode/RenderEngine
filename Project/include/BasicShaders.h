#ifndef INCLUDE_BASIC_SHADERS_H
#define INCLUDE_BASIC_SHADERS_H

#include "VertexShader.h"
#include "FragmentShader.h"

class BasicVertexShader : public VertexShader {
    public:
        int locationProjectionMatrix;
        int locationViewMatrix;
        int locationTransformation;
        int locationLightPos;

        Vector3 lightPos;
        Matrix44 projectionMatrix, viewMatrix, transformation;
        Matrix44 finalMatrix;

        BasicVertexShader() :
            VertexShader(1000, 1000)
        {}

        virtual void initShader() {
            locationProjectionMatrix = uniforms.bind(projectionMatrix);
            locationViewMatrix = uniforms.bind(viewMatrix);
            locationTransformation = uniforms.bind(transformation);
            locationLightPos = uniforms.bind(lightPos);
        }

        virtual void prepare() {
            uniforms.get(locationProjectionMatrix, projectionMatrix);
            uniforms.get(locationViewMatrix, viewMatrix);
            uniforms.get(locationTransformation, transformation);
            uniforms.get(locationLightPos, lightPos);

            finalMatrix = projectionMatrix * viewMatrix * transformation;
        }

        virtual void execute(DataList** attributesIn, DataList* attributesOut, int attributeLocation, Vector4& output) {
            //load attributes
            Vector3 pos, normal;
            Vector2 uv;

            attributesIn[0]->get(attributeLocation, pos);
            attributesIn[1]->get(attributeLocation, uv);
            attributesIn[2]->get(attributeLocation, normal);

            //calculate final vertex position
            output = finalMatrix * Vector4(pos.x, pos.y, pos.z, 1);
            Vector4 tn = transformation * Vector4(normal.x, normal.y, normal.z, 0);
            Vector4 worldPos = transformation * Vector4(pos.x, pos.y, pos.z, 1);

            //bind the transformed normal to position 0
            attributesOut->bind(Vector3(tn.x, tn.y, tn.z));
            //bind the vector pointing from the frag coord to the light in position 1
            attributesOut->bind(lightPos - Vector3(worldPos.x, worldPos.y, worldPos.z));
        }
};

class BasicFragmentShader : public FragmentShader {
    public:
        char shades[12] = "@#&%*+-'`. ";
        int shadesCount = sizeof(shades) / sizeof(shades[0]);

        BasicFragmentShader() :
            FragmentShader(1000)
        {}

        virtual void initShader() {
        }

        virtual void prepare() {
        }

        virtual char execute(DataList* attributes, Vector4& output) {
            Vector3 normal;
            Vector3 toLightVector;

            float brightness;
            attributes->get(0, normal);
            attributes->get(1, toLightVector);

            normal.normalize();
            toLightVector.normalize();

            brightness = normal * toLightVector;
            brightness = MAX(brightness, .19);
            brightness = 1 - brightness;
            brightness *= shadesCount;

            char character = shades[(int)brightness];
            return character;
        }
};

#endif