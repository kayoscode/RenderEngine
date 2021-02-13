
#ifndef INCLUDE_CAMERA_H
#define INCLUDE_CAMERA_H

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"

class Camera{
    public:
        Camera();
        ~Camera();

        inline Vector3& getPosition() { return position; }
        inline Vector3& getRotation() { return rotation; }

        inline void calculateViewMatrix(){
            viewMatrix.setIdentity();
            viewMatrix.rotate(Vector3(1, 0, 0), rotation.x);
            viewMatrix.rotate(Vector3(0, 1, 0), rotation.y);
            viewMatrix.rotate(Vector3(0, 0, 1), rotation.z);
            viewMatrix.translate(position);
        }

        inline Matrix44 getPVMatrix() { 
            return projMatrix * viewMatrix; 
        }

        inline Matrix44 getViewMatrix() {
            return viewMatrix;
        }

        inline Matrix44 getProjectionMatrix() {
            return projMatrix;
        }

        void createProjection(float fov, float aspect, float nearPlane, float farPlane);

    private:
        float fov, aspect, zNear, zFar;
        Vector3 position;
        Vector3 rotation;

        Matrix44 viewMatrix;
        Matrix44 projMatrix;
};

#endif