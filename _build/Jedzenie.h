#pragma once
#include <raylib.h>


class Jedzenie {
public:
	Vector2 position = { 5,6 };
	Texture2D texture;
	Jedzenie();
	~Jedzenie();

	void Draw();

};

