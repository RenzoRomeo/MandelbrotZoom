#pragma once

struct GLFWwindow;

class Mandelbrot {
public:
	static Mandelbrot& get(int width, int height);
	void run();

private:
	Mandelbrot(int width, int height);
	void userInput();

private:
	GLFWwindow* m_Window;
	int m_Width, m_Height;

	double m_ZoomX = 0.0;
	double m_ZoomY = 0.0;
	double m_ZoomXAmp = 1.6;
	double m_ZoomYAmp = 0.9;
	double m_ZoomSpeed = 0.2;

	double m_dt = -1.0;

	bool m_HasToRender = true;

	const double m_MoveSpeed = 0.5;
};