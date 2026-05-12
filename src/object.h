#pragma once

#include <SDL3/SDL_stdinc.h>

#include "mesh.h"
#include "vmath.h"

typedef struct Object {
    void (*init)(struct Object* this);
    void (*update)(struct Object* this);
    void (*draw)(const struct Object* this);

    Vec3 pos;
    Mesh meshes[8];

    bool uhh;
} Object;
