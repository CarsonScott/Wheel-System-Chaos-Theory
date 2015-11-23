#include "Bucket.hpp"

Bucket::Bucket()
{
    water = 0;
}

float Bucket::get_water()
{
    return water;
}

void Bucket::add(float fill_rate)
{
    water += fill_rate;
}

void Bucket::subtract(float leak_rate)
{
    water -= leak_rate;
}
