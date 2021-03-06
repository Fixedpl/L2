#include "Animation.h"

#include "Drawable.h"
#include "Animation.h"



Animation::Animation(DrawableTransformable* to_animate, const glm::vec2& dest, const float& duration_time)
:
m_current_time(0.0f), 
m_duration_time(duration_time),
m_dest(dest),
m_is_over(false),
m_is_stopped(false)
{
	m_to_animate = to_animate;
}

Animation::~Animation()
{
	delete m_to_animate;
}

void Animation::start()
{
	m_is_stopped = false;
}

void Animation::stop()
{
	m_is_stopped = true;
}

bool Animation::hasFinished() const
{
	return m_is_over;
}

DrawableTransformable* Animation::getToAnimate()
{
	return m_to_animate;
}

LineTrajectory::LineTrajectory(DrawableTransformable* to_animate, const glm::vec2& dest, const float& duration_time)
:
Animation(to_animate, dest, duration_time)
{
}

bool LineTrajectory::animate(const float& time_passed)
{
	if (m_is_stopped) {
		return false;
	}
	float move_portion = time_passed / (m_duration_time - m_current_time);
	m_current_time += time_passed;

	glm::vec3 shape_pos(m_to_animate->getPosition());

	if (m_current_time >= m_duration_time) {
		m_is_over = true;
		m_to_animate->setPosition(glm::vec3(m_dest, shape_pos.z));
		return false;
	}

	float whole_dist_x = m_dest.x - shape_pos.x;
	float whole_dist_y = m_dest.y - shape_pos.y;

	m_to_animate->setPosition(glm::vec3(move_portion * whole_dist_x + shape_pos.x, move_portion * whole_dist_y + shape_pos.y, shape_pos.z));

	return true;
}

BezierTrajectory::BezierTrajectory(DrawableTransformable* to_animate, const glm::vec2& dest, const float& duration_time, const glm::vec2& control_point)
:
Animation(to_animate, dest, duration_time), 
m_control_point(control_point), 
m_traveler(control_point)
{
}

bool BezierTrajectory::animate(const float& time_passed)
{
	if (m_is_stopped) {
		return false;
	}
	float move_portion = time_passed / (m_duration_time - m_current_time);
	m_current_time += time_passed;

	glm::vec3 shape_pos(m_to_animate->getPosition());

	if (m_current_time >= m_duration_time) {
		m_is_over = true;
		m_to_animate->setPosition(glm::vec3(m_dest, shape_pos.z));
		return false;
	}

	float traveler_whole_dist_x = m_dest.x - m_traveler.x;
	float traveler_whole_dist_y = m_dest.y - m_traveler.y;

	m_traveler.x += move_portion * traveler_whole_dist_x;
	m_traveler.y += move_portion * traveler_whole_dist_y;

	float whole_dist_x = m_traveler.x - shape_pos.x;
	float whole_dist_y = m_traveler.y - shape_pos.y;

	m_to_animate->setPosition(glm::vec3(move_portion * whole_dist_x + shape_pos.x, move_portion * whole_dist_y + shape_pos.y, shape_pos.z));

	return true;
}
