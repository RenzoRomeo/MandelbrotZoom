#pragma once

struct GLFWwindow;

class Mandelbrot {
public:
	static Mandelbrot& get(int width, int height);
	void run();

private:
	Mandelbrot(int width, int height);

private:
	GLFWwindow* m_Window;
	int m_Width, m_Height;
};