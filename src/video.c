#include <SDL3/SDL_log.h>

#include <S_tructures.h>

#include "video.h"

void draw_mesh(Mesh mesh, Vec3 pos) {
    glPushMatrix();
    glTranslatef(pos.x, pos.y, pos.z);

    glBegin(GL_TRIANGLES);

    for (size_t i = 0; i < TinyDLength(mesh.da_nachos); i++) {
        Nacho nacho = mesh.da_nachos[i];
        Vec3 points[3] = {mesh.da_vertices[nacho.a], mesh.da_vertices[nacho.b], mesh.da_vertices[nacho.c]};

        for (size_t j = 0; j < SDL_arraysize(points); j++) {
            glColor3f(1.f, 0.2f, 0.2f);
            glVertex3f(points[j].x, points[j].y, points[j].z);
        }
    }

    glEnd();

    glPopMatrix();
}
