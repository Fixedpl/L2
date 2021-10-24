#include "RenderWindow.h"

#include <iostream>

RenderWindow::RenderWindow(const uint32_t& windowWidth, const uint32_t& windowHeight, const std::string& windowTitle)
	: Window(windowWidth, windowHeight, windowTitle), m_animation_system(this)
{
	m_shader_system.setProjectionMatrix(0, windowWidth, 0, windowHeight);
}

void RenderWindow::onDraw(const float& frame_time)
{

	/*accumulator += frameTime;
	while (accumulator >= dt)
	{
		accumulator -= dt;
		//onUpdate(frameTime);
	}*/

	//std::cout << 1.0f / frame_time << "\n";

	onEvent(frame_time);

	onUpdate(frame_time);

	m_animation_system.animate(frame_time);

	draw();
}

