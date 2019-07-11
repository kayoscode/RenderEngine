#include "GenMath.h"
#include "defs.h"

float GenMath::interpolate(float a, float b, float t){
    return a + ((b - a) * t);
}

float GenMath::toRadians(float degrees){
    return (PI/180.0f) * degrees;
}

float GenMath::toDegress(float radians){
    return (180.0f/PI) * radians;
}
