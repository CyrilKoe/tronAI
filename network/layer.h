#ifndef LAYER_H
#define LAYER_H

#include <vector>
#include <map>
#include <random>
#include <cstdlib>

#include "utils/matrix.h"

class Layer
{
private:
    Matrix<float> weights, delta;
    // Dynamic size of input (batch)
    Matrix<float> *out = nullptr, *pre_out = nullptr;

public:
    Layer(unsigned int inputs, unsigned int outputs) : weights(inputs, outputs), delta(inputs, outputs)
    {
        weights.randomise(-1, 1);
    }

    ~Layer()
    {
    }

    Matrix<float> *forward(Matrix<float> &inputs)
    {
        delete pre_out;
        delete out;
        pre_out = new Matrix<float>(inputs % weights);
        out = new Matrix<float>(*pre_out);
        return out;
    }

    Matrix<float> &backward(Matrix<float> &in, Matrix<float> &next_weights, Matrix<float> &next_errors, float eta)
    {
        Matrix<float> next_weights_t = next_weights.transposed();
        delta = (next_errors % next_weights_t);

        Matrix<float> in_t = in.transposed();
        Matrix<float> gradient = in_t % delta * eta;
        weights = weights - gradient;
        return delta;
    }

    Matrix<float> &backward(Matrix<float> &in, Matrix<float> &expected_outputs, float eta)
    {
        Matrix<float> in_t = in.transposed();

        delta = expected_outputs - (*out);
        delta = delta;

        Matrix<float> gradient = in_t % delta * eta;

        weights = weights + gradient;

        return delta;
    }

    void print(std::stringstream &ss)
    {
        ss << "Lay size (" << weights.get_m() << ", " << weights.get_n() << ") \n";
        weights.print(ss);
    }

    Matrix<float> &get_weights() { return weights; }
    Matrix<float> *get_out() { return out; }
};
#endif