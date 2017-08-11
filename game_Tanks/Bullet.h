#pragma once
#include <windows.h>
#include"Picture.h"
enum Directions { topDirection, rightDirection, bottomDirection, leftDirection};
#define AMOUNT_OF_DIRECTIONS 4

class Picture;
class Bullet
{
public:
	class BulletType
	{
	public:
		Picture *picture;
		bool enemyTarget;
		bool allienceTarget;

		BulletType(bool _enemyTarget, bool _allienceTarget, Picture* _picture);
	};
protected:
	HBITMAP * hBitmap;
	RECT coordinates;
	Directions direction;
	short int speed;
	short int damage;
	BulletType type;
public:
	RECT get_coordinates() { return coordinates; }
	HBITMAP* get_hBitmap() { return hBitmap; }
	short int get_damage() { return damage; }
	BulletType get_type() { return type; }

	void move();
	Bullet(BulletType _type, RECT _coordinates, Directions _direction, short int _speed, short int damage = 1);
};