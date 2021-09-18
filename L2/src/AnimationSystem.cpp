#include "AnimationSystem.h"

#include "RenderWindow.h"


void AnimationSystem::animate(const float& frame_time)
{
	for (uint32_t i = 0; i < m_animations.size(); ++i) {
		if (!m_animations[i]->hasFinished()) {
			m_animations[i]->animate(frame_time);
			m_render_window->draw(m_animations[i]->getShape());
		} else {
			delete m_animations[i];
			m_animations.erase(m_animations.begin() + i);
		}
	}
}
