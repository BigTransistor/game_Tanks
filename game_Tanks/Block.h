#pragma once
#include <windows.h>
class Block
{
protected:
	HBITMAP* hBitmap;
	RECT coordinates;
	short int life;
	bool bulletReaction;
	bool destroyedByBullet;
	bool tankReaction;
public:
	HBITMAP* get_hBitmap() { return hBitmap; }
	RECT get_coordinates() { return coordinates; }
	bool get_bulletReaction() { return bulletReaction; }
	bool get_tankReaction() { return tankReaction; }
	bool hitting(short int damage) { return destroyedByBullet ? (life -= damage) <= 0 : false; }
	Block(HBITMAP* _hBitmap ,RECT _coordinates ,short int _life  ,bool _bulletReaction , bool _destroyedByBullet , bool _tankReaction):
		coordinates(_coordinates), life(_life) , hBitmap(_hBitmap) , bulletReaction(_bulletReaction) , 
		destroyedByBullet(_destroyedByBullet) , tankReaction(_tankReaction) {}
};