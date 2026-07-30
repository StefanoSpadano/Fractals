#include "graphics.hpp"
#include "fractals.hpp"
#include <iostream>

void run_application() {

	int width = 800;
	int height = 800;

	sf::RenderWindow window(sf::VideoMode(width, height), "Fractal window");

	sf::Font font;

	if (!font.loadFromFile("font.ttf")) {
		std::cout << "Font not found" << std::endl;
	}

	sf::Text menuText;
	menuText.setFont(font);
	menuText.setString("Fractals' menu\n[1] Julia\n[2] Mandelbrot\n[3] Cubic");
	menuText.setCharacterSize(24);
	menuText.setFillColor(sf::Color::White);

	AppState currentState = MENU;



	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::KeyPressed) {
				if (currentState == MENU) {
					if (event.key.code == sf::Keyboard::Num1) {
						currentState = JULIA;
						std::cout << "Passing to state Julia. " << std::endl;
					}
					if (event.key.code == sf::Keyboard::Num2) {
						currentState = MANDELBROT;
						std::cout << "Passing to state Mandelbrot. " << std::endl;
					}
					if (event.key.code == sf::Keyboard::Num3) {
						currentState = CUBIC;
						std::cout << "Passing to state Cubic. " << std::endl;
					}
				}
			}
		}

		window.clear();
		if (currentState == MENU) {
			window.draw(menuText);
		} else {}
		window.display();

	}
}
