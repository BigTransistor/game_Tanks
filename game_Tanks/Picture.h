#pragma once
#include <windows.h>
#include <iostream>
using namespace std;
class Picture
{
public:
	short int length, height;
	HBITMAP top, right, bottom, left;

	
	Picture(string adress,HINSTANCE hInstance, short int _length, short int _height): length(_length) , height(_height),
		top(static_cast<HBITMAP>(LoadImage(hInstance, (adress + "Top.bmp").c_str() , IMAGE_BITMAP, length, height, LR_LOADFROMFILE))),
		right (static_cast<HBITMAP>(LoadImage(hInstance, (adress + "Right.bmp").c_str(), IMAGE_BITMAP, height, length, LR_LOADFROMFILE))) ,
		bottom (static_cast<HBITMAP>(LoadImage(hInstance, (adress + "Bottom.bmp").c_str(), IMAGE_BITMAP, length, height, LR_LOADFROMFILE))) ,
		left ( static_cast<HBITMAP>(LoadImage(hInstance, (adress + "Left.bmp").c_str(), IMAGE_BITMAP, height, length, LR_LOADFROMFILE)))
	{}
};