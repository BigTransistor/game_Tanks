#pragma once
#include <windows.h>
#include"Picture.h"
#include <iostream>
#include <map>
using namespace std;
class Game;
class Map;

class HBitmapStorage
{
friend Game;
friend Map;
public:
	map<string, Picture4Directions> moveObjectPictureMass;
	map<string, Picture1Directions> blockPictureMass;
	HBitmapStorage(string bitmapHileName, HINSTANCE& hInstance);
	~HBitmapStorage() { moveObjectPictureMass.clear(); blockPictureMass.clear(); }
};