#pragma once
#include "../raylib-master/src/raylib.h"
class Gracz {
public:
	Vector2 pozycja;
	Texture2D tekstura;
	float HP = 3;
	bool MozeSkakac;
	float szybkosc;
	int kierunek = 1;
	int frameWidth;
	int frameHeight;
	bool moze_dostac_obr;
	Gracz();
	
};
class Wrog :public Gracz {
public:
	bool ded = false;
	bool aktywny = true;
	Wrog() = default;
};

class Boss :public Wrog {
public:
	bool mozestrzelac=false;
	Boss() = default;
};
