#pragma once
#include <raylib.h>
typedef struct Bloczki {
	Rectangle rect;
	int blokuje;
	Color kolor;

	bool operator==(const Bloczki& other) const
	{
		return false;
	}

	Bloczki() = default;

	Bloczki(const Rectangle& rect, int blokuje, const Color& kolor)
		: rect(rect), blokuje(blokuje), kolor(kolor)
	{
	}
}Bloki;

