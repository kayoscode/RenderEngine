
#include "Camera.h"
#include <math.h>

Camera::Camera()
    :fov(0),
    aspect(0),
    zNear(0),
    zFar(0),
    position(0, 0, 0),
    rotation(0, 0 ,0),
    viewMatrix(),
    projMatrix()
{
    calculateViewMatrix();
}

Camera::~Camera(){}

void Camera::createProjection(float fov, float aspect, float zNear, float zFar){
    projMatrix.setIdentity();
    float tanhfov = (float)tanf(fov / 2);

    projMatrix.m00 = 1/(aspect * tanhfov);
    projMatrix.m11 = 1/tanhfov;
    projMatrix.m22 = -(zNear + zFar) / (zFar - zNear);
    projMatrix.m23 = -1;
    projMatrix.m32 = -(2 * zFar * zNear) / (zFar - zNear);
}