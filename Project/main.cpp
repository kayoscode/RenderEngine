#include "defs.h"
#include <iostream>
#include <vector>

#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Rasterizer.h"
#include "Matrix44.h"
#include "GenMath.h"
#include "Camera.h"
#include "Loader.h"
#include "Shader.h"

#include "BasicShaders.h"
#include <atomic>

RenderContext* renderContext;
Camera* cam = nullptr;

IndexedModel model;
VertexObject modelVao(3);

BasicVertexShader vs;
FragmentShader fs(1000);
ShaderProgram shader((VertexShader*)&vs, &fs);

std::atomic<float> angle(.001f);

bool renderCB(){
    renderContext->getRasterizer()->clearFrame();
    angle = angle + .01;

    Matrix44 transformation;
    transformation.translate(Vector3(0, 0, -3.));
    transformation.scale(Vector3(1, 1, 1));
    transformation.rotate(Vector3(.3f, 1, .8f).normalize(), angle);

    cam->calculateViewMatrix();

    //set uniforms
    shader.vs->getUniforms()->set(vs.location_projectionMatrix, cam->getProjectionMatrix());
    shader.vs->getUniforms()->set(vs.location_viewMatrix, cam->getViewMatrix());
    shader.vs->getUniforms()->set(vs.location_transformation, transformation);

    renderContext->renderIndexedTriangles(shader, modelVao);

    return true;
}

int main(void){
    if(loadIndexedModel("res/cube.obj", model)) {}
    else {
        std::cout << "failed to load model\n";
        return -1;
    }

    //load model into VAO
    modelVao.bufferData(0, model.positions, model.positionsCount, 3);
    modelVao.bufferData(1, model.uvs, model.uvsCount, 2);
    modelVao.bufferData(2, model.normals, model.normalsCount, 3);
    modelVao.bufferIndices(model.indices, model.indexCount);

	initscr();
	raw();
	noecho();
    start_color();
    cbreak();
    curs_set(0);

    renderContext = new RenderContext(WW, WH);
    cam = new Camera();
    cam->createProjection(1.4, (WW / (float)2) / WH, .2f, 400);

    renderContext->getRasterizer()->setRenderCB(renderCB);

    while(true){
        renderContext->getRasterizer()->presentFrame();
        renderContext->getRasterizer()->swapBuffers();

        refresh();
        erase();
    }

    getch();
    clear();
    endwin();

    delete renderContext;
    delete cam;

    return 0;
}
