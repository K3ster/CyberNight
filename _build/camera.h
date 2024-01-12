// camera.h
#pragma once

#include "raylib.h"
#include "Gracz.h"
#include "Bloczki.h"

void UpdateCameraCenterInsideMap(Camera2D* camera, Gracz* player, Bloczki* envItems, int envItemsLength, float delta, int width, int height);

