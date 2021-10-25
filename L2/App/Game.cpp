#include "Game.h"

#include <glm/gtx/string_cast.hpp>

Game::Game()
	:
	RenderWindow(1280, 720, "Game"),
	tex3(1), font_tex(0)
{
	//setVSync(false);
	rect = new Rectangle(this, glm::vec3(100.0f, 100.0f, 0.0f), 100.0f, 100.0f);

	tex3.loadTexture("res/texture/adios.png");

	font_tex.loadTexture("res/texture/arial_atlas.png");

	Text::setFontTexture(&font_tex);
	Text::loadFontData("res/font/arial_atlas_data.json");
	title = new Text(this, "Anarchia ._~=", 26, glm::vec3(700.0f, 250.0f, 0.0f), glm::vec4(0.2f, 0.6f, 0.7f, 1.0f));

	sprite2 = new Sprite(this, &tex3, glm::vec3(500.0f, 200.0f, 0.0f), 40.0f, 40.0f, glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));

	//test_animation = new BezierTrajectory(&sprite, glm::vec2(400.0f, 400.0f), 2.0f, glm::vec2(100.0f, 400.0f));
	draw(title);
	draw(rect);
	draw(sprite2);
}

Game::~Game()
{
	delete rect;
	delete title;
	delete sprite2;
}

void Game::run()
{
	display();
}

void Game::onEvent(const float& frame_time) 
{
	if (isLeftMousePressed()) {
		glm::vec2 mouse_pos = getLastMousePosition();
		std::cout << mouse_pos.x << ":" << mouse_pos.y << "\n";
	}

	if (isKeyPressed(KEY_W) && !once) {
		once = true;
		pushAnimation(test_animation);
	}
	if (isKeyPressed(KEY_S)) {
		

		rect->rotate(0.5f);
		title->move(glm::vec3(-1.0f, 0.0f, 0.0f));
		title->rotate(0.5f);
		draw(title);
		draw(rect);
		
	}
}

void Game::onUpdate(const float& frame_time)
{
	
}
