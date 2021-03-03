#include "map.h"

void Map::draw(SDL_Renderer *renderer)
{
    //unsigned int screen_width = game->get_screen_width();
    //unsigned int screen_height = game->get_screen_height();

    for (unsigned int k = 0; k < size; k++)
    {
        unsigned int i = k % width;
        unsigned int j = int(k / width);

        SDL_Rect box;
        box.x = i * boxes_width;
        box.y = j * boxes_height;
        box.w = boxes_width;
        box.h = boxes_height;

        switch (content[k])
        {
        case 0:
            SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, SDL_ALPHA_OPAQUE);
            break;
        case 1:
            SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, SDL_ALPHA_OPAQUE);
            break;
        default:
            SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, SDL_ALPHA_OPAQUE);
            break;
        }

        // SDL_RenderDrawLine(renderer, width / 2, 0, width, width);
        SDL_RenderFillRect(renderer, &box);
    }
}

void Map::update(float dt)
{
}


unsigned int Map::read_distance(unsigned int pos_x, unsigned int pos_y, direction_t reading_direction)
{
    unsigned int x = pos_x;
    unsigned int y = pos_y;
    unsigned int step_x = 0;
    unsigned int step_y = 0;

    switch (reading_direction)
    {
    case UP:
        step_y = 1;
        break;
    case DOWN:
        step_y = -1;
        break;
    case RIGHT:
        step_x = 1;
        break;
    case LEFT:
        step_x = -1;
        break;
    }

    unsigned int dist = 0;

    x += step_x;
    y += step_y;

    while ((x >= 0 && x < width) && (y >= 0 && y < height))
    {
        if (content[x + y * width] != 0)
        {
            break;
        }
        x += step_x;
        y += step_y;
        dist += 1;
    }

    return dist;
}
