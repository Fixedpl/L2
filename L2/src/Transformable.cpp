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
m_son(nullptr),
m_brother(nullptr),
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
    return glm::vec3(m_position.x, m_position.y, m_position.z);
}

void Transformable::setPosition(const glm::vec3& position)
{
	m_matrix_requires_update = true;
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
	m_matrix_requires_update = true;
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
/*
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
*/
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

/*
glm::mat4 Transformable::getWorldTransform()
{
	float scale = getScale();
	float rotation = getRotation();
	glm::vec3 position = getPosition() - getOrigin();

	Transformable* it = m_parent;
	while (it) {
		scale *= it->getScale();
		rotation += it->getRotation();
		position += it->getPosition() - it->getOrigin();
		it = it->m_parent;
	}

	glm::mat4 world_transform = glm::scale(glm::mat4(1.0f), glm::vec3(scale));
	world_transform = glm::rotate(world_transform, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
	world_transform = glm::translate(world_transform, position);

	return world_transform;
}
*/
const glm::mat4& Transformable::getTransform()
{
	if (m_matrix_requires_update) {
		m_matrix_requires_update = false;
		m_transform = glm::translate(glm::mat4(1.0f), m_position);
		m_transform = glm::rotate(m_transform, glm::radians(m_rotation), glm::vec3(0.0f, 0.0f, 1.0f));
		m_transform = glm::scale(m_transform, glm::vec3(m_scale));
	}

	return m_transform;
}

void Transformable::setTransform(const glm::mat4& transform)
{
	m_transform = transform;
}

void Transformable::addChildTransform(Transformable* transformable)
{
	transformable->m_parent = this;
	if (!m_son) {
		m_son = transformable;
	}
	else {
		Transformable* it = m_son;
		while (it->m_brother) {
			it = it->m_brother;
		}
		it = transformable;
	}
}

Transformable* Transformable::getChildTransforms()
{
	return m_son;
}
/*
Transformable* Transformable::getParent() const
{
	return m_parent;
}

void Transformable::setParent(Transformable* parent)
{
	m_parent = parent;
}
*/


