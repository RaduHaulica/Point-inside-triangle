#pragma once

#include <SFML/Graphics.hpp>

const float pi = 3.141592f;

sf::VertexArray createTriangle(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
    sf::VertexArray va;
    va.append({ p1, sf::Color::White });
    va.append({ p2, sf::Color::White });
    va.append({ p3, sf::Color::White });
    va.append({ p1, sf::Color::White });
    va.setPrimitiveType(sf::PrimitiveType::LineStrip);
    return va;
}

bool isRightOfSegment(sf::Vector2f origin1, sf::Vector2f origin2, sf::Vector2f point)
{
    sf::Vector2f segment = { -(origin2.y - origin1.y), origin2.x - origin1.x }; // B-A then rotate left
    sf::Vector2f movedPoint = point - origin1; // C-A
    float dotProduct = segment.x * movedPoint.x + segment.y * movedPoint.y;
    if (dotProduct > 0)
    {
        std::cout << "right" << std::endl;
        return true;
    }
    std::cout << "left" << std::endl;
    return false;
}

bool insideTriangle(std::vector<sf::Vector2f> triangle, sf::Vector2f point)
{
    if (isRightOfSegment(triangle[0], triangle[1], point))
    {
        if (!isRightOfSegment(triangle[1], triangle[2], point))
            return false;
        if (!isRightOfSegment(triangle[2], triangle[0], point))
            return false;
        return true;
    }
    else
    {
        if (isRightOfSegment(triangle[1], triangle[2], point))
            return false;
        if (isRightOfSegment(triangle[2], triangle[0], point))
            return false;
        return true;
    }
}