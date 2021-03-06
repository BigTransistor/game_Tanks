#include "Bullet.h"

StaticBullet::StaticBullet(Picture4Directions* _picture, bool _enemyTarget, bool _allienceTarget, short int _speed, short int _damage )
	: picture(_picture), enemyTarget(_enemyTarget) , allienceTarget(_allienceTarget) , speed(_speed), damage(_damage){}

MoveBullet::MoveBullet(StaticBullet bulletInfo, RECT _coordinates, Directions _direction): 
	StaticBullet(bulletInfo) , coordinates(_coordinates) , direction(_direction)
{
	switch (direction)
	{
	case topDirection:		hBitmap = &picture->top;	break;
	case rightDirection:	hBitmap = &picture->right;	break;
	case bottomDirection:	hBitmap = &picture->bottom; break;
	case leftDirection:		hBitmap = &picture->left;	break;
	}
}
RECT MoveBullet::move()
{
	RECT tail(coordinates);
	switch (direction)
	{
	case topDirection:		coordinates.top -= speed;	coordinates.bottom -= speed;	tail.top = tail.bottom - speed; break;
	case rightDirection:	coordinates.left += speed;	coordinates.right += speed;		tail.right = tail.left + speed; break;
	case bottomDirection:	coordinates.top += speed;	coordinates.bottom += speed;	tail.bottom = tail.top + speed; break;
	case leftDirection:		coordinates.left -= speed;	coordinates.right -= speed;		tail.left = tail.right - speed; break;
	}
	return tail;
}