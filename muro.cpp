#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "constants.hpp"

class Muro
{
    private:
        sf::RectangleShape body;
        sf::Vector2f pos;
        float width, height;
        bool floating;
        bool canFloat, canMove;

    public:
        Muro(float x, float y, float width, float height, sf::Color color = sf::Color::Red)  {
            this->pos.x = x;
            this->pos.y = y;
            this->width = width;
            this->height = height;

            this->body.setFillColor(color);
            this->setPos(pos);
        }

        void setPos(sf::Vector2f pos) 
        {
            this->body.setPosition(pos);
        }

        void isHitting(Palla& p)
        {
            if (this->pos.x
        }

        void hitting()
        {
            p.setVel(0,0);
        }
};
