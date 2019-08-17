#include "Framebuffer.h"
#include <memory.h>

void Framebuffer::recreate(int width, int height){
    this->width = width;
    this->height = height;

    colorbuffer = new colorbuffer_t[width * height];
    depthbuffer = new depthbuffer_t[width * height];
}

void Framebuffer::clear(int clearColor){
    memset(colorbuffer, clearColor, sizeof(colorbuffer_t) * width * height);
    memset(depthbuffer, MAX_DEPTH_VALUE, sizeof(depthbuffer_t) * width * height);
}

void Framebuffer::setPixel(int x, int y, colorbuffer_t pixelcolor, depthbuffer_t depth){
    int index = (y * width) + x;

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

void Framebuffer::print(int offsetx, int offsety){
    for(int i = offsetx; i < width; i++){
        for(int j = offsety; j < height; j++){
            int index = (width * j) + i;

            //if(!colorbuffer[index]) continue;

            int color = (char)(colorbuffer[index] >> 8);
            attron(COLOR_PAIR(color));

            mvprintw(j, i, "%c", (char)colorbuffer[index]);
        }
    }
}
