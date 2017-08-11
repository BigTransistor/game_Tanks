#pragma once
#include <windows.h>
#include "Bullet.h"

class Tank
{
protected:
	Picture *picture;
	HBITMAP *hBitmap;
	RECT coordinates;
	Directions direction;
	short int speed;
	short int life;
	struct ShotInfo
	{
		short int shotDelayTime;
		short int timeAfterShot;
		short int bulletSpeed;
		short int bulletDamage;
	}shotInfo;
public:
	Tank& set_directions(Directions _directions);
	Tank& set_coordinates(RECT _coordinates) { coordinates = _coordinates; return *this;}
	Tank& set_hBitmap(HBITMAP *_hBitmap) { hBitmap = _hBitmap; return *this;}
	Tank& appTimeAfterShot() { shotInfo.timeAfterShot++; return *this; }
	Directions get_direction() { return direction; }
	RECT get_coordinates() { return coordinates; }
	HBITMAP* get_hBitmap() { return hBitmap; }

	RECT motion—alculation();
	bool shotPossibility();
	Bullet shot(Bullet::BulletType bulletType);
	bool hitting(short int damage);

	Tank(Picture* _picture, RECT _coordinates, Directions _direction, short int _life = 1, short int _speed = 10,
		short int _shotDelayTime = 100, short int _bulletSpeed = 20, short int _bulletDamage = 1);
};