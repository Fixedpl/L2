#pragma once

#include <glm/glm.hpp>

#include "dllexport.h"



class DrawableTransformable;


class LE_API Animation
{
public:

	Animation(DrawableTransformable* to_animate, const glm::vec2& dest, const float& duration_time);
	~Animation();


	virtual bool animate(const float& time_passed) = 0;

	void start(); 
	void stop();

	bool hasFinished() const;

	DrawableTransformable* getToAnimate();

protected:

	DrawableTransformable* m_to_animate;

	glm::vec2 m_dest;

	float m_current_time;
	float m_duration_time;

	bool m_is_stopped;
	bool m_is_over;

};

class LE_API LineTrajectory : public Animation
{
public:

	LineTrajectory(DrawableTransformable* to_animate, const glm::vec2& dest, const float& duration_time);

	bool animate(const float& time_passed);

};

class LE_API BezierTrajectory : public Animation
{
public:

	BezierTrajectory(DrawableTransformable* to_animate, const glm::vec2& dest, const float& duration_time, const glm::vec2& control_point);

	bool animate(const float& time_passed);

private:

	glm::vec2 m_control_point;
	glm::vec2 m_traveler;

};