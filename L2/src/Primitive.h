#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "Transformable.h"

class Pinch
{
public:

	virtual bool perforates(const glm::vec2& point) = 0;

};

class Colorable
{
public:

	Colorable(const glm::vec4& color) : m_color(color) {}

	glm::vec4 getColor() const;
	void setColor(const glm::vec4& color);

protected:

	glm::vec4 m_color;

};

class RectangleBase : public Pinch, public Transformable, public Colorable
{
public:

	RectangleBase(const glm::vec3& pos, const float& width, const float& height, const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	bool perforates(const glm::vec2& point) {
		// Because its hard to check if point perforates transformed figure
		// im transforming point by inverse transform and then checking on 
		// untransformed figure
		glm::mat4 inverse_transform = glm::affineInverse(getTransform());

		glm::vec3 pos = getPosition();

		glm::vec4 point_transform = inverse_transform * glm::vec4(point.x, point.y, pos.z, 1.0f);

		if (point_transform.x >= 0.0f && point_transform.x <= m_width
			&& point_transform.y >= 0.0f && point_transform.y <= m_height) {
			return true;
		}
		return false;
	}

	float getWidth() const;
	void setWidth(const float& width);

	float getHeight() const;
	void setHeight(const float& height);

protected:

	float m_width, m_height;

};

class CircleBase : public Pinch, public Transformable, public Colorable
{
public:

	CircleBase(const glm::vec3& pos, const float& radius, const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	bool perforates(const glm::vec2& point) {
		glm::mat4 inverse_transform = glm::affineInverse(getTransform());

		glm::vec3 pos = getPosition();

		glm::vec4 point_transform = inverse_transform * glm::vec4(point.x, point.y, pos.z, 1.0f);

		float distance = (point_transform.x - m_radius) * (point_transform.x - m_radius)
						+ (point_transform.y - m_radius) * (point_transform.y - m_radius);
		if (distance <= m_radius * m_radius) {
			return true;
		}
		return false;
	}

	float getRadius() const;
	void setRadius(const float& radius);

protected:

	float m_radius;

};

class LineBase : public Pinch, public Transformable, public Colorable
{
public:

	LineBase(const glm::vec3& start, const glm::vec3& finish, const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	bool perforates(const glm::vec2& point) {
		glm::mat4 inverse_transform = glm::affineInverse(getTransform());

		glm::vec4 point_transform = inverse_transform * glm::vec4(point.x, point.y, m_start.z, 1.0f);


		float a = (m_finish.y - m_start.y) / (m_finish.x - m_start.x);

		float y = a * point_transform.x;
		if (y == point_transform.y) {
			return true;
		}
		return false;
	}

	glm::vec3 getLineStart() const;
	void setLineStart(const glm::vec3& start);

	glm::vec3 getLineFinish() const;
	void setLineFinish(const glm::vec3& finish);

protected:

	glm::vec3 m_start, m_finish;

};


class PointBase : public Pinch, public Transformable, public Colorable
{
public:

	PointBase(const glm::vec3& pos, const glm::vec4& color = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));

	bool perforates(const glm::vec2& point) {
		glm::mat4 inverse_transform = glm::affineInverse(getTransform());

		glm::vec3 pos = getPosition();

		glm::vec4 point_transform = inverse_transform * glm::vec4(point.x, point.y, pos.z, 1.0f);

		if(pos.x == point_transform.x && pos.y == point_transform.y) return true;
		return false;
	}
};
