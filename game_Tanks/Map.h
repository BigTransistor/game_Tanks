#pragma once
#include <list>
#include "Bullet.h"
#include "Tank.h"
#include "Block.h"
#include "HBitmapStorage.h"
#include "RemoveOldImage.h"
using namespace std;
class Game;

class Map
{
	friend Game;
protected:
	RECT frame;
	list<Tank> enemyTankList;
	list<MoveBullet> bulletList;
	list<Block> blockList;
	list<RemoveOldImage> removeOldImage;
	Tank* playerTank;
public:
	short int get_length() { return frame.right; }
	short int get_height() { return frame.bottom; }
	void render(HWND& hWnd);
	void draw(HDC& hDc, HWND& hWnd, HBITMAP& hBitmap, RECT& coordinates);
	Map(string objectFileName, HINSTANCE hInstance, HBitmapStorage& hBitmapStorage);
	~Map();
};
