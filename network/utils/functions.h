float a_linear(float t)
{
    return t;
}

float d_linear(float t)
{
    return 1.0;
}

float a_tanh(float t)
{
    return tanh(t);
}

float d_tanh(float t)
{
    return 1 - tanh(t) * tanh(t);
}