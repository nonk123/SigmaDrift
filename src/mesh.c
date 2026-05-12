#include <SDL3/SDL_stdinc.h>

#include <S_tructures.h>

#include "mesh.h"

void gen_box(Mesh* out, Vec3 size) {
    if (!out)
        return;

    Vec3 ext = {size.x * 0.5f, size.y * 0.5f, size.z * 0.5f};

    FreeTinyD(out->da_vertices);
    FreeTinyD(out->da_nachos);

    Vec3 verts[8] = {
        XYZ(-ext.x, -ext.y, -ext.z),
        XYZ(-ext.x, -ext.y, +ext.z),
        XYZ(-ext.x, +ext.y, -ext.z),
        XYZ(-ext.x, +ext.y, +ext.z),
        XYZ(+ext.x, -ext.y, -ext.z),
        XYZ(+ext.x, -ext.y, +ext.z),
        XYZ(+ext.x, +ext.y, -ext.z),
        XYZ(+ext.x, +ext.y, +ext.z),
    };

    out->da_vertices = MakeTinyD(Vec3);

    for (size_t i = 0; i < SDL_arraysize(verts); i++)
        out->da_vertices = TinyDAppend(out->da_vertices, verts[i]);

    out->da_nachos = MakeTinyD(Nacho);

    Nacho nachos[12] = {
        {0, 1, 3},
        {0, 3, 2},
        {4, 6, 7},
        {4, 7, 5},
        {0, 4, 5},
        {0, 5, 1},
        {2, 3, 7},
        {2, 7, 6},
        {0, 2, 6},
        {0, 6, 4},
        {1, 5, 7},
        {1, 7, 3}
    };

    for (size_t i = 0; i < SDL_arraysize(nachos); i++)
        out->da_nachos = TinyDAppend(out->da_nachos, nachos[i]);
}
