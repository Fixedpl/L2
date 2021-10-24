#include "Texture.h"

#include <iostream>
#include <cmath>
#include <algorithm>
#include <vector>

#include <stb_image/stb_image.h>

#include "gl.h"




Texture::Texture()
	:
	m_width(0),
	m_height(0),
	m_BPP(0)
{
	glGenTextures(1, &m_id);
}

Texture::Texture(const uint32_t& texture_slot)
	:
	TextureSource(texture_slot),
	m_width(0),
	m_height(0),
	m_BPP(0)
{
	glGenTextures(1, &m_id);
}

Texture::Texture(const uint32_t& texture_slot, const std::string& path)
	:
	TextureSource(texture_slot),
	m_width(0),
	m_height(0),
	m_BPP(0)
{
	glGenTextures(1, &m_id);
	loadTexture(path);
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_id);
}

void Texture::bind() const
{
	glBindTexture(GL_TEXTURE_2D, m_id);
}

void Texture::activateSlot(const uint32_t& texture_slot)
{
	glActiveTexture(GL_TEXTURE0 + texture_slot);
}

void Texture::loadTexture(const std::string& path)
{
	stbi_set_flip_vertically_on_load(1);
	unsigned char* data = stbi_load(path.c_str(), &m_width, &m_height, &m_BPP, 4);
	activateSlot(m_texture_slot);
	bind();

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		//glGenerateMipmap(GL_TEXTURE_2D);
	} else {
		std::cout << "[ERROR] Texture.cpp: Couldn't load texture because texture file was not found\n";
	}
	stbi_image_free(data);
}



TexturePart::TexturePart(Texture* source, const TexCoords& tex_coords_rel)
	: 
	TextureSource(source->getTextureSlot()),
	m_source_texture(source)
{
	setTextureCoords(tex_coords_rel);
}

TexturePart::TexturePart(Texture* source, const glm::vec2& top_left_rel, const glm::vec2& bot_right_rel)
	:
	TextureSource(source->getTextureSlot()),
	m_source_texture(source)
{
	setTextureCoords(TexCoords(top_left_rel, bot_right_rel));
}

void TexturePart::setSource(Texture* source)
{
	m_source_texture = source;
	m_texture_slot = source->getTextureSlot();
}

TexCoords TexturePart::setTextureCoords(const TexCoords& tex_coords_rel)
{
	if (!m_source_texture) {
		std::cout << "[ERROR] Texture.cpp: Couldn't set texture coords because texture is undefined\n";
	}
	int32_t texture_width = m_source_texture->getWidth();
	int32_t texture_height = m_source_texture->getHeight();

	m_tex_coords.top_left =  glm::vec2(tex_coords_rel.top_left.x / texture_width, tex_coords_rel.top_left.y / texture_height);
	m_tex_coords.bot_left =  glm::vec2(tex_coords_rel.bot_left.x / texture_width, tex_coords_rel.bot_left.y / texture_height);
	m_tex_coords.bot_right = glm::vec2(tex_coords_rel.bot_right.x / texture_width, tex_coords_rel.bot_right.y / texture_height);
	m_tex_coords.top_right = glm::vec2(tex_coords_rel.top_right.x / texture_width, tex_coords_rel.top_right.y / texture_height);

	m_width = tex_coords_rel.top_right.x - tex_coords_rel.top_left.x;
	m_height = tex_coords_rel.top_right.y - tex_coords_rel.bot_left.y;

	return m_tex_coords;
}

TexCoords TexturePart::setTextureCoords(const glm::vec2& top_left_rel, const glm::vec2& bot_right_rel)
{
	return setTextureCoords(TexCoords(top_left_rel, bot_right_rel));
}

TexCoords TexturePart::setTextureCoords(const glm::vec2& top_left_rel, const glm::vec2& bot_left_rel, const glm::vec2& bot_right_rel, const glm::vec2& top_right_rel)
{
	return setTextureCoords(TexCoords(top_left_rel, bot_left_rel, bot_right_rel, top_right_rel));
}

TexCoords TexturePart::getTextureCoordinatesNormalised()
{
	return m_tex_coords;
}
