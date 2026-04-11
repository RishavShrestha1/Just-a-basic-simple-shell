#include <SDL2/SDL.h>
#include "D:/SDL2_ttf-devel-2.24.0-mingw/SDL2_ttf-2.24.0/x86_64-w64-mingw32/include/SDL2/SDL_ttf.h"
#include <iostream>

bool init();
void close();

SDL_Window* shellWindow = NULL;
SDL_Renderer* shellRenderer = NULL;
SDL_Surface* surfScreen = NULL;

bool init(){
    const int SCREEN_WIDTH = 740;
    const int SCREEN_HEIGTH = 450;
    bool initialized = true;

    if(SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "Failed to initialize Video! SDL_ERROR :"<<SDL_GetError() <<std::endl;
        initialized = false;
    }

    if(TTF_Init != 0) {
        std::cerr << "Failed to initialize SDL_ttf! TTF_ERROR : "<<TTF_GetError() <<std::endl;
        initialized = false;
    }

    else{
        shellWindow = SDL_CreateWindow("shell", SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGTH,SDL_WINDOW_SHOWN);
        shellRenderer = SDL_CreateRenderer(shellWindow, -1, SDL_RENDERER_ACCELERATED);
        if(shellWindow == NULL || shellRenderer == NULL){
            std::cerr << "Unable to create window and/or renderer! SDL_ERROR : "<<SDL_GetError()<<std::endl;
            initialized = false;
        }
        else{

            surfScreen = SDL_GetWindowSurface(shellWindow);

        }

    }
    return initialized;
}

void close() {
    SDL_DestroyWindow(shellWindow);
    shellWindow = NULL;
    SDL_DestroyRenderer(shellRenderer);
    SDL_Quit();
    TTF_Quit();
}
