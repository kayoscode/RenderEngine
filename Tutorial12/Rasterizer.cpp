#include "Rasterizer.h"
#include "defs.h"
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Matrix44.h"

#include <math.h>
#include <atomic>

#define PASS_ATTRIBUTEV1 0
#define PASS_ATTRIBUTEV2 1
#define PASS_ATTRIBUTEV3 2
#define PASS_ATTRIBUTE_OUT 3

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

void getBarryCentricCoordinates(int ptx, int pty, const Vector2& v1, const Vector2& v2, const Vector2& v3, Vector3& coords) {
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

static inline bool isPointInTriangle(const Vector3& barryCentricCoords)
{
    int one = (barryCentricCoords.x < -0.001);
    int two = (barryCentricCoords.y < -0.001);
    int three = (barryCentricCoords.z < -0.001);

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
    Framebuffer* fb = rFrame;
    int rawSize = 0;

    //allocate pass space
    for(int i = 0; i < passAttributes[PASS_ATTRIBUTEV1]->getTotalCount(); i++) {
        passAttributes[PASS_ATTRIBUTE_OUT]->bind(nullptr, passAttributes[PASS_ATTRIBUTEV1]->getLocationSize(i));
        rawSize += passAttributes[PASS_ATTRIBUTEV1]->getLocationSize(i);
    }

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
    Vector4 fragmentOut;

    for(int j = miny; j < maxy; j++){
        for(int i = minx; i < maxx; i++){
            Vector3 barryCentric;
            getBarryCentricCoordinates(i, j, v1, v2, v3, barryCentric);

            if(isPointInTriangle(barryCentric)){
                float interpolatedInverseZ = z1 * barryCentric.x + z2 * barryCentric.y + z3 * barryCentric.z;

                //loop through each value in the pass buffer and interpolate the value
                //inverse Z allows for translation from AFFINE interpolation
                //allowing projection space interpolation
                for(int i = 0; i < rawSize; i++) {
                    float value1 = passAttributes[PASS_ATTRIBUTEV1]->getRawValue(i) / vv1.z;
                    float value2 = passAttributes[PASS_ATTRIBUTEV2]->getRawValue(i) / vv1.z;
                    float value3 = passAttributes[PASS_ATTRIBUTEV3]->getRawValue(i) / vv1.z;

                    //interpolate between the three values using barrycentric interpolation
                    float interpolatedValue = (value1 * barryCentric.x) + (value2 * barryCentric.y) + (value3 * barryCentric.z);
                    passAttributes[PASS_ATTRIBUTE_OUT]->setRawValue(i, interpolatedValue / interpolatedInverseZ);
                }

                char outputChar = shader.executeFragmentShader(passAttributes[PASS_ATTRIBUTE_OUT], fragmentOut);

                fb->setPixel(i, j, outputChar, 0);
            }
        }
    }
}

void RenderContext::renderIndexedTriangles(ShaderProgram& shader, VertexArrayObject& vao) {
    shader.prepare();
    Vector4 v1, v2, v3;

    DataList** passAttributes = shader.getPassBuffers();
    passAttributes[PASS_ATTRIBUTEV1]->clear();
    passAttributes[PASS_ATTRIBUTEV2]->clear();
    passAttributes[PASS_ATTRIBUTEV3]->clear();
    passAttributes[PASS_ATTRIBUTE_OUT]->clear();

    for(int i = 0; i < vao.getIndicesCount(); i += 3) {
        shader.executeVertexShader(vao.getBufferData(), passAttributes[PASS_ATTRIBUTEV1], vao.getIndices()[i + 0], v1);
        shader.executeVertexShader(vao.getBufferData(), passAttributes[PASS_ATTRIBUTEV2], vao.getIndices()[i + 1], v2);
        shader.executeVertexShader(vao.getBufferData(), passAttributes[PASS_ATTRIBUTEV3], vao.getIndices()[i + 2], v3);

        v1.x /= v1.z;
        v1.y /= v1.z;

        v2.x /= v2.z;
        v2.y /= v2.z;

        v3.x /= v3.z;
        v3.y /= v3.z;
        
        r.rasterizeTriangle(v1, v2, v3, shader, passAttributes);
        passAttributes[PASS_ATTRIBUTEV1]->clear();
        passAttributes[PASS_ATTRIBUTEV2]->clear();
        passAttributes[PASS_ATTRIBUTEV3]->clear();
        passAttributes[PASS_ATTRIBUTE_OUT]->clear();
    }
}