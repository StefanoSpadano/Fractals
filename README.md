# Fractal Explorer

A C++ application to generate and interactevely explore fractals using SFML library for the graphic rendering alongside OpenMP to keep performance even at high levels of zooming. 

## Functionalities
* **Interactive menu:** a state machine to navigate through the 3 possibile fractals;
* **Real time exploring:** zoom-in&zoom-out capabilities;
* **Recomputation optimized:** if the picture is static the CPU is at rest, and it activtes only after interaction;
* **Parallel computing:** the picture generation is divided in threads using '#pragma omp parallel for'.  

### Supported fractals
1.Julia's set;
2.Mandelbrot's set;
3.cubic Mandelbrot's set ($Z = Z^# + C$).

## Structure of the project
Code is designed in modules:
* `main.cpp`: the orchestrator;
* `graphics.hpp` / `graphics.cpp`: handling of game loop, user's input and SFML rendering;
* `fractals.hpp`: unified header for math function declaration;
* `julia.cpp`, `mandelbrot.cpp`, `cubic.cpp`: different algorithms implementation. 

## System's requirements
In order to compile and run the project these are needed:
Per compilare e avviare il progetto è necessario avere installato:
* A C++ compiler (es. `g++`);
* The graphic library **SFML** (`libsfml-dev` based on Debian/Ubuntu systems);
* **OpenMP** support. 

## Compile&run
From the terminal navigate to the principal folder of the project and execute: 
```bash
g++ main.cpp graphics.cpp julia.cpp mandelbrot.cpp cubic.cpp -o fractals -O3 -fopenmp -lsfml-graphics -lsfml-window -lsfml-system