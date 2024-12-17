#include "Cursor.hpp"
#include "Window.hpp"

#include <GLFW/glfw3.h>

void cursor::setCursorMode(int mode)
{
	glfwSetInputMode(Window::window, GLFW_CURSOR, mode);
}

void cursor::showCursor(bool flag)
{
	if (flag) setCursorMode(GLFW_CURSOR_HIDDEN);
	else setCursorMode(GLFW_CURSOR_NORMAL);
}

void cursor::disableCursor(bool flag)
{
	if (flag) setCursorMode(GLFW_CURSOR_DISABLED);
	else setCursorMode(GLFW_CURSOR_NORMAL);
}

void cursor::setPosition(double x, double y)
{
	glfwSetCursorPos(Window::window, x, y);
}