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

	glm::vec3 pos = getPosition();
	
	glm::vec3 origin = getWorldOrigin();

	glm::vec4 point_transform = inverse_transform * glm::vec4(point.x - origin.x, point.y - origin.y, pos.z, 1.0f) + glm::vec4(origin, 0.0f);


	if (point_transform.x >= 0.0f && point_transform.x <= m_width
		&& point_transform.y >= 0.0f && point_transform.y <= m_height) {
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

	glm::vec3 pos = getPosition();

	glm::vec3 origin = getWorldOrigin();

	glm::vec4 point_transform = inverse_transform * glm::vec4(point.x - origin.x, point.y - origin.y, pos.z, 1.0f) + glm::vec4(origin, 0.0f);

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
	glm::mat4 inverse_transform = glm::affineInverse(getWorldTransform());

	glm::vec3 origin = getWorldOrigin();

	glm::vec4 point_transform = inverse_transform * glm::vec4(point.x - origin.x, point.y - origin.y, m_start.z, 1.0f) + glm::vec4(origin, 0.0f);



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

	glm::vec3 pos = getPosition();

	glm::vec3 origin = getWorldOrigin();

	glm::vec4 point_transform = inverse_transform * glm::vec4(point.x - origin.x, point.y - origin.y, pos.z, 1.0f) + glm::vec4(origin, 0.0f);

	if (pos.x == point_transform.x && pos.y == point_transform.y) return true;
	return false;
}

Colorable::Colorable(const glm::vec4& color)
:
	m_color(color)
{
}

glm::vec4 Colorable::getColor() const
{
	return m_color;
}

void Colorable::setColor(const glm::vec4& color)
{
	m_color = color;
}
