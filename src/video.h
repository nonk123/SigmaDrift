#pragma once

#include <SDL3/SDL_stdinc.h>

#include "mesh.h"

bool init_video();
void begin_drawing(), end_drawing();

void draw_mesh(Mesh, Vec3);
