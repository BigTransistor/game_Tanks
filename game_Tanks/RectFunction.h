#pragma once
#include <windows.h>
bool insertedRect1InRect2(RECT &rect1, RECT &rect2)
{
	return	(	(rect1.left		< rect2.left)	||
				(rect1.top		< rect2.top)	||
				(rect1.bottom	> rect2.bottom) ||
				(rect1.right	> rect2.right)		);
}
bool intersectionRectRect(RECT &rect1, RECT &rect2)
{
	return !(	(rect1.left		>= rect2.right) ||
				(rect1.top		>= rect2.bottom)||
				(rect1.bottom	<= rect2.top)	||
				(rect1.right	<= rect2.left)		);
}