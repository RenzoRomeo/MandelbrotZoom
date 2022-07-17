#include "Mandelbrot.h"

int main() {
	Mandelbrot& mandelbrot = Mandelbrot::get(1280, 720);
	mandelbrot.run();
	
	return 0;
}