#include "defs.h"
#include <iostream>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Rasterizer.h"
#include "Matrix44.h"
#include "GenMath.h"

float angle = 0;
Rasterizer* rasterizer = nullptr;

bool renderCB(){
    angle += .002f;
    Matrix44 transformation;
    transformation.rotate(Vector3(0, 1, 1), angle);

    Vector4 v1(-1, 1, 0, 1);
    Vector4 v2(1, 1, 0, 1);
    Vector4 v3(0, -1, 0, 1);

    v1 = transformation * v1;
    v2 = transformation * v2;
    v3 = transformation * v3;

    rasterizer->clearFrame();
    rasterizer->rasterizeTriangle(Vector2(v1.x, v1.y), Vector2(v2.x, v2.y), Vector2(v3.x, v3.y));

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

    return 0;
}
