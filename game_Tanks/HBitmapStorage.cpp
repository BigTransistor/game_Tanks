#include "HBitmapStorage.h"
HBitmapStorage::HBitmapStorage(string bitmapHileName, HINSTANCE& hInstance)
	:standartPlayerTank{ "data\\StandartPicture\\Player_Tank_",hInstance , 60, 60 },
	standartPlayerBullet{ "data\\StandartPicture\\Player_Bullet_", hInstance ,12 , 18 },
	standartEnemyTank{ "data\\StandartPicture\\Enemy_Tank_" , hInstance , 60 , 60 }
{
	brick = static_cast<HBITMAP>(LoadImage(hInstance, "data\\StandartPicture\\Brick.bmp", IMAGE_BITMAP, 30, 30, LR_LOADFROMFILE));
};