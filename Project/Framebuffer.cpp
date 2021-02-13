#include "Framebuffer.h"
#include <memory.h>

void Framebuffer::recreate(int width, int height){
    this->width = width;
    this->height = height;

    colorbuffer = new colorbuffer_t[width * height];
    depthbuffer = new depthbuffer_t[width * height];
    clear(0);
}

void Framebuffer::clear(int clearColor){
    memset(colorbuffer, clearColor, sizeof(colorbuffer_t) * width * height);
    memset(depthbuffer, MAX_DEPTH_VALUE, sizeof(depthbuffer_t) * width * height);
}

void Framebuffer::setPixel(int x, int y, colorbuffer_t pixelcolor, depthbuffer_t depth){
    int index = (y * width) + x;
    if(index < 0 || index >= (width * height)) return;

    if(depth < depthbuffer[index]){
        colorbuffer[index] = pixelcolor;
        depthbuffer[index] = depth;
    }
}

colorbuffer_t Framebuffer::getColor(int x, int y){
    int index = (y * width) + x;
    return colorbuffer[index];
}

depthbuffer_t Framebuffer::getDepth(int x, int y){
    int index = (y * width) + x;
    return depthbuffer[index];
}

Framebuffer::Framebuffer(int width, int height)
    :width(width), height(height)
{
    recreate(width, height);
}

Framebuffer::~Framebuffer(){
    delete[] colorbuffer;
    delete[] depthbuffer;
}

void Framebuffer::print(){
    for(int i = 0; i < height; i++){
        for(int j = 0; j < width; j++){
            int index = (width * i) + j;

            if(!colorbuffer[index]) {
                //mvprintw(i, j, " ");
                continue;
            }

            //int color = (char)(colorbuffer[index] >> 8);
            //attron(COLOR_PAIR(color));

            mvprintw(i, j, "%c", (char)colorbuffer[index]);
        }
    }
}
