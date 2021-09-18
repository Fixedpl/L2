#pragma once
#include <iostream>
#include "RenderWindow.h"





class Game : protected RenderWindow
{
public:
	
	Game();

	void run();

protected:

	void onUpdate(const float& frame_time);

private:

	static constexpr uint32_t m_window_width = 1280;
	static constexpr uint32_t m_window_height = 720;

	uint32_t array_size = 1000;


	Texture tex1;
	Texture tex3;
	TexturePart tex2;

	Text title;

	Sprite sprite;
	Sprite sprite2;

	bool once = false;

	Animation* test_animation;

};

