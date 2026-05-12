#include <S_tructures.h>

#include "mesh.h"

void gen_box(Mesh* out, Vec3 size) {
    if (!out)
        return;

    Vec3 ext = {size.x * 0.5f, size.y * 0.5f, size.z * 0.5f};

    FreeTinyD(out->da_vertices);
    FreeTinyD(out->da_nachos);

    MakeTinyD(Vec3);

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

    glGenBuffers(1, &out->vbo);
    glBindBuffer(GL_ARRAY_BUFFER, out->vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glGenBuffers(1, &out->ibo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, out->ibo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(nachos), nachos, GL_STATIC_DRAW);
}
