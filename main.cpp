#include <SFML/Graphics.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>
#include <vector>

#include "constants.hpp"
#include "palla.cpp"



int main()
{ 
	sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "solarPlanet", sf::Style::Fullscreen);
    window.setFramerateLimit(FRAME_RATE);

    std::vector < Palla > palle;
    for (int i = 0; i < 30; i++) {
        palle.push_back(Palla(rand() % WIDTH, rand() % HEIGHT, 10, rand() % 10, rand() % 10, 30, sf::Color(rand() % 255, rand() % 255, rand() % 255)));
    }

    /* Palla palla = Palla(205, 200, 0, 0, 20, 30, sf::Color::Red); */
    /* Palla palla2 = Palla(203, 400, 0, 0, 20, 30, sf::Color::Red); */
    /* Palla palla3 = Palla(305, 300, 0, 0, 20, 30, sf::Color::Red, false); */
    /* Palla palla4 = Palla(405, 300, 0, 0, 20, 30, sf::Color::Red, false); */
    /* palle.push_back(palla); */
    /* palle.push_back(palla2); */
    /* palle.push_back(palla3); */
    /* palle.push_back(palla4); */

	while (window.isOpen())
	{
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //hitting
        for (int i = 0; i < palle.size()-1; i++)
            for (int x = i + 1; x < palle.size(); x++)
                if (palle[i].isHitting(palle[x].getPos(), palle[x].getRadius()))
                    palle[i].hitting(palle[x]);
        
        //move
        for (Palla &body : palle)
        {
            body.update_vel();
        }

        //render
        window.clear(sf::Color::Black);
        for (Palla body : palle)
            body.render(window);

        window.display();
    }
}
