#include "Rasterizer.h"
#include "defs.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"

#include <math.h>
#include <atomic>

std::atomic<bool> renderStart, renderFinished, programRunning;

#define ATTRIBUTEV1 0
#define ATTRIBUTEV2 1
#define ATTRIBUTEV3 2
#define ATTRIBUTEPASS 3

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

static Vector3 getBarryCentricCoordinates(int ptx, int pty, const Vector2& v1, const Vector2& v2, const Vector2& v3) {
    Vector3 ret;

    ret.x = ((v2.y - v3.y) * (ptx - v3.x) +
            (v3.x - v2.x) * (pty - v3.y)) /
        ((v2.y - v3.y) * (v1.x - v3.x) +
         (v3.x - v2.x) * (v1.y - v3.y));

    ret.y = ((v3.y - v1.y) * (ptx - v3.x) +
            (v1.x - v3.x) * (pty - v3.y)) /
        ((v2.y - v3.y) * (v1.x - v3.x) +
         (v3.x - v2.x) * (v1.y - v3.y));

    ret.z = 1.0f - ret.x - ret.y;

    return ret;
}

static inline bool isPointInTriangle(const Vector3& barryCentric)
{
    int one = (barryCentric.x < -0.001);
    int two = (barryCentric.y < -0.001);
    int three = (barryCentric.z < -0.001);

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

void Rasterizer::rasterizeTriangle(const Vector4& vv1, const Vector4& vv2, const Vector4& vv3, ShaderProgram& shader, DataList** passAttributes){
    int rawSize = 0;

    //allocate pass size
    for(int i = 0; i < passAttributes[ATTRIBUTEV1]->getLocationCount(); i++) {
        passAttributes[ATTRIBUTEPASS]->bind(nullptr, passAttributes[ATTRIBUTEV1]->getLocationSize(i));
        rawSize += passAttributes[ATTRIBUTEV1]->getLocationSize(i);
    }

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

    float z1 = 1 / vv1.z;
    float z2 = 1 / vv2.z;
    float z3 = 1 / vv3.z;

    for(int j = miny; j < maxy; j++){
        for(int i = minx; i < maxx; i++){
            Vector3 barryCentric = getBarryCentricCoordinates(i, j, v1, v2, v3);
            Vector4 fragmentOutput;

            if(isPointInTriangle(barryCentric)){
                float zInterpolated = z1 * barryCentric.x + z2 * barryCentric.y + z3 * barryCentric.z;

                //loop through each vertex and interpolate each value (DO NOT USE AFFINE SPACE INTERPOLATION)
                //compute projection space interpolation
                for(int i = 0; i < rawSize; i++) {
                    float value1 = passAttributes[ATTRIBUTEV1]->getRawValue(i) / vv1.z;
                    float value2 = passAttributes[ATTRIBUTEV2]->getRawValue(i) / vv2.z;
                    float value3 = passAttributes[ATTRIBUTEV3]->getRawValue(i) / vv3.z;

                    //interpolate between the three values using barrycentric interpolation
                    float interpolatedValue = (value1 * barryCentric.x) + (value2 * barryCentric.y) + (value3 * barryCentric.z);
                    passAttributes[ATTRIBUTEPASS]->setRawValue(i, interpolatedValue / zInterpolated);
                }

                char fbValue = shader.executeFragmentShader(passAttributes[ATTRIBUTEPASS], fragmentOutput);
                float fragDepth = (vv1.z / vv1.w) * barryCentric.x + (vv2.z / vv2.w) * barryCentric.y + (vv3.z / vv3.w) * barryCentric.z;
                depthbuffer_t finalDepth = fragDepth * MAX_DEPTH_VALUE;

                fb->setPixel(i, j, fbValue, finalDepth);
            }
        }
    }
}

void RenderContext::renderIndexedTriangles(ShaderProgram& shader, VertexArrayObject& vao) {
    shader.prepare();
    Vector4 v1, v2, v3;

    DataList** passAttributes = shader.getPassBuffers();
    passAttributes[ATTRIBUTEV1]->clear();
    passAttributes[ATTRIBUTEV2]->clear();
    passAttributes[ATTRIBUTEV3]->clear();
    passAttributes[ATTRIBUTEPASS]->clear();

    for(int i = 0; i < vao.getIndicesCount(); i += 3) {
        shader.executeVertexShader(vao.getBufferData(), passAttributes[0], vao.getIndices()[i + 0], v1);
        shader.executeVertexShader(vao.getBufferData(), passAttributes[1], vao.getIndices()[i + 1], v2);
        shader.executeVertexShader(vao.getBufferData(), passAttributes[2], vao.getIndices()[i + 2], v3);

        v1.x /= v1.z;
        v1.y /= v1.z;
        
        v2.x /= v2.z;
        v2.y /= v2.z;

        v3.x /= v3.z;
        v3.y /= v3.z;

        r.rasterizeTriangle(v1, v2, v3, shader, passAttributes);
        passAttributes[ATTRIBUTEV1]->clear();
        passAttributes[ATTRIBUTEV2]->clear();
        passAttributes[ATTRIBUTEV3]->clear();
        passAttributes[ATTRIBUTEPASS]->clear();
    }
}