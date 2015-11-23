#ifndef WATERWHEEL_HPP_INCLUDED
#define WATERWHEEL_HPP_INCLUDED

#include <iostream>
#include "Bucket.hpp"

class WaterWheel
{
    sf::Sprite axle;
    sf::Texture bucket_texture, axle_texture;
    Bucket buckets[8];
    float spin, accel;

    void fill_bucket(float);
    void leak_buckets(float);
    void update_spin(float);
    void rotate_buckets(float);
    int get_top_bucket_index();

public:
    WaterWheel(sf::Vector2f);
    void update(float, float, float);
    void draw(sf::RenderWindow&);
    float get_spin();
};

#endif // WATERWHEEL_HPP_INCLUDED
