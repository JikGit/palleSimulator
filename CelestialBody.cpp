#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <vector>

class CelestialBody
{
    float G = 6.67 / 1e11;
    private:
        sf::CircleShape body;
        sf::Vector2f pos;
        sf::Vector2f vel;
        float mass;

    public:
        static sf::Vector2f centroMassa;
        CelestialBody(float x, float y, float vX, float vY, float massBody, float radius)
        {
            this->pos.x = x;
            this->pos.y = y;
            this->vel.x = vX;
            this->vel.y = vY;
            this->mass = massBody;

            this->body.setPosition(pos);
            this->body.setRadius(radius);
            this->body.setFillColor(sf::Color::Red);
        }


        void render(sf::RenderWindow& window)
        {
            window.draw(this->body);
        }

        void updatePhysics(std::vector <CelestialBody> allBodies)
        {
            /*pos.x += vel.x; pos.y += vel.y;*/
            pos += vel;
            if (pos.y > 800) vel *= -1.0f;
            if (pos.y < 0) vel *= -1.0f;

        }

        void updatePos()
        {
            body.setPosition(pos);
        }

        sf::Vector2f getPos()
        {
            return pos;
        }

        float getMass()
        {
            return mass;
        }

        static sf::Vector2f getCentroMassa() {
            return centroMassa;
        }

        static void setCentroMassa(CelestialBody p1, CelestialBody p2) 
        {
            centroMassa.x = (p1.getMass() * p1.getPos().x + p2.getMass() * p2.getPos().x) / (p1.getMass() + p2.getMass());
            centroMassa.y = (p1.getMass() * p1.getPos().y + p2.getMass() * p2.getPos().y) / (p1.getMass() + p2.getMass());
        }

};
