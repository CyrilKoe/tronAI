#ifndef NETWORK_H
#define NETWORK_H

#include <vector>
#include <map>
#include <random>
#include <cstdlib>
#include <math.h>

#include "layer.h"
#include "utils/matrix.h"

class Network
{
protected:
    std::vector<Layer *> layers;
    Matrix<float> *in = nullptr;

public:
    Network() {}
    Network(std::vector<unsigned int> layer_sizes)
    {
        for (unsigned int i = 0; i < layer_sizes.size() - 1; i++)
        {
            layers.push_back(new Layer(layer_sizes[i], layer_sizes[i + 1]));
        }
    }

    ~Network()
    {
    }

    Matrix<float> *forward(Matrix<float> &inputs)
    {
        if (in != nullptr)
        {
            delete in;
        }
        in = new Matrix<float>(inputs);
        Matrix<float> *out = in;
        for (auto lay : layers)
        {
            out = lay->forward((*out));
        }
        return out;
    }

    void backward(Matrix<float> &expected_outputs, float eta)
    {
        Matrix<float> next_delta, next_weights;
        unsigned int N = layers.size();
        next_delta = layers[N - 1]->backward(*in, expected_outputs, eta);
    }

    void print(std::stringstream &ss)
    {
        ss << "-----\n";
        for (auto lay : layers)
        {
            lay->print(ss);
            ss << "-----\n";
        }
    }
};
#endif