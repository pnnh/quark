#include "random.hpp"
#include "random.h"
#include <random>

int quark::PSRandom::randomInt(int min, int max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

double quark::PSRandom::randomDouble(double min, double max)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(min, max);
    return dis(gen);
}

std::string quark::PSRandom::randomString(int length)
{
    std::string str = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    std::string result;
    for (int i = 0; i < length; i++)
    {
        result += str[randomInt(0, str.length() - 1)];
    }
    return result;
}

int MTRandomInt(int min, int max)
{
    return quark::PSRandom::randomInt(min, max);
}