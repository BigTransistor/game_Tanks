#include "HBitmapStorage.h"
#include <fstream>
#include <string>
using namespace std;

HBitmapStorage::HBitmapStorage(string bitmapFileName, HINSTANCE& hInstance)
{
	ifstream file{ bitmapFileName };
	
	string name, adress;
	short int length, height, n;
	file >> n;
	while (n--)
	{
		file >> name >> adress >> length >> height;
		moveObjectPictureMass.insert(pair<string, Picture4Directions>(name, Picture4Directions(adress, hInstance, length, height)));
	}
	file >> n;
	while (n--)
	{
		file >> name >> adress >> length >> height;
		blockPictureMass.insert(pair<string, Picture1Directions>(name, Picture1Directions(adress, hInstance, length, height)));
	}
};