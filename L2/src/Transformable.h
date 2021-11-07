#pragma once
#include <glm/glm.hpp>




class Transformable
{
public:

	Transformable();

	void addToOrigin(const glm::vec3& to_add);
	glm::vec3 getOrigin() const;
	void setOrigin(const glm::vec3& origin);

	glm::vec3 getPosition() const;
	virtual void setPosition(const glm::vec3& position);

	float getRotation() const;
	void setRotation(const float& degrees);

	float getScale() const;
	void setScale(const float& percent);

	void move(const glm::vec3& amount);

	void rotate(const float& degrees);

	void scale(const float& percent);

	//glm::vec3 getWorldOrigin();
	glm::mat4 getWorldTransform();
	const glm::mat4& getTransform();
	void setTransform(const glm::mat4& transform);

	void addChildTransform(Transformable* transformable);
	Transformable* getChildTransforms();

protected:
	
	Transformable* m_parent;

	Transformable* m_son;

	Transformable* m_brother;

	bool m_matrix_requires_update;

	glm::vec3 m_position;

	glm::vec3 m_origin;

	glm::mat4 m_transform;

	float m_scale;

	float m_rotation;

};

