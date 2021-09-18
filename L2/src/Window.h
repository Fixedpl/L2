#pragma once
#include <iostream>
#include <array>
#include <glm/glm.hpp>

#include "KeyCodes.h"



class GLFWwindow;

class Window
{
public:

	Window(const uint32_t& windowWidth, const uint32_t& windowHeight, const std::string& windowTitle);

	unsigned int getWidth() const;
	unsigned int getHeight() const;

	void setVSync(const bool& value);

	static bool isKeyPressed(const unsigned int& key);

	static bool isLeftMousePressed();
	static bool isRightMousePressed();
	static glm::vec2 getLastMousePosition();

	void display();

protected:

	void windowInit();

	virtual void onDraw(const float& frame_time) {}

private:

	void windowLoop();

	static void keyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	static void mouseCallback(GLFWwindow* window, int button, int action, int mods);

private:

	GLFWwindow* window;
	uint32_t m_WindowWidth;
	uint32_t m_WindowHeight;
	std::string m_WindowTitle;
	bool m_VSync;

	static std::array<bool, 350> m_Keys;

	static bool m_leftClick;
	static bool m_rightClick;

	static double m_lastCursorX;
	static double m_lastCursorY;

};

