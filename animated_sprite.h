#ifndef _ANIMATED_SPRITE_H_
#define _ANIMATED_SPRITE_H_
#endif

#include <bits/stdc++.h>
#include <SDL2/SDL.h>

using namespace std;

class AnimatedSprite {
    private:
        vector<SDL_Texture*> textures;
        size_t texturesCount = 0;
        size_t currentTextureIndex = 0;
        size_t elapsedTime = 0;
        size_t changeTextureAfterSeconds = 0;
        bool autoReset = false;
    public:
        AnimatedSprite(vector<string> &images, SDL_Renderer *renderer, long desiredFrameRate, bool autoReset);
        ~AnimatedSprite();
        void update(long deltaTime);
        void render(SDL_Renderer *renderer);
        void reset();
};
