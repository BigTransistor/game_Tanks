#pragma once
#include"Map.h"
#include"HBitmapStorage.h"
#include <fstream>
#include <string>
using namespace std;
enum PlayerAction { topKey, rightKey, bottomKey, leftKey, shotKey, nothing};
class Game
{
protected:
	HBitmapStorage hBitmapStorage;
	PlayerAction playerAction;
	void enemyIntellect();
		bool checkEnemyTankMove(RECT& , list<Tank>::iterator& );
	void playerIntellect();
		bool checkPlayerTankMove(RECT&);
	void bulletIntellect();
		bool checkBulletContact(list<Bullet>::iterator& );
	
	void endGame(bool);
public:
	Map map;
	void moveFunction();
	Game& set_playerAction(PlayerAction _playerAction) { playerAction = _playerAction; return *this; }
	PlayerAction get_playerAction() { return playerAction; }
	Game(string objectFileName, string bitmapFileName, HINSTANCE hInstance);
};