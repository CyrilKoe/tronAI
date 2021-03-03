#include <iostream>
#include <sstream>
#include <vector>
#include <math.h>
#include "network.h"
#include "network/utils/matrix.h"
#include "game/game.h"

int main(int argc, char **args)
{
    // TODO JUST ONE LAYER CAUSE CRASH

    Game game;

    unsigned int input_dim = 4, output_dim = 4;
    Network net({input_dim, output_dim});

    game.init();

    while (true)
    {
        game.start(false, false, &net);
        std::stringstream ss;
        net.print(ss);
        ss << "\n";
        std::cout << ss.str();
        ss.flush();

        game.start(true, true, &net);

        net.print(ss);
        ss << "\n";
        std::cout << ss.str();
    }

    /*

    unsigned int batch_size = 1;
    unsigned int input_dim = 4;
    unsigned int output_dim = 2;

    Network net({input_dim, output_dim});
    Matrix<float> targets(batch_size, output_dim, {4.8, 0.1});

    Matrix<float> *outputs = nullptr;

    std::stringstream ss;
    net.print(ss);
    ss << "\n";

    for (unsigned int i = 0; i < 100; i++)
    {
        Matrix<float> inputs(batch_size, input_dim, {(float)i / 100, 0.6, 0.6, 0.0});
        outputs = net.forward(inputs);
        net.backward(targets, 0.02);
        outputs->print(ss);
    }
    std::cout << ss.str();
    */

    return 0;
}