#include <windows.h>
#include "Game.h"
Game* game;

LRESULT CALLBACK gameFunction(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_TIMER:
		game->moveFunction();
	case WM_PAINT:
		game->map.render(hWnd);
		return 0;
		
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 0x57:	game->set_playerAction(topKey);		return 0;//меняем направление моего танка
		case 0x44:	game->set_playerAction(rightKey);	return 0;//меняем направление моего танка
		case 0x53:	game->set_playerAction(bottomKey);	return 0;//меняем направление моего танка
		case 0x41:	game->set_playerAction(leftKey);	return 0;//меняем направление моего танка
		case VK_SPACE:	game->set_playerAction(shotKey);	
			return 0;//выстрел на пробел
		default:	 return DefWindowProc(hWnd, message, wParam, lParam);
		}
	case WM_KEYUP:	
 		switch (wParam)
		{
		case 0x57:	if (game->get_playerAction() == topKey)	game->set_playerAction(nothing);	return 0;//меняем направление моего танка
		case 0x44:	if (game->get_playerAction() == rightKey)	game->set_playerAction(nothing);	return 0;//меняем направление моего танка
		case 0x53:	if (game->get_playerAction() == bottomKey)	game->set_playerAction(nothing);	return 0;//меняем направление моего танка
		case 0x41:	if (game->get_playerAction() == leftKey)	game->set_playerAction(nothing);	return 0;//меняем направление моего танка
		case VK_SPACE:	if (game->get_playerAction() == shotKey)	game->set_playerAction(nothing);	return 0;//выстрел на пробел
		default:	 return DefWindowProc(hWnd, message, wParam, lParam);
		}

	case WM_DESTROY:
		PostQuitMessage(1);
		return 0;
		
	default: return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

int WINAPI	WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int)
{
	game = new Game( "data\\Level_1\\map.txt" , "data\\Level_1\\objectBitmaps.txt" , hInstance);


	WNDCLASS gameWndClass = { NULL , gameFunction , NULL , NULL , hInstance ,NULL,NULL,CreateSolidBrush(RGB(0, 0, 0)),NULL,"gameWndClass" };
	RegisterClass(&gameWndClass);
	game->map.get_length();
	HWND gameWindow = CreateWindow
	(
		"gameWndClass",												//Имя класса
		"Game",														//Заголовок окна
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,	//Стиль окна
		100,														//положение окна на экране по х
		100,														//положение по у
		static_cast<int>(game->map.get_length()) + 16,								//ширина
		static_cast<int>(game->map.get_height()) + 38,								//высота
		NULL,														//идентификатор родительского окна
		NULL,														//идентификатор меню
		hInstance,													//идентификатор экземпляра программы
		NULL														//отсутствие дополнительных параметров
	);
	ShowWindow(gameWindow, SW_SHOW);				//Выводим окно из памяти на экран
	UpdateWindow(gameWindow);						//Обновим содержимое окна
	SetTimer(gameWindow, 1, 20, NULL);

	MSG messge_code;
	while (GetMessage(&messge_code, NULL, 0, 0))	//Получаем сообщение из очереди
	{
		TranslateMessage(&messge_code);				//Преобразует сообщения клавиш в символы
		DispatchMessage(&messge_code);				//Передаёт сообщение соответствующей функции окна(Function_WNDCLASS_Game)
	}
	UnregisterClass("gameWndClass", hInstance);
	delete game;
	return(messge_code.wParam);
}


