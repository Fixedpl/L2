#pragma once
#include <vector>

#include "Window.h"
#include "Renderer.h"
#include "AnimationSystem.h"
#include "dllexport.h"

class ClickablePinch;


class LE_API RenderWindow : public Window, public Renderer
{
public:

	RenderWindow(const uint32_t& windowWidth, const uint32_t& windowHeight, const std::string& windowTitle);

protected:

	virtual void onEvent(const float& frame_time) {};
	virtual void onUpdate(const float& frame_time) {};

	void pushAnimation(Animation* animation);

	void addClickable(ClickablePinch* clickable);
	void releaseClickable(ClickablePinch* clickable);

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

