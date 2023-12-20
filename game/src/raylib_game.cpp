#include <iostream>
#define RAYGUI_IMPLEMENTATION
#include <raylib.h>
#include <raymath.h>
#include <raygui.h>
#include "../_build/Gracz.h"
#include "../_build/Jedzenie.h"
#include "../_build/Bloczki.h"
#include "../_build/camera.h"

#define G 1700
#define PLAYER_JUMP_SPD 750.0f
#define PLAYER_HOR_SPD 200.0f
#define MAX_BULLETS 999


using namespace std;

struct Pocisk {
	Vector2 szybkosc;
	bool aktywny;
	Color kolor = BLUE;
	Vector2 pozycja;
	float wielkosc = 5;
	Vector2 kierunek;

};
bool Ruch;
Color Niebo = { 0, 169, 255,255 };
Color Czarny = { 0, 0, 0,255 };
Color Jasnoszary = { 90,90,90,255 };
Color niewidzialny = { 90,90,90,0 }; 
bool Lewo;
bool Prawo;
Camera2D camera;
Gracz Bohater;
Wrog Przeciwnik;
Boss Wyrzutnia_Rakiet;
Boss Final_Boss;
Pocisk pociski[MAX_BULLETS];
Pocisk rakiety[MAX_BULLETS];
Pocisk laser[MAX_BULLETS];
Texture2D Strzal;
Texture2D Chodzenie;
Texture2D Chodzenie_odw;
Texture2D ded;
bool strzela;
bool Smierc;
float wrogszerokosc;
float bossszerokosc;
float finalszerokosc;
void UpdatePlayer(Gracz* player, Bloczki* envItems, int envItemsLength, float delta);
void UpdateEnemy(Wrog* enemy,float delta);
void UpdateEnemyBoss(Boss* enemy, float delta);
void UpdateFinalEnemyBoss(Boss* enemy, float delta);


int main() {
	
	
	for (int i = 0; i < MAX_BULLETS; i++) {
		pociski[i].pozycja = { 0.0f, 0.0f };
		pociski[i].szybkosc = { 0.0f, 0.0f };
		pociski[i].aktywny = false;
	}
	for (int i = 0; i < MAX_BULLETS; i++) {
		rakiety[i].pozycja = { 0.0f, 0.0f };
		rakiety[i].szybkosc = { 10.0f, 10.0f };
		rakiety[i].aktywny = false;
		rakiety[i].kolor = YELLOW;
	}
	for (int i = 0; i < MAX_BULLETS; i++) {
		laser[i].pozycja = { 0.0f, 0.0f };
		laser[i].szybkosc = { 10.0f, 10.0f };
		laser[i].aktywny = false;
		laser[i].kolor = RED;
	}
	Camera2D camera = { 0 };
	camera.target = Bohater.pozycja;
	camera.offset = { 750 / 2.0f, 750 / 2.0f };
	camera.rotation = 0.0f;
	camera.zoom = 1.0f;
	Bloczki Bloki[] = {
		{{ 0, 0, 1000, 0 }, 0, GREEN },
		{{ 0, 400, 5000, 1200 }, 1, BLACK },
		{{ 300, 200, 400, 10 }, 1, BLACK },
		{{ 250, 300, 100, 10 }, 1, BLACK },
		{{ 650, 300, 100, 10 }, 1, BLACK },
		{{ 0, 0, 5, 1200 }, 1, BLACK },
		{{ 1220, 250, 400, 10 }, 1, BLACK },
		{{ 5000, 400, 5000, 1200 }, 1, BLACK },
		{{ 6500, 250, 400, 10 }, 1, BLACK }
	};
	int envItemsLength = sizeof(Bloki) / sizeof(Bloki[0]);

	InitAudioDevice();

	InitWindow(750, 750, "Gra!");
	SetTargetFPS(60);
	Bohater = Gracz();
	Przeciwnik = Wrog();
	Wyrzutnia_Rakiet = Boss();
	Final_Boss = Boss();
	Final_Boss.pozycja = { 7000,280 };
	Final_Boss.szybkosc = 1;
	Wyrzutnia_Rakiet.pozycja = { 1500,280 };
	Przeciwnik.pozycja = { 900,280 };
	Przeciwnik.szybkosc = 1;
	Bohater.pozycja ={ 50, 280 };
	Bohater.szybkosc = 0;
	Bohater.MozeSkakac = false;

	int currentFrame = 0;
	float frameCounter = 0;
	int currentFramewrog = 0;
	float frameCounterwrog = 0;
	float timeSinceLastDamage = 0.0f;
	float damageInterval = 2.0f;
	float LastRocket = 0.0f;
	float RocketInterval = 0.5f;


	Strzal = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Shot_1.png");
	Texture2D tlo1 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/1.png");
	Texture2D tlo2 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/2.png");
	Texture2D tlo3 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/3.png");
	Texture2D tlo4 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/4.png");
	Texture2D tlo5 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/5.png");
	Texture2D tlo11 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/11.png");
	Texture2D tlo22 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/22.png");
	Texture2D tlo33 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/33.png");
	Texture2D tlo44 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/44.png");
	Texture2D tlo55 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/55.png");
	Texture2D tlo111 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/111.png");
	Texture2D tlo222 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/222.png");
	Texture2D tlo333 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/333.png");
	Texture2D tlo444 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/444.png");
	Texture2D tlo555 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/555.png");
	Texture2D tlo1111 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/1111.png");
	Texture2D tlo2222 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/2222.png");
	Texture2D tlo3333 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/3333.png");
	Texture2D tlo4444 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/4444.png");
	Texture2D tlo5555 = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Night/5555.png");

	Texture2D tlo1d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/1.png");
	Texture2D tlo2d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/2.png");
	Texture2D tlo3d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/3.png");
	Texture2D tlo4d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/4.png");
	Texture2D tlo5d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/5.png");
	Texture2D tlo11d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/11.png");
	Texture2D tlo22d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/22.png");
	Texture2D tlo33d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/33.png");
	Texture2D tlo44d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/44.png");
	Texture2D tlo55d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/55.png");
	Texture2D tlo111d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/111.png");
	Texture2D tlo222d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/222.png");
	Texture2D tlo333d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/333.png");
	Texture2D tlo444d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/444.png");
	Texture2D tlo555d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/555.png");
	Texture2D tlo1111d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/1111.png");
	Texture2D tlo2222d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/2222.png");
	Texture2D tlo3333d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/3333.png");
	Texture2D tlo4444d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/4444.png");
	Texture2D tlo5555d = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Day/5555.png");

	Chodzenie = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Walk.png");
	Texture2D Chodzeniewrog = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Walk_wrog.png");
	Texture2D IdleBoss = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Idle.png");
	Texture2D AttackBoss = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Attack1.png");
	ded = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/ded.png");
	Texture2D FinalBoss = LoadTexture("D:/Users/micha/Desktop/gra/Gra/_build/Shot_2.png");
	Final_Boss.tekstura = FinalBoss;
	Bohater.tekstura = Chodzenie;
	Przeciwnik.tekstura = Chodzeniewrog;
	Wyrzutnia_Rakiet.tekstura = AttackBoss;
	// Ustaw pozycje t³a
	Vector2 pozycjaTlo1 = { camera.target.x ,-50 };
	Vector2 pozycjaTlo2 = { camera.target.x ,80 };
	Vector2 pozycjaTlo3 = { camera.target.x ,80 };
	Vector2 pozycjaTlo4 = { camera.target.x,80 };
	Vector2 pozycjaTlo5 = { camera.target.x ,80 };
	Vector2 pozycjaTlo11 = { camera.target.x + 576,-50 };
	Vector2 pozycjaTlo22 = { camera.target.x + 576,80 };
	Vector2 pozycjaTlo33 = { camera.target.x + 576,80 };
	Vector2 pozycjaTlo44 = { camera.target.x + 576,80 };
	Vector2 pozycjaTlo55 = { camera.target.x + 576,80 };
	Vector2 pozycjaTlo111 = { camera.target.x - 576,-50 };
	Vector2 pozycjaTlo222 = { camera.target.x - 576,80 };
	Vector2 pozycjaTlo333 = { camera.target.x - 576,80 };
	Vector2 pozycjaTlo444 = { camera.target.x - 576,80 };
	Vector2 pozycjaTlo555 = { camera.target.x - 576,80 };
	Vector2 pozycjaTlo1111 = { camera.target.x + 576 * 2,-50 };
	Vector2 pozycjaTlo2222 = { camera.target.x + 576 * 2,80 };
	Vector2 pozycjaTlo3333 = { camera.target.x + 576 * 2,80 };
	Vector2 pozycjaTlo4444 = { camera.target.x + 576 * 2,80 };
	Vector2 pozycjaTlo5555 = { camera.target.x + 576 * 2,80 };

	Chodzenie_odw = Chodzenie;
	Chodzenie_odw.width = -Chodzenie_odw.width;
	Bohater.frameWidth = Bohater.tekstura.width / 8;
	Bohater.frameHeight = Bohater.tekstura.height;
	Przeciwnik.frameWidth = Bohater.tekstura.width / 8;
	Przeciwnik.frameHeight = Bohater.tekstura.height;
	Wyrzutnia_Rakiet.frameWidth = Wyrzutnia_Rakiet.tekstura.width / 8;
	Wyrzutnia_Rakiet.frameHeight = Wyrzutnia_Rakiet.tekstura.height;
	Wyrzutnia_Rakiet.HP = 10;
	Final_Boss.frameWidth = Final_Boss.tekstura.width / 8;
	Final_Boss.frameHeight = Final_Boss.tekstura.height;
	Final_Boss.HP = 15;
	float scrollingBack = 0.0f;
	int Hp = Bohater.HP;
	wrogszerokosc = Przeciwnik.tekstura.width;
	bossszerokosc = Wyrzutnia_Rakiet.tekstura.width;
	finalszerokosc = Final_Boss.tekstura.width;
	while (WindowShouldClose() == false) {
		float deltaTime = GetFrameTime();
		frameCounter += deltaTime;
		frameCounterwrog += deltaTime;
		timeSinceLastDamage += deltaTime;
		LastRocket += deltaTime;
		
		if (timeSinceLastDamage >= damageInterval)
		{
			// Bohater otrzymuje obra¿enia
			Bohater.moze_dostac_obr = true;
			// Resetowanie licznika
			if (Hp > Bohater.HP) {
				Hp = Bohater.HP;
				timeSinceLastDamage = 0.0f;
			}
			
		}
		
		else { Bohater.moze_dostac_obr = false; }
		if (LastRocket >= RocketInterval)
		{
			// Bohater otrzymuje obra¿enia
			Wyrzutnia_Rakiet.mozestrzelac = true;
			Final_Boss.mozestrzelac = true;
			// Resetowanie licznika
			LastRocket = 0.0f;
			
		}
		else { Wyrzutnia_Rakiet.mozestrzelac = false; Final_Boss.mozestrzelac = false;}
		if (Ruch || Bohater.tekstura.id==Strzal.id) {
			if (frameCounter >= 0.1f) // zmieñ klatkê co 0.1 sekundy
			{
				frameCounter = 0;
				currentFrame++;
				if (Bohater.tekstura.id == Strzal.id) { strzela = 1; }
				if (currentFrame > 6.4 && Bohater.tekstura.id == Strzal.id && Bohater.kierunek == 1) { Bohater.tekstura = Chodzenie; currentFrame = 0; strzela = 0; }
				else if (currentFrame > 6.4 && Bohater.tekstura.id == Strzal.id && Bohater.kierunek == -1) { Bohater.tekstura = Chodzenie_odw; currentFrame = 0; strzela = 0;}
				else if (currentFrame > 6.4) currentFrame = 0;

			}
		}

		if (frameCounterwrog >= 0.1f ) // zmieñ klatkê co 0.1 sekundy
			{
				frameCounterwrog = 0;
				currentFramewrog++;
				if (currentFramewrog > 6.4) { 
					if (Przeciwnik.tekstura.id == ded.id) {
						Przeciwnik.ded = true;
					}
					currentFramewrog = 0;
				}

		}
		
		
		scrollingBack -= 0.1f;
		UpdatePlayer(&Bohater,Bloki,envItemsLength, deltaTime);
		UpdateEnemy(&Przeciwnik,deltaTime);
		UpdateEnemyBoss(&Wyrzutnia_Rakiet, deltaTime);
		UpdateFinalEnemyBoss(&Final_Boss, deltaTime);
		if (camera.zoom > 3.0f) camera.zoom = 3.0f;
		else if (camera.zoom < 0.25f) camera.zoom = 0.25f;
		if (scrollingBack <= -tlo1.width * 2) scrollingBack = 0;
		UpdateCameraCenterInsideMap(&camera, &Bohater,Bloki,envItemsLength,deltaTime,750,750);
		BeginDrawing();
		ClearBackground(Jasnoszary);
		BeginMode2D(camera);
		DrawTextureV(tlo1, pozycjaTlo1, WHITE);
		DrawTextureV(tlo11, pozycjaTlo11, WHITE);
		DrawTextureV(tlo111, pozycjaTlo111, WHITE);
		DrawTextureV(tlo1111, pozycjaTlo1111, WHITE);
		DrawTextureV(tlo2, pozycjaTlo2, WHITE);
		DrawTextureV(tlo3, pozycjaTlo3, WHITE);
		DrawTextureV(tlo4, pozycjaTlo4, WHITE);
		DrawTextureV(tlo5, pozycjaTlo5, WHITE);
		DrawTextureV(tlo22, pozycjaTlo22, WHITE);
		DrawTextureV(tlo33, pozycjaTlo33, WHITE);
		DrawTextureV(tlo44, pozycjaTlo44, WHITE);
		DrawTextureV(tlo55, pozycjaTlo55, WHITE);
		DrawTextureV(tlo222, pozycjaTlo222, WHITE);
		DrawTextureV(tlo333, pozycjaTlo333, WHITE);
		DrawTextureV(tlo444, pozycjaTlo444, WHITE);
		DrawTextureV(tlo555, pozycjaTlo555, WHITE);
		DrawTextureV(tlo2222, pozycjaTlo2222, WHITE);
		DrawTextureV(tlo3333, pozycjaTlo3333, WHITE);
		DrawTextureV(tlo4444, pozycjaTlo4444, WHITE);
		DrawTextureV(tlo5555, pozycjaTlo5555, WHITE);
		for (int i = 0; i < envItemsLength; i++) DrawRectangleRec(Bloki[i].rect, Bloki[i].kolor);
		DrawRectangleRec({ 0, 0, 5, 1200 }, BLACK);
		Rectangle sourceRect = { currentFrame * Bohater.frameWidth, 0, Bohater.frameWidth, Bohater.frameHeight };
		Rectangle playerRect = { Bohater.pozycja.x - Bohater.frameWidth+60, Bohater.pozycja.y - Bohater.frameHeight, Bohater.frameWidth , Bohater.frameHeight };
		Rectangle sourceRectwrog = { currentFramewrog * Przeciwnik.frameWidth, 0, Przeciwnik.frameWidth, Przeciwnik.frameHeight };
		Rectangle wrogRect = { Przeciwnik.pozycja.x - Przeciwnik.frameWidth + 60, Przeciwnik.pozycja.y - Przeciwnik.frameHeight+120, Przeciwnik.frameWidth , Przeciwnik.frameHeight };
		Rectangle sourceRectBoss = { currentFramewrog * Wyrzutnia_Rakiet.frameWidth, 0, Wyrzutnia_Rakiet.frameWidth, Wyrzutnia_Rakiet.frameHeight };
		Rectangle BossRect = { Wyrzutnia_Rakiet.pozycja.x - Wyrzutnia_Rakiet.frameWidth + 60, Wyrzutnia_Rakiet.pozycja.y - Wyrzutnia_Rakiet.frameHeight + 120, Wyrzutnia_Rakiet.frameWidth , Wyrzutnia_Rakiet.frameHeight };
		Rectangle sourceRectFinBoss = { currentFramewrog * Final_Boss.frameWidth, 0, Final_Boss.frameWidth, Final_Boss.frameHeight };
		Rectangle FinBossRect = { Final_Boss.pozycja.x - Final_Boss.frameWidth + 60, Final_Boss.pozycja.y - Final_Boss.frameHeight + 120, Final_Boss.frameWidth , Final_Boss.frameHeight };
		Rectangle Przycisk = { GetScreenWidth()-680,camera.target.y-180,620,300 };
		Rectangle Przyciskkoniec = { GetScreenWidth() - 680,camera.target.y - 180,620,300 };

		Vector2 origin = { 0.0f, 0.0f };
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (pociski[i].aktywny) {
				DrawCircleV(pociski[i].pozycja, 5, pociski->kolor);
			}
		}
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (rakiety[i].aktywny) {
				DrawCircleV(rakiety[i].pozycja, rakiety->wielkosc , rakiety->kolor);
			}
		}
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (laser[i].aktywny) {
				DrawCircleV(laser[i].pozycja, laser->wielkosc, laser->kolor);
			}
		}
		//DrawRectangleRec(playerRect, RED);
		DrawTexturePro(Bohater.tekstura, sourceRect, playerRect, origin, 0.0f, WHITE);
		if (!Przeciwnik.ded) {
			DrawTexturePro(Przeciwnik.tekstura, sourceRectwrog, wrogRect, origin, 0.0f, WHITE);
		}
		else { Przeciwnik.pozycja = { -1000,-1000 }; }
		if (!Wyrzutnia_Rakiet.ded) {
			DrawTexturePro(Wyrzutnia_Rakiet.tekstura, sourceRectBoss, BossRect, origin, 0.0f, WHITE);
		}
		else { Wyrzutnia_Rakiet.pozycja = { -1000,-1000 }; }
		if (!Final_Boss.ded) {
			DrawTexturePro(Final_Boss.tekstura, sourceRectFinBoss, FinBossRect, origin, 0.0f, WHITE);
		}
		else { Final_Boss.pozycja = { -1000,-1000 }; }
		if (camera.target.x > pozycjaTlo22.x + 576 / 2) {
			pozycjaTlo1 = { pozycjaTlo22.x ,-50 };
			pozycjaTlo2 = { pozycjaTlo22.x ,80 };
			pozycjaTlo3 = { pozycjaTlo22.x ,80 };
			pozycjaTlo4 = { pozycjaTlo22.x ,80 };
			pozycjaTlo5 = { pozycjaTlo22.x ,80 };
			pozycjaTlo11 = { camera.target.x + 570 / 2,-50 };
			pozycjaTlo22 = { camera.target.x + 570 / 2,80 };
			pozycjaTlo33 = { camera.target.x + 570 / 2,80 };
			pozycjaTlo44 = { camera.target.x + 570 / 2,80 };
			pozycjaTlo55 = { camera.target.x + 570 / 2,80 };
			pozycjaTlo111 = { pozycjaTlo22.x - 570*2 ,-50 };
			pozycjaTlo222 = { pozycjaTlo22.x - 570*2 ,80 };
			pozycjaTlo333 = { pozycjaTlo22.x - 570*2 ,80 };
			pozycjaTlo444 = { pozycjaTlo22.x - 570*2 ,80 };
			pozycjaTlo555 = { pozycjaTlo22.x - 570*2,80 };
			pozycjaTlo1111 = { camera.target.x + 570*1.5f ,-50 };
			pozycjaTlo2222 = { camera.target.x + 570 * 1.5f ,80 };
			pozycjaTlo3333 = { camera.target.x + 570 * 1.5f ,80 };
			pozycjaTlo4444 = { camera.target.x + 570 * 1.5f ,80 };
			pozycjaTlo5555 = { camera.target.x + 570 * 1.5f ,80 };
		}
		else if (camera.target.x < pozycjaTlo2.x + 576 / 2 && camera.target.x > 576) {
			pozycjaTlo11 = { camera.target.x ,-50 };
			pozycjaTlo22 = { camera.target.x ,80 };
			pozycjaTlo33 = { camera.target.x ,80 };
			pozycjaTlo44 = { camera.target.x ,80 };
			pozycjaTlo55 = { camera.target.x ,80 };
			pozycjaTlo1 = { camera.target.x - 570 * 2,-50 };
			pozycjaTlo2 = { camera.target.x - 570 * 2,80 };
			pozycjaTlo3 = { camera.target.x - 570 * 2,80 };
			pozycjaTlo4 = { camera.target.x - 570 * 2,80 };
			pozycjaTlo5 = { camera.target.x - 570 * 2,80 };
			pozycjaTlo111 = { pozycjaTlo22.x - 570 ,-50 };
			pozycjaTlo222 = { pozycjaTlo22.x - 570 ,80 };
			pozycjaTlo333 = { pozycjaTlo22.x - 570 ,80 };
			pozycjaTlo444 = { pozycjaTlo22.x - 570 ,80 };
			pozycjaTlo555 = { pozycjaTlo22.x - 570 ,80 };
			pozycjaTlo1111 = { camera.target.x + 570 * 1.5f ,-50 };
			pozycjaTlo2222 = { camera.target.x + 570 * 1.5f ,80 };
			pozycjaTlo3333 = { camera.target.x + 570 * 1.5f ,80 };
			pozycjaTlo4444 = { camera.target.x + 570 * 1.5f ,80 };
			pozycjaTlo5555 = { camera.target.x + 570 * 1.5f ,80 };
		}


		EndMode2D();
		DrawText(TextFormat("HP:%i", int(Bohater.HP)), GetScreenWidth() - 50, GetScreenHeight()-730, 20, RED);
		if (Bohater.HP <= 0) {
			Bohater.HP = 0;
			if (GuiButton(Przycisk, "Game Over")) {
				CloseWindow();
			}

		}
		if (Wyrzutnia_Rakiet.ded || IsKeyDown(KEY_U)) {
			if (GuiButton(Przyciskkoniec, "2 LVL")) {
				Bohater.pozycja = { 6500,280 };
				
				tlo1 = tlo1d;
				tlo2 = tlo2d;
				tlo3 = tlo3d;
				tlo4 = tlo4d;
				tlo11 = tlo11d;
				tlo22 = tlo22d;
				tlo33 = tlo33d;
				tlo44 = tlo44d;
				tlo111 = tlo111d;
				tlo222 = tlo222d;
				tlo333 = tlo333d;
				tlo444 = tlo444d;
				tlo1111 = tlo1111d;
				tlo2222 = tlo2222d;
				tlo3333 = tlo3333d;
				tlo4444 = tlo4444d;
				pozycjaTlo1 = { camera.target.x ,-50 };
				pozycjaTlo2 = { camera.target.x ,80 };
				pozycjaTlo3 = { camera.target.x ,80 };
				pozycjaTlo4 = { camera.target.x,80 };
				pozycjaTlo5 = { camera.target.x ,80 };
				pozycjaTlo11 = { camera.target.x + 576,-50 };
				pozycjaTlo22 = { camera.target.x + 576,80 };
				pozycjaTlo33 = { camera.target.x + 576,80 };
				pozycjaTlo44 = { camera.target.x + 576,80 };
				pozycjaTlo55 = { camera.target.x + 576,80 };
				pozycjaTlo111 = { camera.target.x - 576,-50 };
				pozycjaTlo222 = { camera.target.x - 576,80 };
				pozycjaTlo333 = { camera.target.x - 576,80 };
				pozycjaTlo444 = { camera.target.x - 576,80 };
				pozycjaTlo555 = { camera.target.x - 576,80 };
				pozycjaTlo1111 = { camera.target.x + 576 * 2,-50 };
				pozycjaTlo2222 = { camera.target.x + 576 * 2,80 };
				pozycjaTlo3333 = { camera.target.x + 576 * 2,80 };
				pozycjaTlo4444 = { camera.target.x + 576 * 2,80 };
				pozycjaTlo5555 = { camera.target.x + 576 * 2,80 };
				ClearBackground(WHITE);
				Wyrzutnia_Rakiet.ded = false;

			}
		}
		if (Final_Boss.HP <= 0) {
			if (GuiButton(Przycisk, "YOU WIN")) {
				CloseWindow();
			}

		}
		EndDrawing();
	}
	UnloadTexture(tlo1);

	CloseWindow();
	return 0;
}

void UpdateEnemy(Wrog* enemy,float delta) {
	if (enemy->aktywny) {
		if (Bohater.pozycja.x > enemy->pozycja.x) {
			enemy->pozycja.x += (PLAYER_HOR_SPD * delta) * 0.25;
			//if (Bohater.pozycja.x < enemy->pozycja.x && Bohater.pozycja.y > enemy->pozycja.y) Bohater.HP--;
			enemy->tekstura.width = wrogszerokosc;
			//cout << enemy->pozycja.x << endl;
			//cout << Bohater.pozycja.x << endl;
			if ((enemy->pozycja.x > Bohater.pozycja.x - 15) && (Bohater.pozycja.y >= enemy->pozycja.y+55) && Bohater.moze_dostac_obr) {
				Bohater.HP = Bohater.HP - 0.5f;
			}
		}
		else if (Bohater.pozycja.x < enemy->pozycja.x) {
			enemy->pozycja.x -= (PLAYER_HOR_SPD * delta) * 0.25;
			enemy->tekstura.width = -wrogszerokosc;
			if ((enemy->pozycja.x < Bohater.pozycja.x + 25 ) && (Bohater.pozycja.y >= enemy->pozycja.y+55) && Bohater.moze_dostac_obr) {
				Bohater.HP = Bohater.HP - 0.5f;
			}
		}
		
		
	}
	else {
		enemy->tekstura = ded;
	}
	
	

}
void UpdateEnemyBoss(Boss* enemy, float delta) {
	if (enemy->aktywny && Bohater.pozycja.x < 5000) {
		if (Bohater.pozycja.x > enemy->pozycja.x) {
			//if (Bohater.pozycja.x < enemy->pozycja.x && Bohater.pozycja.y > enemy->pozycja.y) Bohater.HP--;
			enemy->tekstura.width = bossszerokosc;
			//cout << enemy->pozycja.x << endl;
			//cout << Bohater.pozycja.x << endl;
			if ((enemy->pozycja.x >= Bohater.pozycja.x - 15) && (Bohater.pozycja.y >= enemy->pozycja.y + 55) && Bohater.moze_dostac_obr) {
				Bohater.HP = Bohater.HP - 0.5f;
			}
		}
		else if (Bohater.pozycja.x < enemy->pozycja.x) {
			enemy->tekstura.width = -bossszerokosc;
			if ((enemy->pozycja.x <= Bohater.pozycja.x + 25) && (Bohater.pozycja.y >= enemy->pozycja.y + 55) && Bohater.moze_dostac_obr) {
				Bohater.HP = Bohater.HP - 0.5f;
			}
		}
		if ((Bohater.pozycja.x > enemy->pozycja.x && !(Bohater.pozycja.x > enemy->pozycja.x-360) ) || Bohater.pozycja.x > enemy->pozycja.x) {
			//enemy->mozestrzelac = true;
			//cout << "Tak"<<endl; 
		}
		Vector2 Bohaterpozycjapopr = { Bohater.pozycja.x,Bohater.pozycja.y - 100 };
		Vector2 direction = Vector2Subtract(Bohaterpozycjapopr, enemy->pozycja); // Oblicz wektor kierunku
		float length = Vector2Length(direction); // Oblicz d³ugoœæ wektora
		if (length != 0) { // Unikaj dzielenia przez zero
			direction.x /= length; // Normalizuj wektor
			direction.y /= length;
		}
		if (enemy->mozestrzelac) {
			for (int i = 0; i < MAX_BULLETS; i++) {
				if (!rakiety[i].aktywny) {
					rakiety[i].pozycja = { enemy->pozycja.x + 25, enemy->pozycja.y+40 };
					rakiety[i].szybkosc = { 2.0f * direction.x, 2.0f * direction.y }; // Prêdkoœæ pocisku
					rakiety[i].aktywny = true;
					break;
				}
			}
		}
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (rakiety[i].aktywny) {
				// Aktualizacja pozycji pocisku

				rakiety[i].pozycja.x += rakiety[i].szybkosc.x;
				rakiety[i].pozycja.y += rakiety[i].szybkosc.y;
			}
			if (rakiety[i].pozycja.x < Bohater.pozycja.x+25 && rakiety[i].pozycja.x > Bohater.pozycja.x-25 && rakiety[i].pozycja.y - 15 > Bohater.pozycja.y - Bohater.frameHeight && rakiety[i].pozycja.y < Bohater.pozycja.y && Bohater.moze_dostac_obr) {
				rakiety[i].aktywny = false;
				Bohater.HP = Bohater.HP - 0.5f;
			}
			if (rakiety[i].pozycja.x > Bohater.pozycja.x + 720 || rakiety[i].pozycja.y > Bohater.pozycja.y + 720 || rakiety[i].pozycja.x < Bohater.pozycja.x - 720 || rakiety[i].pozycja.y < Bohater.pozycja.y - 720) {
				rakiety[i].aktywny = false;
			}
		}
	}
	else {
		enemy->tekstura = ded;
	}



}
void UpdateFinalEnemyBoss(Boss* enemy, float delta) {
	if (enemy->aktywny && Bohater.pozycja.x >= 5000) {
		if (Bohater.pozycja.x > enemy->pozycja.x) {
			enemy->pozycja.x += (PLAYER_HOR_SPD * delta) * 0.25;
			enemy->tekstura.width = finalszerokosc;
			//cout << enemy->pozycja.x << endl;
			//cout << Bohater.pozycja.x << endl;
			if ((enemy->pozycja.x >= Bohater.pozycja.x - 15) && (Bohater.pozycja.y >= enemy->pozycja.y + 55) && Bohater.moze_dostac_obr) {
				Bohater.HP = Bohater.HP - 0.5f;
			}
		}
		else if (Bohater.pozycja.x < enemy->pozycja.x) {
			enemy->pozycja.x -= (PLAYER_HOR_SPD * delta) * 0.25;
			enemy->tekstura.width = -finalszerokosc;
			if ((enemy->pozycja.x <= Bohater.pozycja.x + 25) && (Bohater.pozycja.y >= enemy->pozycja.y + 55) && Bohater.moze_dostac_obr) {
				Bohater.HP = Bohater.HP - 0.5f;
			}
		}
		if ((Bohater.pozycja.x > enemy->pozycja.x && !(Bohater.pozycja.x > enemy->pozycja.x - 360)) || Bohater.pozycja.x > enemy->pozycja.x) {
			//enemy->mozestrzelac = true;
			//cout << "Tak"<<endl; 
		}
		Vector2 Bohaterpozycjapopr = { Bohater.pozycja.x,Bohater.pozycja.y - 100 };
		Vector2 direction = Vector2Subtract(Bohaterpozycjapopr, enemy->pozycja); // Oblicz wektor kierunku
		float length = Vector2Length(direction); // Oblicz d³ugoœæ wektora
		if (length != 0) { // Unikaj dzielenia przez zero
			direction.x /= length; // Normalizuj wektor
			direction.y /= length;
		}
		if (enemy->mozestrzelac) {
			for (int i = 0; i < MAX_BULLETS; i++) {
				if (!laser[i].aktywny) {
					laser[i].pozycja = { enemy->pozycja.x + 25, enemy->pozycja.y + 40 };
					laser[i].szybkosc = { 4.0f * direction.x, 4.0f * direction.y }; // Prêdkoœæ pocisku
					laser[i].aktywny = true;
					break;
				}
			}
		}
		for (int i = 0; i < MAX_BULLETS; i++) {
			if (laser[i].aktywny) {
				// Aktualizacja pozycji pocisku

				laser[i].pozycja.x += laser[i].szybkosc.x;
				laser[i].pozycja.y += laser[i].szybkosc.y;
				laser[i].wielkosc = 10;
			}
			if (laser[i].pozycja.x < Bohater.pozycja.x + 25 && laser[i].pozycja.x > Bohater.pozycja.x - 25 && laser[i].pozycja.y - 15 > Bohater.pozycja.y - Bohater.frameHeight && laser[i].pozycja.y < Bohater.pozycja.y && Bohater.moze_dostac_obr) {
				laser[i].aktywny = false;
				Bohater.HP = Bohater.HP - 0.5f;
			}
			if (laser[i].pozycja.x > Bohater.pozycja.x + 720 || laser[i].pozycja.y > Bohater.pozycja.y + 720 || laser[i].pozycja.x < Bohater.pozycja.x - 720 || laser[i].pozycja.y < Bohater.pozycja.y - 720) {
				laser[i].aktywny = false;
			}
		}
	}
	else {
		
	}



}

void UpdatePlayer(Gracz* player, Bloczki* envItems, int envItemsLength, float delta)
{
	
	if (player->HP <= 0) Smierc = true;
	if (IsKeyDown(KEY_LEFT) && !Smierc) { 
		player->pozycja.x -= PLAYER_HOR_SPD * delta;
		if (player->kierunek == 1) {
			player->tekstura.width = -player->tekstura.width;
		}
		player->kierunek = -1;
		
	}
	if (IsKeyDown(KEY_RIGHT) && !Smierc) {
		player->pozycja.x += PLAYER_HOR_SPD * delta;
		if (player->kierunek == -1) {
			player->tekstura.width = -player->tekstura.width;
		}
		player->kierunek = 1;
	}
	if (IsKeyDown(KEY_UP) && player->MozeSkakac && !Smierc)
	{
		player->szybkosc = -PLAYER_JUMP_SPD;
		player->MozeSkakac = false;
	}
	if (IsKeyDown(KEY_K) && !Smierc)
	{
		player->HP--;
	}
	if (IsKeyPressed(KEY_SPACE) && strzela == 0 && !Smierc) {
		float Szerokosc = Bohater.tekstura.width;
		Bohater.tekstura = Strzal;
		Bohater.tekstura.width = Szerokosc;
		
		for (int i = 0; i < MAX_BULLETS; i++) {
			
			if (!pociski[i].aktywny) {
				pociski[i].pozycja = { player->pozycja.x+25, player->pozycja.y-57 };
				pociski[i].szybkosc = { 10.0f * player->kierunek, 0.0f }; // Prêdkoœæ pocisku
				pociski[i].aktywny = true;
				break;
			}
			if (pociski[i].pozycja.x > player->pozycja.x + 720 || pociski[i].pozycja.y > player->pozycja.y + 720 || pociski[i].pozycja.x < player->pozycja.x - 720 || pociski[i].pozycja.y < player->pozycja.y - 720) {
				pociski[i].aktywny = false;
			}
		}
	}
	if (IsKeyDown(KEY_LEFT)) {
		Ruch = true;
	}
	else if (IsKeyDown(KEY_RIGHT)) {
		Ruch = true;
	}
	else { Ruch = false; }
	for (int i = 0; i < MAX_BULLETS; i++) {
		if (pociski[i].aktywny) {
			// Aktualizacja pozycji pocisku
			
				pociski[i].pozycja.x += pociski[i].szybkosc.x;
				pociski[i].pozycja.y += pociski[i].szybkosc.y;
				//cout << pociski[i].pozycja.y<<endl;
				//cout << Przeciwnik.pozycja.t<<endl;'
				//cout << Przeciwnik.pozycja.y + (Przeciwnik.frameHeight/2) << endl;
			// Jeœli pocisk wyjdzie poza ekran, dezaktywuj go
			if (player->pozycja.x > Wyrzutnia_Rakiet.pozycja.x && pociski[i].pozycja.x < Wyrzutnia_Rakiet.pozycja.x && pociski[i].pozycja.y + 5 > Wyrzutnia_Rakiet.pozycja.y + (Wyrzutnia_Rakiet.frameHeight / 2)) {
					pociski[i].aktywny = false;
					Wyrzutnia_Rakiet.HP--;
					if (Wyrzutnia_Rakiet.HP <= 0) Wyrzutnia_Rakiet.ded = true;

			}
			if (player->pozycja.x < Wyrzutnia_Rakiet.pozycja.x && pociski[i].pozycja.x > Wyrzutnia_Rakiet.pozycja.x && pociski[i].pozycja.y + 5 > Wyrzutnia_Rakiet.pozycja.y + (Wyrzutnia_Rakiet.frameHeight / 2)) {
					pociski[i].aktywny = false;
					Wyrzutnia_Rakiet.HP--;
					if (Wyrzutnia_Rakiet.HP <= 0) Wyrzutnia_Rakiet.ded = true;

			}
			if (player->pozycja.x > Final_Boss.pozycja.x && pociski[i].pozycja.x < Final_Boss.pozycja.x && pociski[i].pozycja.y + 5 > Final_Boss.pozycja.y + (Final_Boss.frameHeight / 2)) {
				pociski[i].aktywny = false;
				Final_Boss.HP--;
				if (Final_Boss.HP <= 0) Final_Boss.ded = true;

			}
			if (player->pozycja.x < Final_Boss.pozycja.x && pociski[i].pozycja.x > Final_Boss.pozycja.x && pociski[i].pozycja.y + 5 > Final_Boss.pozycja.y + (Final_Boss.frameHeight / 2)) {
				pociski[i].aktywny = false;
				Final_Boss.HP--;
				if (Final_Boss.HP <= 0) Final_Boss.ded = true;

			}
			if (player->pozycja.x > Przeciwnik.pozycja.x && pociski[i].pozycja.x < Przeciwnik.pozycja.x && pociski[i].pozycja.y+5 > Przeciwnik.pozycja.y + (Przeciwnik.frameHeight / 2)) {
				pociski[i].aktywny = false;
				Przeciwnik.aktywny = false;
			}
			if (player->pozycja.x < Przeciwnik.pozycja.x && pociski[i].pozycja.x > Przeciwnik.pozycja.x && pociski[i].pozycja.y+5 > Przeciwnik.pozycja.y + (Przeciwnik.frameHeight / 2)) {
				pociski[i].aktywny = false;
				Przeciwnik.aktywny = false;
				
			}
			if (pociski[i].pozycja.x > player->pozycja.x + 720 || pociski[i].pozycja.y > player->pozycja.y + 720 || pociski[i].pozycja.x < player->pozycja.x - 720 || pociski[i].pozycja.y < player->pozycja.y - 720) {
				pociski[i].aktywny = false;
			}
		}
	}

	int hitObstacle = 0;
	for (int i = 0; i < envItemsLength; i++)
	{
		Bloczki* ei = envItems + i;
		Vector2* p = &(player->pozycja);
		if (ei->blokuje &&
			ei->rect.x <= p->x &&
			ei->rect.x + ei->rect.width >= p->x &&
			ei->rect.y >= p->y &&
			ei->rect.y <= p->y + player->szybkosc * delta)
		{
			hitObstacle = 1;
			player->szybkosc = 0.0f;
			p->y = ei->rect.y;
		}
	}
	

	if (!hitObstacle)
	{
		player->pozycja.y += player->szybkosc * delta;
		player->szybkosc += G * delta;
		player->MozeSkakac = false;
	}
	else player->MozeSkakac = true;
}
