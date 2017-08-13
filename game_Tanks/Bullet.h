#pragma once
#include <windows.h>
#include"Picture.h"
enum Directions { topDirection, rightDirection, bottomDirection, leftDirection};
#define AMOUNT_OF_DIRECTIONS 4

class Picture4Directions;

class StaticBullet
{
protected:
	Picture4Directions *picture;
	bool enemyTarget;
	bool allienceTarget;
	short int speed;
	short int damage;
public:
	Picture4Directions* get_picture() { return picture; }
	short int get_damage() { return damage; }
	bool get_enemyTarget() { return enemyTarget; }
	bool get_allienceTarget() { return allienceTarget; }

	StaticBullet( Picture4Directions* _picture, bool _enemyTarget, bool _allienceTarget, short int _speed, short int damage = 1);
};

class MoveBullet : public StaticBullet
{
protected:
	HBITMAP * hBitmap;
	RECT coordinates;
	Directions direction;
public:
	RECT move();
	HBITMAP* get_hBitmap() { return hBitmap; }
	RECT get_coordinates() { return coordinates; }
	MoveBullet( StaticBullet bulletInfo , RECT _coordinates , Directions _direction );
};