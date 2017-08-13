#include "Tank.h"
#define GAME_SIZE_CONST 10
RECT Tank::motionÑalculation()
{
	RECT futureLocation(coordinates);
	switch (direction)
	{
	case topDirection:	futureLocation.top -= speed;	futureLocation.bottom -= speed;	break;
	case rightDirection:	futureLocation.left += speed;	futureLocation.right += speed;	break;
	case bottomDirection:futureLocation.top += speed;	futureLocation.bottom += speed;	break;
	case leftDirection:	futureLocation.left -= speed;	futureLocation.right -= speed;	break;
	}
	return futureLocation;
}
bool Tank::hitting(short int damage)
{
	life -= damage;
	return life > 0 ? false : true;
}


Tank& Tank::set_directions(Directions _directions) 
{
	if(direction == _directions)
		return *this;
	direction = _directions;
	switch (direction)
	{
	case topDirection:	set_hBitmap(&picture->top); break;
	case rightDirection:	set_hBitmap(&picture->right); break;
	case bottomDirection:set_hBitmap(&picture->bottom); break;
	case leftDirection:	set_hBitmap(&picture->left); break;
	}
	return *this;
}

MoveBullet Tank::shot()
{
	timeAfterShot = 0;
	RECT bulletCoordinates;
	switch (direction)
	{
	case topDirection:
		bulletCoordinates.left = (coordinates.right + coordinates.left - bulletInfo.get_picture()->length ) / 2;
		bulletCoordinates.top = coordinates.top - bulletInfo.get_picture()->height;
		bulletCoordinates.right = (coordinates.right + coordinates.left + bulletInfo.get_picture()->length ) / 2;
		bulletCoordinates.bottom = coordinates.top;
		break;
	case rightDirection:
		bulletCoordinates.left = coordinates.right;
		bulletCoordinates.top = (coordinates.top + coordinates.bottom - bulletInfo.get_picture()->length) / 2;
		bulletCoordinates.right = coordinates.right + bulletInfo.get_picture()->height;
		bulletCoordinates.bottom = (coordinates.top + coordinates.bottom + bulletInfo.get_picture()->length) / 2;
		break;
	case bottomDirection:
		bulletCoordinates.left = (coordinates.right + coordinates.left - bulletInfo.get_picture()->length) / 2 ;
		bulletCoordinates.top = coordinates.bottom;
		bulletCoordinates.right = (coordinates.right + coordinates.left + bulletInfo.get_picture()->length) / 2;
		bulletCoordinates.bottom = coordinates.bottom + bulletInfo.get_picture()->height;
		break;
	case leftDirection:
		bulletCoordinates.left = coordinates.left - bulletInfo.get_picture()->height;
		bulletCoordinates.top = (coordinates.top + coordinates.bottom - bulletInfo.get_picture()->length) / 2;
		bulletCoordinates.right = coordinates.left;
		bulletCoordinates.bottom = (coordinates.top + coordinates.bottom + bulletInfo.get_picture()->length) / 2;
		break;
	}
	return MoveBullet(bulletInfo, bulletCoordinates, direction);
}
Tank::Tank(	Picture4Directions* _picture, RECT _coordinates, Directions _direction, StaticBullet _bulletInfo ,short int _life , short int _speed ,short int _shotDelayTime )
	:picture(_picture), coordinates(_coordinates), direction(_direction), speed(_speed), life(_life) , shotDelayTime(_shotDelayTime),bulletInfo(_bulletInfo)
{
	timeAfterShot = rand() % _shotDelayTime;
	switch (direction)
	{
	case topDirection:	hBitmap = &picture->top;	break;
	case rightDirection:	hBitmap = &picture->right;	break;
	case bottomDirection:hBitmap = &picture->bottom; break;
	case leftDirection:	hBitmap = &picture->left;	break;
	}
}

RECT Tank::tailCalculation()
{
	RECT tail(coordinates);
	switch (direction)
	{
	case topDirection:	tail.top = tail.bottom - speed;  break;
	case rightDirection:	tail.right = tail.left + speed;  break;
	case bottomDirection: tail.bottom = tail.top + speed;  break;
	case leftDirection:	tail.left = tail.right - speed;  break;
	}
	return tail;
}