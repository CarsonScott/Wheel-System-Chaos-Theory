#ifndef SYSTEMLOG_HPP_INCLUDED
#define SYSTEMLOG_HPP_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <SFML/Graphics.hpp>

struct Point
{
    float x, y;
    Point(float x, float y)
    {
        this->x = x;
        this->y = y;
    }
};

class Graph
{
    std::vector<sf::Sprite> points;
    sf::Texture point;

    sf::Vector2f origin;

public:
    Graph()
    {
        origin.x = 0;
        origin.y = 300;

        point.loadFromFile("images/point.png");
    }

    void plot(float x, float y)
    {
        sf::Sprite new_point;
        new_point.setTexture(point);

        sf::Vector2f pos;
        pos.x = origin.x + x;
        pos.y = origin.y + y;

        new_point.setPosition(pos);
        points.push_back(new_point);
    }

    void draw(sf::RenderWindow& window)
    {
        for(int i = 0; i < points.size(); i++)
        {
            window.draw(points[i]);
        }
    }
};

class SystemLog
{
    std::vector<Point> points;
    float time, goal;
public:
    Graph graph;

    SystemLog();
    void record_system(float, float);
    void save_to_file(std::string);
    float get_elapsed_time();
};

#endif // SYSTEMLOG_HPP_INCLUDED
