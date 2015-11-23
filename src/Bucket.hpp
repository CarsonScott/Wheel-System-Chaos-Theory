#ifndef BUCKET_HPP_INCLUDED
#define BUCKET_HPP_INCLUDED

#include <SFML/Graphics.hpp>

class Bucket:public sf::Sprite
{
    float water;
public:
    Bucket();
    float get_water();
    void add(float);
    void subtract(float);
};

#endif // BUCKET_HPP_INCLUDED
