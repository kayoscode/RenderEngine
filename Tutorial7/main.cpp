#include "defs.h"
#include <iostream>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Rasterizer.h"
#include "Matrix44.h"
#include "GenMath.h"

int main(void){
	initscr();
	raw();
	noecho();
    start_color();
    cbreak();
    
    Rasterizer rasterizer(WW, WH);

    float angle = 0;

    while(true){
        angle += .002f;
        Matrix44 transformation;
        transformation.rotate(Vector3(0, 1, 1), angle);

        Vector4 v1(-1, 1, 0, 1);
        Vector4 v2(1, 1, 0, 1);
        Vector4 v3(0, -1, 0, 1);

        v1 = transformation * v1;
        v2 = transformation * v2;
        v3 = transformation * v3;

        rasterizer.clearFrame();
        rasterizer.rasterizeTriangle(Vector2(v1.x, v1.y), Vector2(v2.x, v2.y), Vector2(v3.x, v3.y));
        rasterizer.presentFrame(0, 0);

        refresh();
        erase();
    }

    getch();
    clear();

    endwin();

    return 0;
}
