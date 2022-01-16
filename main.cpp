#include <bits/stdc++.h>

using namespace std;

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "./animated_sprite.h"

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 480

AnimatedSprite* createAnimation(string prefix, string sufix, int count, SDL_Renderer *renderer, size_t desiredFrameRate, bool autoReset);
bool isWalking(const Uint8 *currentKeyStates);
bool isRunning(const Uint8 *currentKeyStates);
bool isJumping(const Uint8 *currentKeyStates);
bool isDying(const Uint8 *currentKeyStates);

int main(void) {
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cerr << "SDL error: " << SDL_GetError();
        exit(EXIT_FAILURE);
    }

    int imageFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imageFlags) & imageFlags)) {
        cerr << "Initializing IMG error: " << IMG_GetError();
    }


    window = SDL_CreateWindow(
        "SDL Tutorial",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN
    );
    if (window == NULL) {
        cerr << "Creating window error: " << SDL_GetError();
        exit(EXIT_FAILURE);
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        cerr << "Creating renderer error: " << SDL_GetError();
        exit(EXIT_FAILURE);
    }
   

    AnimatedSprite *idle = createAnimation("./sprites/boy/Idle (", ").png", 15, renderer, 30l, true);
    AnimatedSprite *walk = createAnimation("./sprites/boy/Walk (", ").png", 15, renderer, 30l, true);
    AnimatedSprite *run = createAnimation("./sprites/boy/Run (", ").png", 15, renderer, 30l, true);
    AnimatedSprite *jump = createAnimation("./sprites/boy/Jump (", ").png", 15, renderer, 20l, true);
    AnimatedSprite *dead = createAnimation("./sprites/boy/Dead (", ").png", 15, renderer, 30l, false);
    AnimatedSprite *currentAnimation = idle;

    bool quit = false;
    SDL_Event e;    

    long lastTime = SDL_GetTicks();
    long deltaTime = 0;

    while (!quit) {
        long startGameLoopTime = SDL_GetTicks();
        
        SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            }
            else if (e.type == SDL_KEYDOWN) {
                switch(e.key.keysym.sym)
                {
                    case SDLK_ESCAPE:
                    case SDLK_q:
                        quit = true;
                        break;
                }
            }           
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);

        if (isJumping(currentKeyStates)) {
            currentAnimation = jump;
        }
        else if (isRunning(currentKeyStates)) {
            currentAnimation = run;
        }
        else if (isWalking(currentKeyStates)) {
            currentAnimation = walk;
        }
        else if (isDying(currentKeyStates)) {
            if (currentAnimation != dead) {
                dead->reset();
            }

            currentAnimation = dead;
        }
        else if (currentAnimation != dead) {
            currentAnimation = idle;
        }

        SDL_RenderClear(renderer);
       
        currentAnimation->update(deltaTime);
        currentAnimation->render(renderer);

        SDL_RenderPresent(renderer);

        long endGameLoopTime = SDL_GetTicks();
        long deltaGameLoopTime = endGameLoopTime - startGameLoopTime;
        if (deltaGameLoopTime < 16l) {
             SDL_Delay(16l - deltaGameLoopTime); // adjusting to 60 fps...
        }

        long currentTime = SDL_GetTicks();
        deltaTime = currentTime - lastTime;
        lastTime = currentTime;        

        cout << deltaTime << endl;
    }

    delete idle;
    delete walk;
    delete run;
    delete jump;
    delete dead;

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);

    IMG_Quit();
    SDL_Quit();

    return EXIT_SUCCESS;
}

AnimatedSprite* createAnimation(string prefix, string sufix, int count, SDL_Renderer *renderer, size_t desiredFrameRate, bool autoReset) {
    vector<string> images;

    for (int i = 1; i <= count; i++) {
        images.push_back(prefix + to_string(i) + sufix);
    }

    return new AnimatedSprite(images, renderer, desiredFrameRate, autoReset);
}

bool isWalking(const Uint8 *currentKeyStates) {
    return currentKeyStates[SDL_SCANCODE_RIGHT] || currentKeyStates[SDL_SCANCODE_D];
}

bool isRunning(const Uint8 *currentKeyStates) {
    return currentKeyStates[SDL_SCANCODE_LSHIFT] && isWalking(currentKeyStates);
}

bool isJumping(const Uint8 *currentKeyStates) {
    return currentKeyStates[SDL_SCANCODE_SPACE] || currentKeyStates[SDL_SCANCODE_W] || currentKeyStates[SDL_SCANCODE_UP];
}

bool isDying(const Uint8 *currentKeyStates) {
    return currentKeyStates[SDL_SCANCODE_DOWN] || currentKeyStates[SDL_SCANCODE_S];
}
