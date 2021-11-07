#pragma once
#include <vector>

#include "Window.h"
#include "Renderer.h"
#include "AnimationSystem.h"

class ClickablePinch;


class RenderWindow : public Window, public Renderer
{
public:

	RenderWindow(const uint32_t& windowWidth, const uint32_t& windowHeight, const std::string& windowTitle);

	void draw(Drawable* drawable);

protected:

	virtual void onEvent(const float& frame_time) {};
	virtual void onUpdate(const float& frame_time) {};

	void pushAnimation(Animation* animation);

	void addClickable(ClickablePinch* clickable);
	void releaseClickable(ClickablePinch* clickable);

	void setLineWidth(const float& width);

private:

	void _onEvent(const float& frame_time);

	void onDraw(const float& frame_time);

	void checkClickables();

private:

	AnimationSystem m_animation_system;

	std::vector<ClickablePinch*> m_clickables;

	//	static constexpr float m_dt = 1.0f / 144.0f;
	//	float accumulator = 0.0f;

};

