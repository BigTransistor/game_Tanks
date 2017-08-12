#pragma once
#include <windows.h>
#include "Bullet.h"

class Tank
{
protected:
	Picture4Directions *picture;
	HBITMAP *hBitmap;
	RECT coordinates;
	Directions direction;
	short int speed;
	short int life;
	short int shotDelayTime;
	short int timeAfterShot;
	StaticBullet bulletInfo;
public:
	Tank& set_directions(Directions _directions);
	Tank& set_coordinates(RECT _coordinates) { coordinates = _coordinates; return *this;}
	Tank& set_hBitmap(HBITMAP *_hBitmap) { hBitmap = _hBitmap; return *this;}
	Tank& appTimeAfterShot() { timeAfterShot++; return *this; }
	Directions get_direction() { return direction; }
	RECT get_coordinates() { return coordinates; }
	HBITMAP* get_hBitmap() { return hBitmap; }
	bool Tank::shotPossibility() { return shotDelayTime <= timeAfterShot; }

	RECT motionÑalculation();
	MoveBullet shot();
	bool hitting(short int damage);

	Tank(Picture4Directions* _picture, RECT _coordinates, Directions _direction, StaticBullet _bulletInfo, short int _life = 1, short int _speed = 10,short int _shotDelayTime = 100);	
};