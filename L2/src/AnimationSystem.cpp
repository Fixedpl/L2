#include "AnimationSystem.h"

#include "Animation.h"
#include "RenderWindow.h"
#include "Drawable.h"

AnimationSystem::AnimationSystem(RenderWindow* render_window)
:
m_render_window(render_window)
{
}

void AnimationSystem::addAnimation(Animation* animation)
{
	m_animations.push_back(animation);
}

void AnimationSystem::animate(const float& frame_time)
{
	for (uint32_t i = 0; i < m_animations.size(); ++i) {
		if (!m_animations[i]->hasFinished()) {
			m_animations[i]->animate(frame_time);
			m_render_window->draw(m_animations[i]->getToAnimate());
		} else {
			m_animations.erase(m_animations.begin() + i);
		}
	}
}
