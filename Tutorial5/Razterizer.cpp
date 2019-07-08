#include "Razterizer.h"

#include "defs.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"

#include <math.h>

static inline bool isPointInTriangle(int ptx, int pty, const Vector2& v1,
    const Vector2& v2, const Vector2& v3)
{
    float wv1 = ((v2.y - v3.y) * (ptx - v3.x) +
            (v3.x - v2.x) * (pty - v3.y)) /
        ((v2.y - v3.y) * (v1.x - v3.x) +
         (v3.x - v2.x) * (v1.y - v3.y));

    float wv2 = ((v3.y - v1.y) * (ptx - v3.x) +
            (v1.x - v3.x) * (pty - v3.y)) /
        ((v2.y - v3.y) * (v1.x - v3.x) +
         (v3.x - v2.x) * (v1.y - v3.y));

    float wv3 = 1.0f - wv1 - wv2;

    int one = (wv1 < -0.001);
    int two = (wv2 < -0.001);
    int three = (wv3 < -0.001);

    //is the point in the triangle
    return ((one == two) && (two == three));
}

void Razterizer::initializeFramebuffer(int width, int height){
    fb = new Framebuffer(width, height);
}

Razterizer::Razterizer(int width, int height)
    :fb(nullptr)
{
    initializeFramebuffer(width, height);
}

Razterizer::~Razterizer(){
    delete fb;
}

void Razterizer::razterizeTriangle(const Vector2& v1, const Vector2& v2, const Vector2& v3){
    int minx, maxx;
    int miny, maxy;

    minx = MAX(0, MIN(v1.x, MIN(v2.x, v3.x)));
    miny = MAX(0, MIN(v1.y, MIN(v2.y, v3.y)));

    maxx = MIN(fb->width, MAX(v1.x, MAX(v2.x, v3.x)) + 1);
    maxy = MIN(fb->height, MAX(v1.y, MAX(v2.y, v3.y)) + 1);

    for(int j = miny; j < maxy; j++){
        for(int i = minx; i < maxx; i++){
            if(isPointInTriangle(i, j, v1, v2, v3)){
                mvprintw(j, i, "#");
            }
            else {
                mvprintw(j, i, ".");
            }
        }
    }
}
