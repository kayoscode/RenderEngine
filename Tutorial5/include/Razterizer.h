#ifndef INCLUDE_RAZTERIZER_H
#define INCLUDE_RAZTERIZER_H

class Vector2;
class Vector3;
class Vector4;
class Matrix44;

struct Framebuffer{
    Framebuffer(int width, int height)
        :width(width), height(height){}

    int width, height;
};

class Razterizer{
    public:
        Razterizer(int width, int height);
        virtual ~Razterizer();

        void razterizeTriangle(const Vector2& v1, const Vector2& v2, const Vector2& v3);

        inline Framebuffer* getFrameBuffer() const {return fb;}

    private:
        Framebuffer* fb;
        void initializeFramebuffer(int width, int height);
};

#endif
