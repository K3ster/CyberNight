#include "Jedzenie.h"
#include <iostream>
#include "camera.h"
#define wielkoscPunktow 30
#define iloscPunktow 25
using namespace std;
Jedzenie::Jedzenie()
{
	Image image = LoadImage("D:/Users/micha/Desktop/gra/Gra/game/src/apple.png");
	if (!IsImageReady(image)) {
		cout << "Nie wczytuje zdjecia" << endl;
	}

	texture = LoadTextureFromImage(image);
	UnloadImage(image);
}

Jedzenie::~Jedzenie()
{
	UnloadTexture(texture);
}

void Jedzenie::Draw()
{
	DrawTexture(texture, position.x * wielkoscPunktow, position.y * wielkoscPunktow, WHITE);
}
