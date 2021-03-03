#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <float.h>

#include <SDL2/SDL.h>
#include "utils.h"
#include "map.h"
#include "../network/utils/matrix.h"
#include "../network/network.h"

class Player
{
private:
    int index;
    bool is_human, is_learning;

    enum direction_t direction;
    unsigned int pos_x, pos_y;
    float learning_rate = 0.05;

    Network *ai_network = nullptr;

    move_t last_move;

    void read_input_queue();
    void ask_ai();
    void learn_ai();

public:
    Player(int _index, bool _is_human, bool _is_learning, Network *_ai_network) : index(_index), is_human(_is_human), is_learning(_is_learning), ai_network(_ai_network)
    {
        direction = (direction_t)(rand() % 4);
        pos_x = rand() % 25 + 10;
        pos_y = rand() % 25 + 10;
    }

    void update(float dt, Map *map);
    void draw();

    float get_pos_x() { return pos_x; }
    float get_pos_y() { return pos_y; }
};

#endif