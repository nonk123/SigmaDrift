#define SDL_MAIN_USE_CALLBACKS

#include <glad/gl.h>

#include <SDL3/SDL_init.h>
#include <SDL3/SDL_log.h>
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_opengl.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_stdinc.h>
#include <SDL3/SDL_video.h>

#include "cmake.h"

static SDL_Window* window = NULL;
static SDL_GLContext gpu = NULL;

SDL_AppResult SDL_Fail() {
    SDL_LogError(SDL_LOG_CATEGORY_CUSTOM, "Error %s", SDL_GetError());
    return SDL_APP_FAILURE;
}

SDL_AppResult SDL_AppInit(void** ctx, int argc, char* argv[]) {
    (void)ctx, (void)argc, (void)argv;

    if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
        return SDL_Fail();

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);

    window = SDL_CreateWindow(GAME_NAME, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

    if (!window)
        return SDL_Fail();

    gpu = SDL_GL_CreateContext(window);

    if (!gpu || !SDL_GL_MakeCurrent(window, gpu))
        return SDL_Fail();

    SDL_ShowWindow(window);
    SDL_GL_SetSwapInterval(-1);

    if (!gladLoadGL((GLADloadfunc)SDL_GL_GetProcAddress))
        return SDL_Fail();

    return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void* ctx, SDL_Event* event) {
    (void)ctx;

    switch (event->type) {
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

    glClearColor(0.5f, 0.2f, 0.5f, 1.f);
    glClear(GL_COLOR_BUFFER_BIT);

#if 0
    glClearDepthf(1.f);
    glClear(GL_DEPTH_BUFFER_BIT);
#endif

    return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void* ctx, SDL_AppResult result) {
    (void)ctx, (void)result;

    if (gpu)
        SDL_GL_DestroyContext(gpu);

    SDL_Quit();
}
