#define SDL_MAIN_USE_CALLBACKS

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <cglm/cglm.h>

#define S_TRUCTURES_IMPLEMENTATION
#include <S_tructures.h>

#include "cmake.h"
#include "coob.h"
#include "object.h"

static SDL_Window* window = NULL;
static SDL_GLContext gpu = NULL;

static Object* objects = NULL;

static SDL_AppResult SDL_Fail() {
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "%s", SDL_GetError());
    return SDL_APP_FAILURE;
}

SDL_AppResult SDL_AppInit(void** ctx, int argc, char* argv[]) {
    (void)ctx, (void)argc, (void)argv;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    // SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
        return SDL_Fail();

    window = SDL_CreateWindow(GAME_NAME, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window)
        return SDL_Fail();

    if (!SDL_GL_CreateContext(window))
        return SDL_Fail();

    SDL_GL_SetSwapInterval(-1);
    SDL_LogInfo(SDL_LOG_CATEGORY_CUSTOM, "%s\n", glGetString(GL_RENDERER));

    glEnable(GL_TEXTURE_2D);

    objects = MakeTinyD(Object);

    Object coob = {.init = init_coob, .draw = draw_coob};
    coob.pos = XYZ(0.f, 0.f, 0.f);
    objects = TinyDAppendPro(objects, &coob);

    SDL_ShowWindow(window);

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* ctx, SDL_Event* event) {
    (void)ctx;

    switch (event->type) {
    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
        return SDL_APP_SUCCESS;

    case SDL_EVENT_KEY_DOWN:
        if (event->key.key == SDLK_ESCAPE)
            return SDL_APP_SUCCESS;
        break;

    default:
        break;
    }

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void* ctx) {
    (void)ctx;

    for (size_t i = 0; i < TinyDLength(objects); i++) {
        Object* obj = objects + i;

        if (!obj->uhh) {
            if (obj->init)
                obj->init(obj);
            obj->uhh = true;
        }

        if (obj->update)
            obj->update(obj);
    }

    int width = 0, height = 0;
    SDL_GetWindowSizeInPixels(window, &width, &height);
    glViewport(0, 0, width, height);

    glClearColor(0.5f, 0.2f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mat4 proj = {0};
    glm_perspective(glm_rad(45.0f), (float)width / (float)height, 0.01f, 1024.f, proj);

    glMatrixMode(GL_PROJECTION);
    glLoadMatrixf(proj[0]);

    mat4 view = {0};
    glm_lookat(XYZf(3.f, 3.f, 3.f), XYZf(0.f, 0.f, 0.f), XYZf(0.f, 1.f, 0.f), view);

    glMatrixMode(GL_MODELVIEW);
    glLoadMatrixf(view[0]);

    for (size_t i = 0; i < TinyDLength(objects); i++) {
        Object* obj = objects + i;

        if (obj->draw)
            obj->draw(obj);
    }

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* ctx, SDL_AppResult result) {
    (void)ctx, (void)result;

    FreeTinyD(objects); // TODO: individual cleanup?

    if (gpu)
        SDL_GL_DestroyContext(gpu);

    SDL_Quit();
}
