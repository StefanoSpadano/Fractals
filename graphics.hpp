#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include <SFML/Graphics.hpp>

enum AppState {
	MENU,
	JULIA,
	MANDELBROT,
	CUBIC
};

void run_application();

#endif

