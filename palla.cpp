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
        bool canFloat, canMove;

    public:
        Palla(float x, float y, float vX, float vY, float massBody, float radius, sf::Color color = sf::Color::Red, bool canFloat = true, bool canMove = true) 
        {
            this->pos = {x, y};
            this->vel = {vX, vY};
            this->mass = massBody;
            this->radius = radius;

            this->floating = canFloat;
            this->canFloat = canFloat;
            this->canMove = canMove;

            this->body.setRadius(radius);
            this->body.setFillColor(color);
            this->body.setPosition(pos);
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

        float getRadius() 
        {
            return this->radius;
        }

        float getMass() 
        {
            return this->mass;
        }

        bool getCanMove() 
        {
            return this->canMove;
        }

        void setVel(float x, float y) {
            this->vel.y = y;
            this->vel.x = x;
        }

        void setPos(sf::Vector2f pos) 
        {
            if (!this->canMove) return;
            this->body.setPosition(pos);
        }

        void updatePhysics(float dt) 
        {
            if (!this->canMove) return;

            if (this->pos.x >= WIDTH-this->radius || this->pos.x - this->radius <= 0 )
                this->vel.x *= -1;
            if (this->pos.y >= HEIGHT-this->radius || this->pos.y + this->radius <= 0)
                this->vel.y *= -1;

            if (this->floating && this->canFloat) 
                vel.y += G * dt;

            pos.x += vel.x * dt;
            pos.y += vel.y * dt;

            this->setPos(this->pos);
        }
        
        bool isHitting(sf::Vector2f pos, float radius) 
        {
            float dx = this->pos.x - pos.x;
            float dy = this->pos.y - pos.y;
            float radiusSum = this->radius + radius;
            bool hitting = dx * dx + dy * dy <= radiusSum * radiusSum;

            if (hitting)        this->floating = false;
            else                this->floating = true;
            return hitting;
        }

        bool overlap(Palla& p) {
            float pos1x = this->getPos().x, pos1y = this->getPos().y, pos2x = p.getPos().x, pos2y = p.getPos().y;
            const float overlap = (this->radius + p.getRadius()) - sqrt(pow(pos1x - pos2x, 2) + pow(pos1y - pos2y, 2));
            if (overlap > 0) {
                const float dx = pos2x - pos1x;
                const float dy = pos2y - pos1y;
                const float distance = sqrt(dx * dx + dy * dy);
                const float adjustX = (dx / distance) * overlap / 2;
                const float adjustY = (dy / distance) * overlap / 2;

                this->pos.x -= adjustX;
                this->pos.y -= adjustY;
                p.pos.x += adjustX;
                p.pos.y += adjustY;

                return 0;
            }
            return 1;
        }

        sf::Vector2f prova (float vr, float vt, const float THETA) 
        {
            float newVx = vr * cos(THETA) - vt * sin(THETA);
            float newVy = vr * sin(THETA) + vt * cos(THETA);
            sf::Vector2f newV = {newVx, newVy};
            return newV;
        }

        void hitting(Palla& p) {
            float m1 = this->mass, m2 = p.getMass();
            float pos1x = this->getPos().x, pos1y = this->getPos().y, pos2x = p.getPos().x, pos2y = p.getPos().y;
            float vel1x = this->getVel().x, vel1y = this->getVel().y, vel2x = p.getVel().x, vel2y = p.getVel().y;
            const float mTot = m1 + m2;

            //palle sovrapposte
            if (overlap(p)) 
            {
                this->setPos(this->pos);
                p.setPos(p.pos);
            }

            const float THETA = atan2(pos2y - pos1y, pos2x - pos1x);
            float v1r = (vel1x * cos(THETA)) + (vel1y * sin(THETA));
            float v2r = (vel2x * cos(THETA)) + (vel2y * sin(THETA));
            float v1t = (-vel1x * sin(THETA)) + (vel1y * cos(THETA));
            float v2t = -vel2x * sin(THETA) + vel2y * cos(THETA);

            sf::Vector2f new1V;
            sf::Vector2f new2V;

            if (!p.getCanMove()) 
            {
                v1r *= -1;
                new1V = prova(v1r, v1t, THETA);
            }else if (!this->getCanMove()) 
            {
                v2r *= -1;
                new2V = prova(v2r, v2t, THETA);
            }else {
                float v1r_old = v1r;
                float v2r_old = v2r;
                v1r = (v1r_old * (m1 - m2) + 2 * m2 * v2r_old) / mTot;
                v2r = (v2r_old * (m2 - m1) + 2 * m1 * v1r_old) / mTot;
                new1V = prova(v1r, v1t, THETA);
                new2V = prova(v2r, v2t, THETA);
            }

            this->setVel(new1V.x * MU, new1V.y * MU);
            p.setVel(new2V.x * MU, new2V.y * MU);
        }

        void stop() 
        {
            this->floating = false;
            this->vel.x = 0;
            this->vel.y = 0;
        }
};
