#pragma once

#include <glad/gl.h>

typedef struct {
    GLfloat x, y, z;
} Vec3;

#define XYZ(_x, _y, _z) ((Vec3){.x = (_x), .y = (_y), .z = (_z)})
