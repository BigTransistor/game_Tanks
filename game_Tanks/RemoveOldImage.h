#pragma once
#include<windows.h>
class RemoveOldImage
{
protected:
	RECT coord;
public:
	RECT get_coord() { return coord; }
	void draw(HDC &hDc) { FillRect(hDc, &coord, CreateSolidBrush(RGB(0, 0, 0))); };
	RemoveOldImage(RECT _coord) :coord(_coord) {}
};