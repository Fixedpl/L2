#pragma once
#include <string>
#include <cstdint>

#include <glm/glm.hpp>

class Shader
{
public:

	Shader();
	Shader(const std::string& vsPath, const std::string& fsPath);
	~Shader();

	void setUniformMat4f(const std::string& name, const glm::mat4& matrix);
	void setUniform1i(const std::string& name, const int32_t& value);

	void bind() const;

	void loadShader(const std::string& vsPath, const std::string& fsPath);

private:

	uint32_t createShader(const std::string& path, const int32_t& type);

	int32_t getUniformLocation(const std::string& name);

private:

	uint32_t m_id;

};

