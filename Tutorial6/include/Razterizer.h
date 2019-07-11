#ifndef INCLUDE_RAZTERIZER_H
#define INCLUDE_RAZTERIZER_H

#include "Framebuffer.h"

class Vector2;
class Vector3;
class Vector4;
class Matrix44;

class Razterizer{
    public:
        Razterizer(int width, int height);
        virtual ~Razterizer();

        void razterizeTriangle(const Vector2& v1, const Vector2& v2, const Vector2& v3);

        inline Framebuffer* getFramebuffer() const {return fb;}

        inline void presentFrame(int x, int y){
            fb->print(x, y);
        }

        inline void clearFrame(){
            fb->clear(0);
        }

    private:
        Framebuffer* fb;
        void initializeFramebuffer(int width, int height);
};

#endif
