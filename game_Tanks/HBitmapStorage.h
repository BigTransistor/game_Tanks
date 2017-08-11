#pragma once
#include <windows.h>
#include"Picture.h"
#include <iostream>
#include <vector>
using namespace std;
class Game;
class Map;

class HBitmapStorage
{
friend Game;
friend Map;
public:
	Picture standartPlayerTank, standartPlayerBullet , standartEnemyTank;
	HBITMAP brick;
	HBitmapStorage(string bitmapHileName, HINSTANCE& hInstance);
	~HBitmapStorage(){}
};