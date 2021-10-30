#include "Text.h"

#include <iostream>
#include <cstdint>
#include <fstream>

#include "RenderWindow.h"

using json = nlohmann::json;

Character c[128];

Texture* Text::m_font_texture = nullptr;


Text::Text(RenderWindow* renderer, const std::string& caption, const uint32_t& font_size, const glm::vec3& pos, const glm::vec4& color)
: 
Drawable(color),
RectangleBase(0.0f, 0.0f),
m_renderer(renderer), 
m_caption(caption), 
m_font_size(font_size), 
m_requires_update(true)
{
	setPosition(pos);
	setCaption(caption);
}

Text::~Text()
{
	for (auto& sprite : m_sprite_caption) {
		delete sprite;
	}
}

void Text::setFontTexture(Texture* font_texture)
{
	m_font_texture = font_texture;
}


void Text::onClick()
{
	//std::cout << "PRESSED TEXT\n";
}

void Text::setCaption(const std::string& caption, const uint32_t& font_size, const glm::vec4& font_color)
{
	for (auto& sprite : m_sprite_caption) {
		delete sprite;
	}
	m_sprite_caption.clear();

	float x_offset = 0.0f;
	float highest_y = 0.0f;


	float font_size_portion = font_size / 48.0f;

	for (uint32_t i = 0; i < caption.size(); ++i) {
		Character& character_data = c[caption[i]];

		glm::vec3 sprite_pos = glm::vec3(0.0f);
		sprite_pos.x += x_offset + character_data.bearing_left * character_data.size * font_size_portion;
		sprite_pos.y += character_data.bearing_bot * character_data.size * font_size_portion;

		highest_y = std::max(highest_y, character_data.height * font_size_portion);

		x_offset += character_data.advance * character_data.size * font_size_portion;


		// PRECOMPUTED FONT SIZES
		float tex_id = 0.0f;

		if (font_size < 20) {
			tex_id = 0.0f;
		}
		else if (font_size < 24) {
			tex_id = 1.0f;
		}
		else if (font_size < 40) {
			tex_id = 2.0;
		}
		else if (font_size < 54) {
			tex_id = 3.0f;
		}
		else if (font_size < 70) {
			tex_id = 4.0f;
		}
		else if (font_size < 90) {
			tex_id = 5.0f;
		}
		else {
			tex_id = 6.0f;
		}

		character_data.texture.setTextureSlot(tex_id);
		Sprite* letter = new Sprite(
			m_renderer, 
			&character_data.texture, 
			sprite_pos, 
			character_data.width * font_size_portion,
			character_data.height * font_size_portion,
			tex_id, 
			font_color
		);
		letter->setParent(this);
		
		m_sprite_caption.push_back(letter);
	}
	setWidth(x_offset);
	setHeight(highest_y);
	setOrigin(glm::vec3(x_offset / 2, highest_y / 2, 0.0f));
	m_requires_update = false;
}


void Text::loadFontData(const std::string& font_data_path)
{
	std::ifstream file(font_data_path);

	if (file.is_open()) {
		std::string whole_file;
		file >> whole_file;

		json top = json::parse(whole_file);

		json atlas_info = top["atlas"];
		json glyphs = top["glyphs"];
		json kerning = top["kerning"];

		float atlas_width = std::stoi(atlas_info["width"].dump());
		float atlas_height = std::stoi(atlas_info["height"].dump());

		for (auto& glyph : glyphs) {
			uint8_t ascii_code = glyph["unicode"];
			float advance = std::stof(glyph["advance"].dump());
			float size = std::stof(atlas_info["size"].dump());
			
			if (ascii_code == ' ') {
				c[ascii_code].advance = advance;

				c[ascii_code].size = size;

				c[ascii_code].texture.setSource(m_font_texture);
				c[ascii_code].texture.setTextureCoords(TexCoords(
					glm::vec2(0.0f, 0.0f),
					glm::vec2(0.0f, 0.0f)));

				continue;
			}

			json atlas_bounds = glyph["atlasBounds"];
			json plane_bounds = glyph["planeBounds"];


			c[ascii_code].texture.setSource(m_font_texture);


			uint32_t left_coord = std::stoi(atlas_bounds["left"].dump());
			uint32_t right_coord = std::stoi(atlas_bounds["right"].dump());
			uint32_t bot_coord = std::stoi(atlas_bounds["bottom"].dump());
			uint32_t top_coord = std::stoi(atlas_bounds["top"].dump());

			float left_bound = std::stof(plane_bounds["left"].dump());
			float bot_bound = std::stof(plane_bounds["bottom"].dump());
			float right_bound = std::stof(plane_bounds["right"].dump());
			float top_bound = std::stof(plane_bounds["top"].dump());


			c[ascii_code].width = right_coord - left_coord;
			c[ascii_code].height = top_coord - bot_coord;

			c[ascii_code].bearing_left = left_bound;
			c[ascii_code].bearing_bot = bot_bound;
			c[ascii_code].bearing_right = right_bound;
			c[ascii_code].bearing_top = top_bound;

			c[ascii_code].advance = advance;

			c[ascii_code].size = size;

			c[ascii_code].texture.setTextureCoords(TexCoords(
													glm::vec2(left_coord, top_coord), 
													glm::vec2(right_coord, bot_coord)));
			
		}

	}
	else {
		std::cout << "[ERROR]Text.cpp: Couldn't open file \n";
	}
	file.close();
}

std::string Text::getCaption() const
{
	return m_caption;
}

void Text::setCaption(const std::string& caption)
{
	m_requires_update = true;
	m_caption = caption;
}

uint32_t Text::getFontSize() const
{
	return m_font_size;
}

void Text::setFontSize(const uint32_t& font_size)
{
	m_requires_update = true;
	m_font_size = font_size;
}


void Text::draw()
{
	// If text has changed or font has changed
	// every sprite is reloaded
	if (m_requires_update) {
		setCaption(m_caption, m_font_size, getColor());
	}



	for (auto& character : m_sprite_caption) {
		character->setColor(getColor());
		
		m_renderer->draw(character);
	}
}

Character::Character()
:
width(0.0f),
height(0.0f),
bearing_left(0.0f),
bearing_right(0.0f),
bearing_bot(0.0f),
bearing_top(0.0f),
advance(0.0f),
size(0.0f)
{
}
