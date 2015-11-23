#include "WaterWheel.hpp"

int WaterWheel::get_top_bucket_index()
{
    int index = 0;
    for(int i = 0; i < 8; i++)
    {
        if(buckets[i].getGlobalBounds().top < buckets[index].getGlobalBounds().top)
        {
            index = i;
        }
    }

    return index;
}

void WaterWheel::fill_bucket(float fill_rate)
{
    int top_index = get_top_bucket_index();
    buckets[top_index].add(fill_rate);
}

void WaterWheel::leak_buckets(float leak_rate)
{
    for(int i = 0; i < 8; i++)
    {
        buckets[i].subtract(leak_rate);
    }
}

void WaterWheel::update_spin(float dt)
{
    float left, right;
    left = 0;
    right = 0;

    int index = get_top_bucket_index();
    for(int i = 0; i < 8; i++)
    {
        if(i < 4)
        {
            right += buckets[index].get_water();
        }
        else
        {
            left += buckets[index].get_water();
        }

        if(index < 8)
        {
            index ++;
        }
        else
        {
            index = 0;
        }
    }

    if(left > right)
    {
        spin -= accel*(left/right)*dt;
    }
    else if(right > left)
    {
        spin += accel*(right/left)*dt;
    }
}

void WaterWheel::rotate_buckets(float dt)
{
    for(int i = 0; i < 8; i++)
    {
        buckets[i].rotate(spin*dt);
    }
}

WaterWheel::WaterWheel(sf::Vector2f position)
{
    axle_texture.loadFromFile("images/axle.png");
    axle.setTexture(axle_texture);
    axle.setOrigin(axle.getTextureRect().width/2, axle.getTextureRect().height/2);
    axle.setPosition(position);

    axle.setScale(sf::Vector2f(3, 3));

    bucket_texture.loadFromFile("images/bucket.png");
    for(int i = 0; i < 8; i++)
    {
        buckets[i] = Bucket();
        buckets[i].setTexture(bucket_texture);
        buckets[i].setPosition(position);
        buckets[i].setOrigin(0, buckets[i].getTextureRect().height / 2);
        buckets[i].setRotation(360/8*i);
    }

    spin = 0;
    accel = 30;
}

void WaterWheel::update(float add_water, float subtract_water, float dt)
{
    fill_bucket(add_water*dt);
    leak_buckets(subtract_water*dt);
    update_spin(dt);
    rotate_buckets(dt);
    axle.rotate(spin*dt);
}

void WaterWheel::draw(sf::RenderWindow& window)
{
    for(int i = 0; i < 8; i++)
    {
        window.draw(buckets[i]);
    }
    window.draw(axle);
}

float WaterWheel::get_spin()
{
    return spin;
}
