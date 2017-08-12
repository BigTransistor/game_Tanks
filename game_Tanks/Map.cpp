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
	ifstream file{ objectFileName };
	if (!file) { PostQuitMessage(0); return; }
	string pictureName , bulletPictureName;
	short int leftX, topY, life, speed, shotDeleyTime, bulletSpeed, bulletDamage, size , n ;
	bool bulletReaction , destroyedByBullet , tankReaction , enemyTarget , allienceTarget;
	Picture4Directions *tankPicture , *bulletPicture;
	Picture1Directions* blockPicture;

	file >> pictureName >> leftX >> topY >> life >> speed >> shotDeleyTime >> bulletSpeed >> bulletDamage >> bulletPictureName >> enemyTarget >> allienceTarget;
	tankPicture = &hBitmapStorage.moveObjectPictureMass.find(pictureName)->second;
	bulletPicture = &hBitmapStorage.moveObjectPictureMass.find(bulletPictureName)->second;

	playerTank = new Tank{	tankPicture ,RECT{ leftX, topY, leftX + tankPicture->length  , topY + tankPicture->height }, static_cast<Directions>(rand() % 4), 
							StaticBullet{ bulletPicture , enemyTarget, allienceTarget,  bulletSpeed, bulletDamage = 1 } ,life, speed , shotDeleyTime			};
	file >> n;
	while (n--)
	{
		file >> pictureName >> leftX >> topY >> life >> speed >> shotDeleyTime >> bulletSpeed >> bulletDamage >>  bulletPictureName  >> enemyTarget >> allienceTarget;
		tankPicture = &hBitmapStorage.moveObjectPictureMass.find(pictureName)->second;
		bulletPicture = &hBitmapStorage.moveObjectPictureMass.find(bulletPictureName)->second;
		enemyTankList.push_back(Tank{	tankPicture ,RECT{ leftX, topY, leftX + tankPicture->length  , topY + tankPicture->height }, static_cast<Directions>(rand() % 4) ,
										StaticBullet{ bulletPicture , enemyTarget, allienceTarget,  bulletSpeed, bulletDamage = 1} ,life, speed , shotDeleyTime				});
		//StaticBullet( Picture4Directions* _picture, bool _enemyTarget, bool _allienceTarget, short int _speed, short int damage = 1);
	}
	file >> n;
	while (n--)
	{
		file >> pictureName >> leftX >> topY >> life >> size >> bulletReaction >> destroyedByBullet >> tankReaction;
		blockPicture = &hBitmapStorage.blockPictureMass.find(pictureName)->second;
		blockList.push_back(Block{ &blockPicture->picture ,RECT{ leftX, topY, leftX + blockPicture->length  , topY + blockPicture->height },
									 life ,bulletReaction ,destroyedByBullet , tankReaction													});
	}
}
Map::~Map()
{
	delete playerTank;
	enemyTankList.clear();
	bulletList.clear();
	blockList.clear();
}