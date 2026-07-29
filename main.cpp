#include <iostream>
#include <complex>
#include <SFML/Graphics.hpp>

void compute_fractal(sf::Image& image, int width, int height, double center_x, double center_y, double zoom) {

	std::complex<double> complex_number_seed(-0.75, 0.1);
    int iter_max = 256;

    #pragma omp parallel for

	for (int y = 0; y < height; y++) {
		for (int x=0; x<width; x++) {
			double z_real = center_x + (x - width / 2.0) * zoom;
            double z_imag = center_y + (y - height / 2.0) * zoom;

            std::complex<double> z(z_real, z_imag);
            int iter = 0;

            while (std::abs(z) < 2 && iter < iter_max) {
            	z = z*z + complex_number_seed;
            	iter++;
            }

            if (iter < iter_max) {
				int color_index = iter % 50;
				int red;
				int green;
				int blue;

				if (color_index < 25) {
					red = (color_index * 255) / 25;           
                    blue = (color_index * 255) / 25;
                    green = 255 - ((color_index * 255) / 25);
				} else {
					int step = color_index - 25;

					red = 255 - ((step * 127) / 25);
					green = 0;
					blue = 255;
				}

				sf::Color pixelColor(red, green, blue);
				image.setPixel(x, y, pixelColor);
			}
			else {
                image.setPixel(x, y, sf::Color::Black);
		}
	}
}

}

int main() {
	int width = 800;
	int height = 800;
	sf::Image image;
	image.create(width, height, sf::Color::Black);
	std::cout << "Fractals being generated..." << std::endl;

	double center_x = 0.0;
	double center_y = 0.0;
	double zoom = 3.0 / width;

	compute_fractal(image, width, height, center_x, center_y, zoom);

	if (image.saveToFile("Julia_fractal.png")) {
		std::cout << "Image successfully saved to file. " << std::endl;
	}
	else {
		std::cout << "An error occurred while saving the file. " << std::endl;
	}

	sf::Texture texture;
	texture.loadFromImage(image);
	sf::Sprite sprite(texture);

	sf::RenderWindow window(sf::VideoMode(width, height), "A Julia fractal in C++. ");

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			if (event.type == sf::Event::MouseButtonPressed) {

                int mouse_x = event.mouseButton.x;
                int mouse_y = event.mouseButton.y;

				if (event.mouseButton.button == sf::Mouse::Left) {
					std::cout << "Zooming in..." << std::endl;

					center_x = center_x + (mouse_x - width / 2.0) * zoom;
                    center_y = center_y + (mouse_y - height / 2.0) * zoom;

                    zoom = zoom / 2.0;
				}
                else if (event.mouseButton.button == sf::Mouse::Right) {
                    std::cout << "Zooming out..." << std::endl;
                    
                    center_x = center_x + (mouse_x - width / 2.0) * zoom;
                    center_y = center_y + (mouse_y - height / 2.0) * zoom;
                    zoom = zoom * 2.0; 
                }

                compute_fractal(image, width, height, center_x, center_y, zoom);

                texture.loadFromImage(image);
                }
		}
		window.clear();
		window.draw(sprite);
		window.display();
	}
	return 0;
}