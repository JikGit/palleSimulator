#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <cmath>
#include <iostream>
#include <vector>

#include "constants.hpp"

class Palla
{
    private:
        sf::CircleShape body;
        sf::Vector2f pos;
        sf::Vector2f vel;
        float mass;
        float radius;
        bool floating;

    public:
        Palla(float x, float y, float vX, float vY, float massBody, float radius, sf::Color color = sf::Color::Red, bool floating = true) 
        {
            this->pos = {x, y};
            this->vel = {vX, vY};
            this->mass = massBody;
            this->radius = radius;
            
            this-> floating = floating;

            this->body.setRadius(radius);
            this->body.setFillColor(color);
        }

        void render(sf::RenderWindow& window)
        {
            window.draw(this->body);
        }

        sf::Vector2f getPos() 
        {
            return this->pos;
        }

        sf::Vector2f getVel() 
        {
            return this->vel;
        }

        void setVel(float x, float y) {
            this->vel.x = x;
            this->vel.y = y;
        }

        float getRadius() 
        {
            return this->radius;
        }

        float getMass() 
        {
            return this->mass;
        }

        void updatePos() 
        {
            pos.x += vel.x + 1/FRAME_RATE;
            pos.y += vel.y + 1/FRAME_RATE;

            if (this->pos.x >= WIDTH-this->radius || this->pos.x - this->radius <= 0 )
                this->vel.x *= -1;
            if (this->pos.y >= HEIGHT-this->radius || this->pos.y + this->radius <= 0)
                this->vel.y *= -1;
            this->body.setPosition(this->pos);
        }

        void update_vel() 
        {
            if (this->floating) 
                vel.y += G * 1/FRAME_RATE;
            else
                this->floating = true;

            this->updatePos();
        }
        
        bool isHitting(sf::Vector2f pos, float radius) 
        {
            this->floating = false;
            return sqrt(pow(this->pos.x - pos.x, 2) + pow(this->pos.y - pos.y, 2)) <= radius + this->radius;
        }

        void hitting(Palla& p) {
            float m1 = this->mass, m2 = p.getMass();
            float pos1x = this->pos.x, pos1y = this->pos.y, pos2x = p.getPos().x, pos2y = p.getPos().y;
            float vel1x = this->vel.x, vel1y = this->vel.y, vel2x = p.getVel().x, vel2y = p.getVel().y;

            const float THETA = atan2(pos2y - pos1y, pos2x - pos1x);
            const float mTot = m1 + m2;

            //palle sovrapposte
            const float D = -this->radius - p.getRadius() + sqrt(pow(pos1x - pos2x, 2) + pow(pos1y - pos2y, 2));
            if (D < 0) 
            {
                /* pos1x += this->radius; */
                /* pos1y += this->radius; */
                /* const float ALPHA = atan2(vel1y, vel1x); */
                /* const float GAMMA = ALPHA + THETA; */
                /* pos1x += D * sin(GAMMA); */
                /* pos1y += D * cos(GAMMA); */

                /* std::cout << "asdfsafasddfas" << std::endl; */
                /* std::cout << -this->radius - p.getRadius() + sqrt(pow(pos1x - pos2x, 2) + pow(pos1y - pos2y, 2)); */
                /* std::cout << std::endl; */
                /* std::cout << std::endl; */
            }


            float v1r = (vel1x * cos(THETA)) + (vel1y * sin(THETA));
            float v2r = (vel2x * cos(THETA)) + (vel2y * sin(THETA));

            float v1r_old = v1r;
            float v2r_old = v2r;

            v1r = (v1r_old * (m1 - m2) + 2 * m2 * v2r_old) / mTot;
            v2r = (v2r_old * (m2 - m1) + 2 * m1 * v1r_old) / mTot;

            float v1t = -vel1x * sin(THETA) + vel1y * cos(THETA);
            float v2t = -vel2x * sin(THETA) + vel2y * cos(THETA);

            this->vel.x = v1r * cos(THETA) - v1t * sin(THETA);
            this->vel.y = v1r * sin(THETA) + v1t * cos(THETA);

            float new2Vx = v2r * cos(THETA) - v2t * sin(THETA);
            float new2Vy = v2r * sin(THETA) + v2t * cos(THETA);

            p.setVel(new2Vx, new2Vy);
        }

        void stop() 
        {
            this->floating = false;
            this->vel.x = 0;
            this->vel.y = 0;
        }
};
