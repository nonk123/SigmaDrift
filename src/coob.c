#include <stdio.h>

#include "coob.h"
#include "video.h"

void init_coob(Object* this) {
    gen_box(&this->meshes[0], XYZ(1.f, 1.f, 1.f));
    printf("HI COOB\n");
}

void draw_coob(const Object* this) {
    draw_mesh(this->meshes[0], this->pos);
}
