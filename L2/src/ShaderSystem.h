#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"


class ShaderSystem
{
public:

	ShaderSystem();
	~ShaderSystem();

	void add(Shader* shader);

	void setProjectionMatrix(const float& left, const float& right, const float& bottom, const float& top);

	Shader* loadShader(const std::string& v_path, const std::string& f_path);

private:

	std::vector<Shader*> m_shaders;

};

