#include "player.h"

void Player::update(float dt, Map *map)
{
    last_move.dist_u = map->read_distance(pos_x, pos_y, UP);
    last_move.dist_r = map->read_distance(pos_x, pos_y, RIGHT);
    last_move.dist_l = map->read_distance(pos_x, pos_y, LEFT);
    last_move.dist_d = map->read_distance(pos_x, pos_y, DOWN);
    last_move.pos_x = pos_x;
    last_move.pos_y = pos_y;

    if (is_human)
    {
        read_input_queue();
    }
    else
    {
        ask_ai();
    }

    last_move.direction = direction;

    switch (direction)
    {
    case UP:
        pos_y += 1;
        break;
    case DOWN:
        pos_y -= 1;
        break;
    case RIGHT:
        pos_x += 1;
        break;
    case LEFT:
        pos_x -= 1;
        break;
    }

    if (is_learning)
    {
        learn_ai();
    }
}

void Player::read_input_queue()
{
    SDL_Event e;

    while (SDL_PollEvent(&e) != 0)
    {

        if (e.type == SDL_QUIT)
        {
            SDL_Quit();
            exit(1);
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_DOWN:
                direction = UP;
                break;
            case SDLK_UP:
                direction = DOWN;
                break;
            case SDLK_RIGHT:
                direction = RIGHT;
                break;
            case SDLK_LEFT:
                direction = LEFT;
                break;
            }
        }
    }
}

void Player::ask_ai()
{
    Matrix<float> last_move_matrix(1, 4, {(float)last_move.dist_u / 50, (float)last_move.dist_r / 50, (float)last_move.dist_d / 50, (float)last_move.dist_l / 50});
    Matrix<float> *output = ai_network->forward(last_move_matrix);
    int max_idx = 0;
    float max_val = FLT_MIN;
    for (int i = 0; i < 4; i++)
    {
        if ((*output)(0, i) > max_val)
        {
            max_idx = i;
            max_val = (*output)(0, i);
        }
    }
    direction = (direction_t)max_idx;
}

// Learn with the player input
void Player::learn_ai()
{
    Matrix<float> last_move_matrix(1, 4, {(float)last_move.dist_u / 50, (float)last_move.dist_r / 50, (float)last_move.dist_d / 50, (float)last_move.dist_l / 50});
    Matrix<float> desired_output(1, 4, {(float)(last_move.direction == UP), (float)(last_move.direction == RIGHT), (float)(last_move.direction == DOWN), (float)(last_move.direction == LEFT)});
    ai_network->backward(desired_output, learning_rate);
}