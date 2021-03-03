#include <iostream>
#include <SDL2/SDL.h>

#include "game.h"

// Pointers to our window and renderer
SDL_Window *window;
SDL_Renderer *renderer;

int mouseX = 0, mouseY = 0;

bool Game::loop()
{

    while (!is_finished)
    {
        update();
        draw();
        SDL_Delay(50);
    }

    delete map;
    delete player;

    return true;
}

bool Game::is_closed()
{
    return false;
}

void Game::update()
{

    new_t = SDL_GetTicks();
    if (!last_t)
        last_t = new_t;

    dt = (new_t - last_t);

    delay_t += dt;

    // UPDATE
    if (delay_t > update_t)
    {
        delay_t -= update_t;
        player->update(dt, map);
        is_finished = !map->update_player_pos(player->get_pos_x(), player->get_pos_y(), 1);
        map->update(dt);
    }

    last_t = new_t;
}

void Game::draw()
{
    // Clear the window to white
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // DRAW
    map->draw(renderer);

    SDL_RenderPresent(renderer);
}

bool Game::init()
{

    // See last example for comments
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
        system("pause");
        return false;
    }

    window = SDL_CreateWindow("Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
    if (!window)
    {
        std::cout << "Error creating window: " << SDL_GetError() << std::endl;
        system("pause");
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer)
    {
        std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    return true;
}

bool Game::start(bool _is_human, bool _is_learning, Network *_ai_network)
{
    is_human = _is_human;
    is_learning = _is_learning;
    ai_network = _ai_network;

    is_finished = false;
    map = new Map(screen_width, screen_height, 50, 50);
    player = new Player(0, is_human, is_learning, ai_network);

    loop();

    return true;
}