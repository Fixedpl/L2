#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Primitive.h"
#include "Texture.h"
#include "AnimationSystem.h"
#include "Text.h"

class RenderWindow : public Window, public Renderer
{
public:

	RenderWindow(const uint32_t& windowWidth, const uint32_t& windowHeight, const std::string& windowTitle);

protected:

	virtual void onUpdate(const float& frame_time) {};

	void onDraw(const float& frame_time);

	void pushAnimation(Animation* animation) { m_animation_system.addAnimation(animation); }
		 
private:

	AnimationSystem m_animation_system;

	//	static constexpr float m_dt = 1.0f / 144.0f;
	//	float accumulator = 0.0f;

};

