#include "./animated_sprite.h"
#include <SDL2/SDL_image.h>

SDL_Texture* loadTexture(const char *path, SDL_Renderer* renderer) {
    SDL_Surface *img_temp = IMG_Load(path);
    if (img_temp == NULL) {
        cerr << "Loading image error: " << SDL_GetError();
        exit(EXIT_FAILURE);
    }

    SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer, img_temp);
    if (texture == NULL) {
        cerr << "Creating texture from surface error: " << SDL_GetError();
        exit(EXIT_FAILURE);
    }

    SDL_FreeSurface(img_temp);

    return texture;
}

AnimatedSprite::AnimatedSprite(vector<string> &images, SDL_Renderer *renderer, long desiredFrameRate, bool autoReset) {
    for (string &path : images) {
        this->textures.push_back(loadTexture(path.c_str(), renderer));
    }

    this->texturesCount = this->textures.size();
    this->changeTextureAfterSeconds = 1000 / desiredFrameRate;
    this->autoReset = autoReset;
}

AnimatedSprite::~AnimatedSprite() {
    for (SDL_Texture *texture : this->textures) {
        SDL_DestroyTexture(texture);
    }
  
}

void AnimatedSprite::update(long deltaTime) {
    this->elapsedTime += deltaTime;

    if (this->elapsedTime > this->changeTextureAfterSeconds) {
        long steps = this->elapsedTime / this->changeTextureAfterSeconds;

        size_t nextIndex = this->currentTextureIndex + steps;

        if (this->autoReset) {
             this->currentTextureIndex = nextIndex % this->texturesCount;
        }
        else {
            this->currentTextureIndex = min(nextIndex, this->texturesCount - 1);
        }       

        this->elapsedTime -= steps * this->changeTextureAfterSeconds;
    }    
}

void AnimatedSprite::render(SDL_Renderer *renderer) {
    SDL_Texture *currentTexture = this->textures[this->currentTextureIndex];

    SDL_RenderCopy(renderer, currentTexture, NULL, NULL);    
}

void AnimatedSprite::reset() {
    this->currentTextureIndex = 0;
}
