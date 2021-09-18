#pragma once
#include <vector>
#include <unordered_map>
#include <string>

#include <glm/glm.hpp>

#include "Primitive.h"
#include "Texture.h"


class Renderer;

class Text
{
public:

	glm::vec3 pos;

public:

	Text() : pos(0.0f), m_renderer(nullptr), m_font_texture(nullptr) {}
	Text(Renderer* renderer, Texture* font_texture);
	Text(Renderer* renderer, Texture* font_texture, const std::string& caption);
	Text(Renderer* renderer, Texture* font_texture, const std::string& caption, const glm::vec3& _pos);
	~Text();
	void setCaption(const std::string& caption, const float& size = 128.0f);

	void setRenderer(Renderer* renderer);
	void setFontTexture(Texture* font_texture) { m_font_texture = font_texture; }

	void redraw();

private:

	std::vector<Sprite*> m_caption;
		
	Renderer* m_renderer;

	Texture* m_font_texture;

};

