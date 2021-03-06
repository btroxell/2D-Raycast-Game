// game.h
// Alex Rutan
// 4/1/15

#ifndef GAME_EXIST
#define GAME_EXIST

#include <SDL2/SDL.h>
#include <vector>
#include "game.h"
#include "map.h"
#include "AmmoPickup.h"

class Game
{
    private:
        int resX;
        int resY;
	std::vector<AmmoPickup>itemsAmmo;
        SDL_Window* window;
	SDL_Surface* surface;
	//SDL_Rect srcAmmoRect;
	//SDL_Rect dstAmmoRect;
        SDL_Texture* ammoTexture;
	SDL_Texture* enemyTexture;
	SDL_Texture* weaponTexture;
        SDL_Renderer* renderer;

    public:
        Game();
        ~Game();
        bool init();
        bool loadTextures();
        int run();
        void close();
}; //end Game

#endif //GAME_EXISTS
