#include "Transformable.h"

#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

Transformable::Transformable()
: 
m_transform(1.0f), 
m_scale(1.0f), 
m_rotation(0.0f), 
m_origin(0.0f), 
m_position(0.0f),
m_matrix_requires_update(true),
m_parent(nullptr)
{
}

Transformable::Transformable(const glm::vec3& position, const glm::vec3& origin)
:
m_transform(1.0f),
m_scale(1.0f),
m_rotation(0.0f),
m_origin(origin),
m_position(0.0f),
m_matrix_requires_update(true),
m_parent(nullptr)
{
}

void Transformable::addToOrigin(const glm::vec3& to_add)
{
	m_origin += to_add;
}

glm::vec3 Transformable::getOrigin() const
{
	return m_origin;
}

void Transformable::setOrigin(const glm::vec3& origin)
{
	m_origin = origin;
}

glm::vec3 Transformable::getPosition() const
{
    return glm::vec3(m_position.x + m_origin.x, 
					 m_position.y + m_origin.y, 
					 m_position.z + m_origin.z);
}

void Transformable::setPosition(const glm::vec3& position)
{
	m_position = position;
}

float Transformable::getRotation() const
{
	return m_rotation;
}

void Transformable::setRotation(const float& degrees)
{
	m_matrix_requires_update = true;
	m_rotation = degrees;
}

float Transformable::getScale() const
{
	return m_scale;
}

void Transformable::setScale(const float& percent)
{
	m_matrix_requires_update = true;
	m_scale = percent;
}

void Transformable::move(const glm::vec3& amount)
{
	m_position += amount;
}

void Transformable::rotate(const float& degrees)
{
	m_matrix_requires_update = true;
	m_rotation += degrees;
}

void Transformable::scale(const float& percent)
{
	m_matrix_requires_update = true;
	m_scale *= percent;
}

glm::vec3 Transformable::getWorldOrigin()
{
	glm::vec3 world_origin = getOrigin();
	Transformable* it = m_parent;
	while (it) {
		world_origin = it->getOrigin() + world_origin;
		it = it->m_parent;
	}
	return world_origin;
}

glm::mat4 Transformable::getWorldTransform()
{
	glm::mat4 world_transform = getTransform();
	Transformable* it = m_parent;
	while (it) {
		world_transform = it->getTransform() * world_transform;
		it = it->m_parent;
	}
	return world_transform;
}

const glm::mat4& Transformable::getTransform()
{
	if (m_matrix_requires_update) {
		m_matrix_requires_update = false;
		m_transform = glm::scale(glm::mat4(1.0f), glm::vec3(m_scale));
		m_transform = glm::rotate(m_transform, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	}
	m_transform[3][0] = m_position.x - m_origin.x;
	m_transform[3][1] = m_position.y - m_origin.y;
	m_transform[3][2] = m_position.z - m_origin.z;

	return m_transform;
}

void Transformable::setTransform(const glm::mat4& transform)
{
	m_transform = transform;
}

Transformable* Transformable::getParent() const
{
	return m_parent;
}

void Transformable::setParent(Transformable* parent)
{
	m_parent = parent;
}



