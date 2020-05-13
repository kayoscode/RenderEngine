#include "Rasterizer.h"
#include "defs.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"

#include <math.h>

bool renderStart, renderFinished, programRunning;

void renderThreadF(bool(**renderCB)()){
    while(programRunning){
        if(renderStart){
            renderStart = false;
            renderFinished = false;

            if(*renderCB != nullptr){
                (*renderCB)();
            }

            renderFinished = true;
        }
    }
}

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

void Rasterizer::presentFrame(){
    renderStart = true;
    pFrame->print();

    while(!renderFinished);
}

void Rasterizer::initializeFramebuffer(int width, int height){
    frameBuffers[0] = new Framebuffer(width, height);
    frameBuffers[1] = new Framebuffer(width, height);
    swapBuffers();
}

Rasterizer::Rasterizer(int width, int height)
    :renderCallback(nullptr),
    pFrame(nullptr),
    rFrame(nullptr),
    currentBuffer(0)
{
    programRunning = true;
    renderStart = false;
    renderFinished = false;

    initializeFramebuffer(width, height);
    renderThread = std::thread(renderThreadF, &renderCallback);
}

Rasterizer::~Rasterizer(){
    delete frameBuffers[0];
    delete frameBuffers[1];
}

void Rasterizer::rasterizeTriangle(const Vector2& vv1, const Vector2& vv2, const Vector2& vv3){
    Framebuffer* fb = rFrame;

    int h_width = fb->getWidth() / 2, h_height = fb->getHeight() / 2;
    int minx, maxx;
    int miny, maxy;

    Vector2 v1 = Vector2(vv1.x * h_width + h_width, -vv1.y * h_height + h_height);
    Vector2 v2 = Vector2(vv2.x * h_width + h_width, -vv2.y * h_height + h_height);
    Vector2 v3 = Vector2(vv3.x * h_width + h_width, -vv3.y * h_height + h_height);

    minx = MAX(0, MIN(v1.x, MIN(v2.x, v3.x)));
    miny = MAX(0, MIN(v1.y, MIN(v2.y, v3.y)));

    maxx = MIN(fb->getWidth(), MAX(v1.x, MAX(v2.x, v3.x)) + 1);
    maxy = MIN(fb->getHeight(), MAX(v1.y, MAX(v2.y, v3.y)) + 1);

    for(int j = miny; j < maxy; j++){
        for(int i = minx; i < maxx; i++){
            if(isPointInTriangle(i, j, v1, v2, v3)){
                fb->setPixel(i, j, '#', 0);
            }
        }
    }
}

