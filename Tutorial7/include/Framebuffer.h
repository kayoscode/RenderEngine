#ifndef INCLUDE_FRAMEBUFFER_H
#define INCLUDE_FRAMEBUFFER_H

#include "defs.h"

typedef uint8_t depthbuffer_t;
typedef uint16_t colorbuffer_t;

#define MAX_DEPTH_VALUE 0xFF

class Framebuffer{
    public:
        Framebuffer(int width, int height);
        ~Framebuffer();

        void recreate(int width, int height);
        void clear(int clearColor);

        void setPixel(int x, int y, colorbuffer_t pixelcolor, depthbuffer_t depth);
        
        colorbuffer_t getColor(int x, int y);
        depthbuffer_t getDepth(int x, int y);

        inline int getWidth() const {return width;}
        inline int getHeight() const {return height;}

        void print(int offsetx, int offsety);

    private:
        int width, height;

        depthbuffer_t* depthbuffer;
        colorbuffer_t* colorbuffer;
};

#endif
