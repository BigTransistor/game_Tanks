#include "Bullet.h"
void Bullet::move()
{
	switch (direction)
	{
	case topDirection:		coordinates.top -= speed;	coordinates.bottom -= speed;	break;
	case rightDirection:	coordinates.left += speed;	coordinates.right += speed;		break;
	case bottomDirection:	coordinates.top += speed;	coordinates.bottom += speed;	break;
	case leftDirection:		coordinates.left -= speed;	coordinates.right -= speed;		break;
	}
}

Bullet::Bullet(BulletType _type, RECT _coordinates, Directions _direction, short int _speed, short int _damage )
	:type(_type), coordinates(_coordinates), direction(_direction), speed(_speed), damage(_damage) 
{
	switch (direction)
	{
	case topDirection:		hBitmap = &type.picture->top;	break;
	case rightDirection:	hBitmap = &type.picture->right;	break;
	case bottomDirection:	hBitmap = &type.picture->bottom;break;
	case leftDirection:		hBitmap = &type.picture->left;	break;
	}
}

Bullet::BulletType::BulletType( bool _enemyTarget , bool _allienceTarget, Picture* _picture)
	: enemyTarget(_enemyTarget), allienceTarget(_allienceTarget), picture(_picture) {}