#include "RenderWindow.h"

#include <iostream>

#include "Clickable.h"

RenderWindow::RenderWindow(const uint32_t& windowWidth, const uint32_t& windowHeight, const std::string& windowTitle)
	: Window(windowWidth, windowHeight, windowTitle), m_animation_system(this)
{
	m_shader_system.setProjectionMatrix(0, windowWidth, 0, windowHeight);
}

void RenderWindow::_onEvent(const float& frame_time)
{
	checkClickables();

	onEvent(frame_time);
}

void RenderWindow::onDraw(const float& frame_time)
{

	/*accumulator += frameTime;
	while (accumulator >= dt)
	{
		accumulator -= dt;
		//onUpdate(frameTime);
	}*/

	std::cout << 1.0f / frame_time << "\n";

	_onEvent(frame_time);

	onUpdate(frame_time);

	m_animation_system.animate(frame_time);

	draw();
}

void RenderWindow::checkClickables()
{
	if (isLeftMousePressed()) {
		glm::vec2 mouse_pos = getLastMousePosition();
		//std::cout << "CHECKING COORDINATES: " << mouse_pos.x << ":" << mouse_pos.y << "FOR " << m_clickables.size() << "ELEMENTS\n";
		for (auto& clickable : m_clickables) {
			if (clickable->perforates(mouse_pos)) {
				clickable->onClick();
			}
		}
	}
}

void RenderWindow::pushAnimation(Animation* animation)
{
	m_animation_system.addAnimation(animation);
}

void RenderWindow::addClickable(ClickablePinch* clickable)
{
	m_clickables.push_back(clickable);
}

void RenderWindow::releaseClickable(ClickablePinch* clickable)
{
	std::vector<ClickablePinch*>::iterator it = std::find(m_clickables.begin(), m_clickables.end(), clickable);
	if (it != m_clickables.end()) {
		m_clickables.erase(it);
	}
	else {
		std::cout << "[ERROR] Couldn't erase clickable because it wasn't found\n";
	}

}