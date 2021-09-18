#include "ShaderSystem.h"



ShaderSystem::ShaderSystem()
{
    //m_mvp = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f);
}

ShaderSystem::~ShaderSystem()
{
    for (auto& shader : m_shaders)
        delete shader;
}

void ShaderSystem::setProjectionMatrix(const float& left, const float& right, const float& bottom, const float& top)
{
    for (auto& shader : m_shaders) {
        shader->bind();
        shader->setUniformMat4f("u_MVP", glm::ortho(left, right, bottom, top, -1.0f, 1.0f));
    }
}

Shader* ShaderSystem::loadShader(const std::string& v_path, const std::string& f_path)
{
    m_shaders.emplace_back(new Shader(v_path, f_path));
    return m_shaders[m_shaders.size() - 1];
}

