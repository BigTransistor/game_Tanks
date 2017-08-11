#include "Map.h"
#include <fstream>
#include <string>
using namespace std;
void Map::render(HWND& hWnd)
{
	InvalidateRect(hWnd, &frame, true);
	PAINTSTRUCT paintStruct;
	HDC hDc = BeginPaint(hWnd, &paintStruct);

	draw(hDc, hWnd, *playerTank->get_hBitmap(), playerTank->get_coordinates());

	for (auto tank = enemyTankList.begin(); tank != enemyTankList.end(); tank++)
		draw(hDc, hWnd, *tank->get_hBitmap(), tank->get_coordinates());

	for (auto bullet = bulletList.begin(); bullet != bulletList.end(); bullet++)
		draw(hDc, hWnd, *bullet->get_hBitmap(), bullet->get_coordinates());

	for (auto block(blockList.begin()); block != blockList.end(); block++)
		draw(hDc, hWnd, *block->get_hBitmap(), block->get_coordinates());

	EndPaint(hWnd, &paintStruct);
	ReleaseDC(hWnd, hDc);
	DeleteDC(hDc);
}
void Map::draw(HDC& hDc, HWND& hWnd, HBITMAP& hBitmap, RECT& coordinates)
{
	HDC cHDc = CreateCompatibleDC(hDc);
	SelectObject(cHDc, hBitmap);
	BitBlt(hDc, coordinates.left, coordinates.top, coordinates.right - coordinates.left, coordinates.bottom - coordinates.top, cHDc, 0, 0, SRCCOPY);
	ReleaseDC(hWnd, cHDc);
	DeleteDC(cHDc);
}
Map::Map(string objectFileName, HINSTANCE hInstance, HBitmapStorage& hBitmapStorage) : frame{ 0, 0, 600, 600 }
{
	/*ifstream file{ objectFileName };
	string pictureName;
	short int leftX, topY , life , speed , shotDeleyTime ,bulletSpeed , bulletDamage ;
	file >> pictureName >> leftX >> topY >> life >> speed >> shotDeleyTime >> bulletSpeed >> bulletDamage;
	playerTank = new Tank{ &hBitmapStorage.standartPlayerTank,RECT{ leftX, topY, leftX + 60, topY + 60 }, static_cast<Directions>(rand() % 4) ,life, speed , shotDeleyTime , bulletSpeed ,bulletDamage  };
	int n;
	file >> n;
	while (n)
	{
		file >> pictureName >> leftX >> topY >> life >> speed >> shotDeleyTime >> bulletSpeed >> bulletDamage;
		n--;
	}
	*/

	playerTank = new Tank{ &hBitmapStorage.standartPlayerTank,RECT{ 0, 0,  60, 60 }, static_cast<Directions>(rand() % 4) };
	enemyTankList.push_back(Tank{ &hBitmapStorage.standartEnemyTank, RECT{ 120, 120, 180, 180 }, static_cast<Directions>(rand() % 4) });
	blockList.push_back(Block{ &hBitmapStorage.brick , RECT{ 240 , 240 , 270 , 270 } , 1 , true , true , true });
}
Map::~Map()
{
	delete playerTank;
	enemyTankList.clear();
	bulletList.clear();
	blockList.clear();
}