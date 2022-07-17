#include "Input.h"

namespace Input {
	bool keyStates[GLFW_KEY_LAST] = { false };
	bool mouseButtonStates[GLFW_MOUSE_BUTTON_LAST] = { false };
	double xoff = 0.0;
	double yoff = 0.0;

	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		xoff = xoffset;
		yoff = yoffset;
	}

	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (key >= 0 && key < GLFW_KEY_LAST) {
			if (action == GLFW_PRESS) {
				keyStates[key] = true;
			}
			else if (action == GLFW_RELEASE) {
				keyStates[key] = false;
			}
		}
	}

	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
	{
		if (button >= 0 && button < GLFW_MOUSE_BUTTON_LAST) {
			if (action == GLFW_PRESS) {
				mouseButtonStates[button] = true;
			}
			else if (action == GLFW_RELEASE) {
				mouseButtonStates[button] = false;
			}
		}
	}

	bool isKeyPressed(int key)
	{
		if (key < 0 || key >= GLFW_KEY_LAST)
			return false;
		return keyStates[key];
	}

	bool isMouseButtonPressed(int button)
	{
		if (button < 0 || button >= GLFW_MOUSE_BUTTON_LAST)
			return false;
		return mouseButtonStates[button];
	}
}


