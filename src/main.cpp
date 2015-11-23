#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <ctime>
#include <cstdlib>
#include <SFML/Graphics.hpp>
#include "WaterWheel.hpp"
#include "SystemLog.hpp"

std::string to_string(float number)
{
    std::stringstream ss(std::stringstream::in | std::stringstream::out);
    ss << number;
    return ss.str();
}

class Button:public sf::Text
{
protected:
    bool clicked, released;
public:

    Button()
    {
        clicked = false;
    }

    void handle_event(sf::Event& event, sf::Vector2f mouse_pos)
    {
        if(getGlobalBounds().contains(mouse_pos))
        {
            if(event.type == sf::Event::MouseButtonPressed)
            {
                clicked = true;
            }
        }
        else
        {
            clicked = false;
        }
    }

    virtual void update() = 0;
};

class HideWheel:public Button
{
    bool hidden;
public:
    HideWheel()
    {
        hidden = true;
        setString("Hide wheel");
    }

    void update()
    {
        if(clicked)
        {
            if(hidden)
            {
                hidden = false;
            }
            else
            {
                hidden = true;
            }

            clicked = false;
        }

        if(hidden)
        {
            setString("Show wheel");
        }
        else
        {
            setString("Hide wheel");
        }
    }

    bool wheel_is_hidden()
    {
        return hidden;
    }
};

class HideGraph:public Button
{
    bool hidden;
public:
    HideGraph()
    {
        hidden = false;
        setString("Hide graph");
    }

    void update()
    {
        if(clicked)
        {
            if(hidden)
            {
                hidden = false;
            }
            else
            {
                hidden = true;
            }
            clicked = false;
        }

        if(hidden)
        {
            setString("Show graph");
        }
        else
        {
            setString("Hide graph");
        }
    }

    bool graph_is_hidden()
    {
        return hidden;
    }
};

class Game
{
public:
    void main(sf::RenderWindow& window)
    {
        sf::Font font;
        font.loadFromFile("consola.ttf");

        sf::Text spin;
        spin.setFont(font);
        spin.setPosition(500, 0);

        sf::Text fill_rate, leak_rate;
        fill_rate.setFont(font);

        leak_rate.setFont(font);
        leak_rate.setPosition(0, 30);

        WaterWheel wheel(sf::Vector2f(300, 300));
        SystemLog log;

        float fill_per_second, leak_per_second;

        srand(time(NULL));

        fill_per_second = (rand () % 100);
        leak_per_second = (rand() % 100);

        fill_rate.setString("fill: " + to_string(fill_per_second));
        leak_rate.setString("leak: " + to_string(leak_per_second));

        HideWheel hideWheel;
        HideGraph hideGraph;

        hideWheel.setFont(font);
        hideGraph.setFont(font);

        hideWheel.setPosition(500, 400);
        hideGraph.setPosition(500, 430);

        float elapsed_time = 0;

        sf::Clock clock;
        while (window.isOpen())
        {
            float dt = clock.restart().asSeconds();
            elapsed_time += dt;

            sf::Event event;
            while (window.pollEvent(event))
            {
                hideWheel.handle_event(event, sf::Vector2f(sf::Mouse::getPosition(window)));
                hideGraph.handle_event(event, sf::Vector2f(sf::Mouse::getPosition(window)));

                if (event.type == sf::Event::Closed || elapsed_time > 60*3) // elapsed_time is in seconds, program reloads after 3 minutes
                {
                    sf::Image graph_image;
                    graph_image.create(800, 400);
                    graph_image.copy(window.capture(), 0, 0, sf::IntRect(0, 0, 800, 600));
                    graph_image.saveToFile("graphs/" + to_string(fill_per_second) + "," + to_string(leak_per_second) + "_" + to_string(log.get_elapsed_time()) + ".png");

                    window.close();
                }
            }
            window.clear(sf::Color(10, 0, 25));

            hideWheel.update();
            hideGraph.update();

            //window.draw(hideWheel);
            window.draw(hideGraph);

            wheel.update(fill_per_second, leak_per_second, dt);
            if(!hideWheel.wheel_is_hidden())
            {
                wheel.draw(window);

            }

            spin.setString("spin: " + to_string(wheel.get_spin()));
            //window.draw(spin);

            window.draw(fill_rate);
            window.draw(leak_rate);

            if(!hideGraph.graph_is_hidden())
            {
                log.graph.draw(window);
            }

            window.display();
            log.record_system(dt, wheel.get_spin());
        }
    }
};

int main()
{
    for(int i = 0; i < 5; i++)
    {
        std::cout << "iteration " << i << std::endl;
        sf::RenderWindow window(sf::VideoMode(800, 600), "Water Wheel Chaotic System");
        Game().main(window);
    }
    return 0;
}
