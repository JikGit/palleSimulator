#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>

#include "constants.hpp"
#include "palla.cpp"
#include "muro.cpp"


std::vector<sf::Vector2f> getPyramid(int levels, sf::Vector2f space, sf::Vector2f shiftingPoint) {
    std::vector<sf::Vector2f> coordinates;
    coordinates.reserve((levels * (levels + 1)) / 2);

    for (int i = 1; i < levels; i++) 
    {
        for (int x = 0; x <= i; x++) 
        { 
            float posX = (WIDTH - shiftingPoint.x - space.x * i) / 2 + (x * space.x);
            float posY = shiftingPoint.y + space.y * i;
            coordinates.push_back(sf::Vector2f(posX, posY));
        }
    }
    return coordinates;
}

int main()
{ 
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "solarPlanet", sf::Style::Fullscreen);
    window.setFramerateLimit(FRAME_RATE*3);
    sf::Clock deltaClock;

    std::vector < Palla > palle;
    int levels = 10;
    sf::Vector2f space(100, 50), shiftingPoint(0, 100);
    std::vector<sf::Vector2f> coordinates = getPyramid(levels, space, shiftingPoint);
    for (const auto& coord : coordinates)
        palle.push_back(Palla(coord.x, coord.y, 0, 0, 20, 20, sf::Color::Blue, false, false));

    /* test multiple palline */
    /* for (int i = 0; i < 40; i++) */
    /*     palle.push_back(Palla(rand() % WIDTH, rand() % HEIGHT, rand() % 10, rand() % 10, 50, 30, sf::Color::White)); */
    /* int i = 0; */

    /* std::vector < Muro > muri; */
    /* Muro muroX = Muro(0,HEIGHT - 50,WIDTH, 50); */
    /* muri.push_back(muroX); */

    palle.push_back(Palla(WIDTH/2 + rand() % (int)(space.x) - space.x/2, 100, 0, 0, 20, 5, sf::Color::White));

	while (window.isOpen())
	{
        std::cout << palle[0].getPos().x << ", "<< palle[0].getPos().y << std::endl;
        sf::Time dt = deltaClock.restart();
        /* if (i++ == 240) { */
        /*     palle.push_back(Palla(WIDTH/2 + rand() % (int)(space.x) - space.x/2, 100, 0, 0, 20, 5, sf::Color::White)); */
        /*     i = 0; */
        /* } */

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //hitting
        for (int i = 0; i < palle.size()-1; i++) {
            for (int x = i + 1; x < palle.size(); x++) { 
                if (palle[i].isHitting(palle[x].getPos(), palle[x].getRadius())){ 
                    palle[i].hitting(palle[x]);
                    /* palle[i].stop(); */
                    /* palle[x].stop(); */
                }
            }
        }


        //hitting
        /* for (int i = 0; i < muri.size()-1; i++) */
        /*     for (int x = 0; x < palle.size()-1; i++) */
        /*         if (muri[i].isHitting(palle[x])) */
        /*             muri[i].hitting(palle[x]); */
        
        //move
        for (Palla &body : palle)
        {
            body.updatePhysics(dt.asSeconds() * 5);
        }

        //render
        window.clear(sf::Color::Black);
        for (Palla body : palle)
            body.render(window);

        window.display();
    }
};
