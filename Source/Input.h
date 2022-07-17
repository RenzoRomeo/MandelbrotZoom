#pragma once

#include "GLFW/glfw3.h"

namespace Input {
	extern double xoff;
	extern double yoff;
	extern bool keyStates[GLFW_KEY_LAST];
	extern bool mouseButtonStates[GLFW_MOUSE_BUTTON_LAST];

	void scrollCallback(GLFWwindow* window, double xoffset, double yoffset);
	void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

	bool isKeyPressed(int key);
	bool isMouseButtonPressed(int button);
}