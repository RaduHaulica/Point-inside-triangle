#include <SFML/Graphics.hpp>
#include <cmath>
#include <iostream>
#include <string>

#include "utils.h"

int main()
{
    float pixelWidth = 800.0f;
    sf::RenderWindow window(sf::VideoMode(pixelWidth, pixelWidth), "SFML works!");
    sf::View camera;
	
    sf::Font font;
    font.loadFromFile("./Roboto-Bold.ttf");
	
    sf::Text helpText;
    helpText.setFont(font);
    helpText.setString("First three clicks create a triangle.\nSubsequent clicks add points that are either green (inside) or red (outside).");
    helpText.setCharacterSize(12);
    helpText.setFillColor(sf::Color::White);
    helpText.setPosition({ 0, 0 });

    sf::Vector2i mousePos;
    sf::Vector2f mousePosWorld;

    // time
    sf::Clock frameClock;
    float dt;
    float acc{ 0.0f }, t;

    std::vector<sf::Vector2f> points;
    sf::VertexArray pointsVA;
    std::vector<sf::Vector2f> triangle;
    bool triangleExists = false;
    bool addPoint = false;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::MouseButtonPressed)
            {
                addPoint = true;
            }
        }

        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        sf::Vector2f mousePosWorld = window.mapPixelToCoords(mousePos);

        dt = frameClock.restart().asSeconds();
        acc += dt;
        t = acc / 0.2f;

        // meat and potatoes
        if (addPoint)
        {
            if (!triangleExists)
            {
                triangle.push_back({ mousePosWorld.x, mousePosWorld.y });
            }
            else
            {
                points.push_back({ mousePosWorld.x, mousePosWorld.y });
                if (insideTriangle(triangle, { mousePosWorld.x, mousePosWorld.y }))
                {
                    pointsVA.append({ {mousePosWorld.x, mousePosWorld.y}, sf::Color::White });
                }
                else
                {
                    pointsVA.append({ {mousePosWorld.x, mousePosWorld.y}, sf::Color::Red });
                }
            }
            addPoint = false;
        }

        if (triangle.size() == 3)
        {
            triangleExists = true;
        }

        //draw
        window.clear();

        if (triangleExists)
        {
            window.draw(createTriangle(triangle[0], triangle[1], triangle[2]));
            window.draw(pointsVA);
        }
        window.draw(helpText);
        window.display();
    }

    return 0;
}