#include "Game.h"
#include "RectFunction.h"

Game::Game(string objectFileName, string bitmapFileName, HINSTANCE hInstance)
	: hBitmapStorage(bitmapFileName, hInstance),map(objectFileName, hInstance, hBitmapStorage) 
{}



void Game::playerIntellect()
{
	map.playerTank->appTimeAfterShot();
	switch (playerAction)
	{
	case shotKey:
		if (map.playerTank->shotPossibility())
			map.bulletList.push_back(map.playerTank->shot());
	case nothing:	return;

	default:
		if (map.playerTank->get_direction() == static_cast<Directions>(playerAction))
			break;
		map.playerTank->set_directions(static_cast<Directions>(playerAction));
		break;
	}
	RECT futureLocation(map.playerTank->motion—alculation());
	if (!checkPlayerTankMove(futureLocation))
	{
		map.removeOldImage.push_back(RemoveOldImage{ map.playerTank->tailCalculation() });
		map.playerTank->set_coordinates(futureLocation);
	}
}
void Game::enemyIntellect()
{
	for (auto tank(map.enemyTankList.begin()); tank != map.enemyTankList.end(); tank++)
	{
		tank->appTimeAfterShot();
		if (tank->shotPossibility())
			map.bulletList.push_back(tank->shot());

		RECT futureLocation(tank->motion—alculation());
		if (checkEnemyTankMove(futureLocation, tank))
		{
			auto newDirection(static_cast<Directions>(rand() % AMOUNT_OF_DIRECTIONS)) ;
			tank->set_directions(newDirection);
		}
		else
		{
			map.removeOldImage.push_back(RemoveOldImage{ tank->tailCalculation() });
			tank->set_coordinates(futureLocation);
		}
	}
}

bool Game::checkPlayerTankMove(RECT& futureLocation)
{
	if (insertedRect1InRect2(futureLocation, map.frame))
		return true;
	for (auto block(map.blockList.begin()); block != map.blockList.end(); block++)
		if (block->get_tankReaction() && intersectionRectRect(futureLocation, block->get_coordinates()))
			return true;
	for (auto tank(map.enemyTankList.begin()); tank != map.enemyTankList.end(); tank++)
		if (intersectionRectRect(futureLocation, tank->get_coordinates()))
			return true;
	return false;
}
bool Game::checkEnemyTankMove(RECT& futureLocation, list<Tank>::iterator& currentTank)
{
	if (insertedRect1InRect2(futureLocation, map.frame))
		return true;
	if (intersectionRectRect(futureLocation, map.playerTank->get_coordinates()))
		return true;
	for (auto block(map.blockList.begin()); block != map.blockList.end(); block++)
		if (block->get_tankReaction() && intersectionRectRect(futureLocation, block->get_coordinates()))
			return true;
	for (auto tank(map.enemyTankList.begin()); tank != map.enemyTankList.end(); tank++)
		if (intersectionRectRect(futureLocation, tank->get_coordinates()) && tank != currentTank)
			return true;
	return false;
}

void Game::bulletIntellect()
{
	auto bullet(map.bulletList.begin());
	while (bullet != map.bulletList.end())
	{
		map.removeOldImage.push_back(RemoveOldImage{ bullet->move() }); 
		if (checkBulletContact(bullet))
		{
			map.removeOldImage.push_back(bullet->get_coordinates());
			bullet = map.bulletList.erase(bullet);
		}
		else bullet++;
	}
}
bool Game::checkBulletContact(list<MoveBullet>::iterator& currentBullet)
{
	bool temp(false);
	RECT bulletCoordinates(currentBullet->get_coordinates());
	if (insertedRect1InRect2(bulletCoordinates, map.frame))
		temp = true;
	
	auto block(map.blockList.begin());
	while (block != map.blockList.end())
	{
		if (intersectionRectRect(bulletCoordinates, block->get_coordinates()) && block->get_bulletReaction())
		{
			temp = true;
			if (block->hitting(currentBullet->get_damage()))
			{
				map.removeOldImage.push_back(block->get_coordinates());
				block = map.blockList.erase(block);
			}
			else block++;
		}
		else block++;
	}

	if (intersectionRectRect(bulletCoordinates, map.playerTank->get_coordinates()) && currentBullet->get_allienceTarget())
	{
		temp = true;
		//khhhhhhhhhhh
	}
	if (currentBullet->get_enemyTarget())
	{
		auto tank(map.enemyTankList.begin());
		while (tank != map.enemyTankList.end())
		{
			if (intersectionRectRect(bulletCoordinates, tank->get_coordinates()))
			{
				temp = true;
				if (tank->hitting(currentBullet->get_damage()))
				{
					map.removeOldImage.push_back(tank->get_coordinates());
					tank = map.enemyTankList.erase(tank);
				}
				else tank++;
			}
			else tank++;
		}
	}
	return temp;
}

void Game::moveFunction()
{
	playerIntellect();
	enemyIntellect();
	bulletIntellect();
}