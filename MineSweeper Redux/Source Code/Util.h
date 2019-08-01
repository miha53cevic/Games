#pragma once
#include <random>

// Random number generator in given range
static float fRandom(float first, float second)
{
    std::random_device rd;
    std::default_random_engine generator(rd()); // rd() provides a random seed
    std::uniform_real_distribution<float> distribution(first, second);

    return distribution(generator);
}

static int iRandom(int first, int second)
{
    std::random_device rd;
    std::default_random_engine generator(rd()); // rd() provides a random seed
    std::uniform_int_distribution<int> distribution(first, second);

    return distribution(generator);
}