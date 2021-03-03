#ifndef GAME_UTILS_H
#define GAME_UTILS_H

enum direction_t
{
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef struct Move
{
    unsigned int pos_x, pos_y, dist_u, dist_r, dist_d, dist_l;
    direction_t direction;
} move_t;

#endif