#include "fractals.hpp"
#include <complex>

void compute_julia(sf::Image& image, int width, int height, double center_x, double center_y, double zoom) {

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
