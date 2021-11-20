#include "Primitive.h"

RectangleBase::RectangleBase(const float& width, const float& height)
:
m_width(width), 
m_height(height)
{
}


float RectangleBase::getWidth() const
{
	return m_width;
}

void RectangleBase::setWidth(const float& width)
{
	m_width = width;
}

float RectangleBase::getHeight() const
{
	return m_height;
}

void RectangleBase::setHeight(const float& height)
{
	m_height = height;
}

bool RectangleBase::perforates(const glm::vec2& point)
{

	glm::mat4 inverse_transform = glm::affineInverse(getWorldTransform());

	glm::vec4 point_transform = inverse_transform * glm::vec4(point.x, point.y, m_position.z, 1.0f);


	if (point_transform.x >= -m_origin.x && point_transform.x <= -m_origin.x + m_width
		&& point_transform.y >= -m_origin.y && point_transform.y <= m_height - m_origin.y) {
		return true;
	}
	return false;
}

CircleBase::CircleBase(const float& radius)
:
m_radius(radius)
{
}


float CircleBase::getRadius() const
{
	return m_radius;
}

void CircleBase::setRadius(const float& radius)
{
	m_radius = radius;
}

bool CircleBase::perforates(const glm::vec2& point)
{
	glm::mat4 inverse_transform = glm::affineInverse(getWorldTransform());

	glm::vec4 point_transform = inverse_transform * glm::vec4(point.x, point.y, m_position.z, 1.0f) - glm::vec4(-m_origin.x, -m_origin.y, 0.0f, 0.0f);

	float distance = (point_transform.x - m_radius) * (point_transform.x - m_radius)
		+ (point_transform.y - m_radius) * (point_transform.y - m_radius);
	if (distance <= m_radius * m_radius) {
		return true;
	}
	return false;
}

LineBase::LineBase(const glm::vec3& start, const glm::vec3& finish)
:
m_start(start),
m_finish(finish)
{
}


glm::vec3 LineBase::getLineStart() const
{
	return m_start;
}

void LineBase::setLineStart(const glm::vec3& start)
{
	m_start = start;
}

glm::vec3 LineBase::getLineFinish() const
{
	return m_finish;
}

void LineBase::setLineFinish(const glm::vec3& finish)
{
	m_finish = finish;
}

bool LineBase::perforates(const glm::vec2& point)
{
	// WRONG BECAUSE ITS CHECKING INFINITE LINE
	glm::mat4 inverse_transform = glm::affineInverse(getWorldTransform());

	glm::vec4 point_transform = inverse_transform * glm::vec4(point.x, point.y, m_start.z, 1.0f);

	float a = (m_finish.y - m_start.y) / (m_finish.x - m_start.x);

	float y = a * point_transform.x;
	if (y == point_transform.y) {
		return true;
	}
	return false;
}

PointBase::PointBase(const glm::vec3& point)
{
}

bool PointBase::perforates(const glm::vec2& point)
{
	glm::mat4 inverse_transform = glm::affineInverse(getWorldTransform());

	glm::vec4 point_transform = inverse_transform * glm::vec4(point.x, point.y, m_position.z, 1.0f);

	if (m_position.x == point_transform.x && m_position.y == point_transform.y) return true;
	return false;
}
