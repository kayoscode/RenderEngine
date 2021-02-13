#include "Rasterizer.h"
#include "defs.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"

#include <math.h>
#include <atomic>

std::atomic<bool> renderStart, renderFinished, programRunning;

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

static inline bool isPointInTriangle(const Vector3& barryCentricCoords)
{
    int one = (barryCentricCoords.x < -0.001);
    int two = (barryCentricCoords.y < -0.001);
    int three = (barryCentricCoords.z < -0.001);

    //is the point in the triangle
    return ((one == two) && (two == three));
}

static inline void calculateBarryCentricCoords(int ptx, int pty, const Vector2& v1, const Vector2& v2, const Vector2& v3, Vector3& coords) {
    coords.x = ((v2.y - v3.y) * (ptx - v3.x) +
            (v3.x - v2.x) * (pty - v3.y)) /
        ((v2.y - v3.y) * (v1.x - v3.x) +
         (v3.x - v2.x) * (v1.y - v3.y));

    coords.y = ((v3.y - v1.y) * (ptx - v3.x) +
            (v1.x - v3.x) * (pty - v3.y)) /
        ((v2.y - v3.y) * (v1.x - v3.x) +
         (v3.x - v2.x) * (v1.y - v3.y));

    coords.z = 1.0f - coords.x - coords.y;
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

    Vector3 barryCentricCoords;

    for(int j = miny; j < maxy; j++){
        for(int i = minx; i < maxx; i++){
            calculateBarryCentricCoords(i, j, v1, v2, v3, barryCentricCoords);
            if(isPointInTriangle(barryCentricCoords)){
                fb->setPixel(i, j, '#', 0);
            }
        }
    }
}

#include <iostream>
void vertexShader(ShaderProgram& shader, VertexObject& vao, int vertexIndex, Vector4& out) {
    shader.executeVertexShader(vao.getBufferData(), vertexIndex, out);
}

void RenderContext::renderIndexedTriangles(ShaderProgram& shader, VertexObject& vao) {
    shader.prepare();
    Vector4 v1, v2, v3;

    for(int i = 0; i < vao.getIndicesCount(); i += 3) {
        vertexShader(shader, vao, vao.getIndices()[i + 0], v1);
        vertexShader(shader, vao, vao.getIndices()[i + 1], v2);
        vertexShader(shader, vao, vao.getIndices()[i + 2], v3);
        
        r.rasterizeTriangle(Vector2(v1.x / v1.z, v1.y / v1. z), Vector2(v2.x / v2.z, v2.y / v2.z), Vector2(v3.x / v3.z, v3.y / v3.z));
    }
}