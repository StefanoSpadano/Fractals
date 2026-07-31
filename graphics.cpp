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

	double center_x = 0.0;
	double center_y = 0.0;
	double zoom = 3.0 / width;

	bool needs_update = false;

	sf::Image image;
	image.create(width, height, sf::Color::Black);
	sf::Texture texture;
	sf::Sprite sprite;




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
						needs_update = true;
					}
					if (event.key.code == sf::Keyboard::Num2) {
						currentState = MANDELBROT;
						std::cout << "Passing to state Mandelbrot. " << std::endl;
						needs_update = true;
					}
					if (event.key.code == sf::Keyboard::Num3) {
						currentState = CUBIC;
						std::cout << "Passing to state Cubic. " << std::endl;
						needs_update = true;
					}
				}
				else {
					if (event.key.code == sf::Keyboard::Escape) {
						currentState = MENU;
						std::cout << "Going to menu. " << std::endl;
						needs_update = true;
						center_x = 0.0;
						center_y = 0.0;
						zoom = 3.0 / width;
					}
				}
			}
		}

		if (needs_update && currentState != MENU) {
			if (currentState == JULIA) {
				compute_julia(image, width, height, center_x, center_y, zoom);
			}
			else if (currentState == MANDELBROT) {
				compute_mandelbrot(image, width, height, center_x, center_y, zoom);
			}
			else if (currentState == CUBIC) {
				compute_cubic_fractal(image, width, height, center_x, center_y, zoom);
			}

			texture.loadFromImage(image);
			sprite.setTexture(texture);


			needs_update = false;
		}

		window.clear();
		if (currentState == MENU) {
			window.draw(menuText);
		} else {
			window.draw(sprite);
		}
		window.display();

	}
}
