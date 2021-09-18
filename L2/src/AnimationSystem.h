#pragma once
#include <vector>

#include "Animation.h"


class RenderWindow;

class AnimationSystem
{
public:

	AnimationSystem(RenderWindow* render_window) : m_render_window(render_window) {}

	void addAnimation(Animation* animation) { m_animations.push_back(animation); }

	void animate(const float& frame_time);

private:

	std::vector<Animation*> m_animations;

	RenderWindow* m_render_window;

};

