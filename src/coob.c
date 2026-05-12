#include <SDL3/SDL_log.h>

#include "coob.h"
#include "video.h"

void init_coob(Object* this) {
    gen_box(&this->meshes[0], XYZ(1.f, 1.f, 1.f));
    SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "HI COOB");
}

void draw_coob(const Object* this) {
    draw_mesh(this->meshes[0], this->pos);
}
