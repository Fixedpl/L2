#pragma once
#include <vector>



class RenderWindow;
class Animation;


class AnimationSystem
{
public:

	AnimationSystem(RenderWindow* render_window);

	void addAnimation(Animation* animation);

	void animate(const float& frame_time);

private:

	std::vector<Animation*> m_animations;

	RenderWindow* m_render_window;

};

