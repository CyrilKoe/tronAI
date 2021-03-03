#ifndef MAP_H
#define MAP_H

#include <SDL2/SDL.h>
#include "utils.h"

class Game;

class Map
{
private:
    Game *game;
    unsigned int screen_width, screen_height;
    unsigned int width, height, size;
    unsigned int boxes_width, boxes_height;
    uint8_t *content = nullptr;

public:
    Map(unsigned int _screen_width, unsigned int _screen_height, unsigned int _width, unsigned int _height) : screen_width(_screen_width), screen_height(_screen_height), width(_width), height(_height)
    {
        boxes_width = screen_width / width;
        boxes_height = screen_height / height;
        size = width * height;
        content = new uint8_t[size];
        for (unsigned int i = 0; i < size; i++)
            content[i] = 0;
    }

    ~Map()
    {
        if (content)
            delete[] content;
    }

    void update(float dt);

    bool update_player_pos(unsigned int pos_x, unsigned int pos_y, uint8_t player_id)
    {
        if (!((pos_x >= 0 && pos_x < width) && (pos_y >= 0 && pos_y < height)))
            return false;

        if (content[pos_x + pos_y * width])
            return false;

        content[pos_x + pos_y * width] = player_id;
        return true;
    }
    void draw(SDL_Renderer *renderer);
    unsigned int read_distance(unsigned int pos_x, unsigned int pos_y, direction_t reading_direction);
};

#endif