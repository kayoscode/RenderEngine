#include "defs.h"
#include <iostream>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Rasterizer.h"
#include "Matrix44.h"
#include "GenMath.h"
#include "Camera.h"

float angle = 0;
Rasterizer* rasterizer = nullptr;
Camera* cam = nullptr;

Vector4 v1(-1, 1, 0, 1);
Vector4 v2(1, 1, 0, 1);
Vector4 v3(0, -1, 0, 1);

Vector4 transformVertex(const Vector4& vertex, const Matrix44& MVPMatrix){
    Vector4 f;

    f = MVPMatrix * vertex;
    f.x /= f.w;
    f.y /= f.w;
    f.z /= f.w;

    return f;
}

bool renderCB(){
    Matrix44 transformation;
    Matrix44 PVMatrix;
    Matrix44 finalMatrix;

    cam->calculateViewMatrix();
    
    PVMatrix = cam->getPVMatrix();

    angle += .001f;

    transformation.translate(Vector3(0, 0, -1.f));
    transformation.rotate(Vector3(0, 1, 0), angle);
    finalMatrix = PVMatrix * transformation;

    Vector4 fv1 = transformVertex(v1, finalMatrix);
    Vector4 fv2 = transformVertex(v2, finalMatrix);
    Vector4 fv3 = transformVertex(v3, finalMatrix);

    rasterizer->clearFrame();
    rasterizer->rasterizeTriangle(Vector2(fv1.x, fv1.y), Vector2(fv2.x, fv2.y), Vector2(fv3.x, fv3.y));

    return true;
}

int main(void){
	initscr();
	raw();
	noecho();
    start_color();
    cbreak();
    curs_set(0);

    rasterizer = new Rasterizer(WW, WH);
    cam = new Camera();
    cam->createProjection(1.21f, (WW / (float)2) / WH, .2f, 400);

    rasterizer->setRenderCB(renderCB);

    while(true){
        rasterizer->presentFrame();
        rasterizer->swapBuffers();

        refresh();
        erase();
    }

    getch();
    clear();

    endwin();

    delete rasterizer;
    delete cam;

    return 0;
}
