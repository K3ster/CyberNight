// raylib_game.cpp
#include "camera.h"
#include <raymath.h>
#include "../_build/Gracz.h"
#include "../_build/Jedzenie.h"
#include "../_build/Bloczki.h"
#include "../_build/camera.h"

// ...

void UpdateCameraCenterInsideMap(Camera2D* camera, Gracz* player, Bloczki* envItems, int envItemsLength, float delta, int width, int height)
{
	camera->target = player->pozycja;
	camera->offset = { width / 2.0f, height / 2.0f };
	float minX = 1000, minY = 1000, maxX = -1000, maxY = -1000;

	for (int i = 0; i < envItemsLength; i++)
	{
		Bloczki* ei = envItems + i;
		minX = fminf(ei->rect.x, minX);
		maxX = fmaxf(ei->rect.x + ei->rect.width, maxX);
		minY = fminf(ei->rect.y, minY);
		maxY = fmaxf(ei->rect.y + ei->rect.height, maxY);
	}

	Vector2 max = GetWorldToScreen2D({ maxX, maxY }, *camera);
	Vector2 min = GetWorldToScreen2D({ minX, minY }, *camera);

	if (max.x < width) camera->offset.x = width - (max.x - width / static_cast<float>(2));
	if (max.y < height) camera->offset.y = height - (max.y - height / static_cast<float>(2));
	if (min.x > 0) camera->offset.x = width / static_cast<float>(2) - min.x;
	if (min.y > 0) camera->offset.y = height / static_cast<float>(2) - min.y;
}
