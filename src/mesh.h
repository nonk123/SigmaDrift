#pragma once

#include <glad/gl.h>

#include "vmath.h"

typedef struct {
    uint16_t a, b, c;
} Nacho;

typedef struct {
    Vec3* da_vertices;
    Nacho* da_nachos;
} Mesh;

void gen_box(Mesh*, Vec3);
