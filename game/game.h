#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <SDL2/SDL.h>

#include "map.h"
#include "player.h"
#include "network.h"

class Game
{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;

    bool is_human = false, is_learning = false;
    Uint32 last_t = 0, new_t = 0, update_t = 100, delay_t = update_t + 1;
    float dt;

    unsigned int screen_width = 600, screen_height = 600;
    bool is_finished = false;

    Map *map;
    Player *player;

    Network *ai_network = nullptr;

    bool loop();
    void update();
    void draw();
    bool is_closed();

public:
    Game() {}

    ~Game() {}

    bool start(bool _is_human, bool _is_learning, Network *_ai_network);
    bool init();

    unsigned int get_screen_width() { return screen_width; }
    unsigned int get_screen_height() { return screen_height; }
};

#endif
