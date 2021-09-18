#pragma once

#include <glm/glm.hpp>



class Shape;

class Animation
{
public:

	Animation(Shape* to_animate, const glm::vec2& dest, const float& duration_time);

	virtual bool animate(const float& time_passed) = 0;

	void start() { m_is_stopped = false; }
	void stop() { m_is_stopped = true; }

	bool hasFinished() const { return m_is_over; }

	Shape* getShape() { return m_to_animate; }

protected:

	Shape* m_to_animate;

	glm::vec2 m_dest;

	float m_current_time;
	float m_duration_time;

	bool m_is_stopped;
	bool m_is_over;

};

class LineTrajectory : public Animation
{
public:

	LineTrajectory(Shape* to_animate, const glm::vec2& dest, const float& duration_time)
	: Animation(to_animate, dest, duration_time) {}

	bool animate(const float& time_passed);

};

class BezierTrajectory : public Animation
{
public:

	BezierTrajectory(Shape* to_animate, const glm::vec2& dest, const float& duration_time, const glm::vec2& control_point)
		: Animation(to_animate, dest, duration_time), m_control_point(control_point), m_traveler(control_point) {}

	bool animate(const float& time_passed);

private:

	glm::vec2 m_control_point;
	glm::vec2 m_traveler;

};