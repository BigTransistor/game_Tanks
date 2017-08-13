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
		case 0x57:	game->set_playerAction(topKey);		return 0;//������ ����������� ����� �����
		case 0x44:	game->set_playerAction(rightKey);	return 0;//������ ����������� ����� �����
		case 0x53:	game->set_playerAction(bottomKey);	return 0;//������ ����������� ����� �����
		case 0x41:	game->set_playerAction(leftKey);	return 0;//������ ����������� ����� �����
		case VK_SPACE:	game->set_playerAction(shotKey);	
			return 0;//������� �� ������
		default:	 return DefWindowProc(hWnd, message, wParam, lParam);
		}
	case WM_KEYUP:	
 		switch (wParam)
		{
		case 0x57:	if (game->get_playerAction() == topKey)	game->set_playerAction(nothing);	return 0;//������ ����������� ����� �����
		case 0x44:	if (game->get_playerAction() == rightKey)	game->set_playerAction(nothing);	return 0;//������ ����������� ����� �����
		case 0x53:	if (game->get_playerAction() == bottomKey)	game->set_playerAction(nothing);	return 0;//������ ����������� ����� �����
		case 0x41:	if (game->get_playerAction() == leftKey)	game->set_playerAction(nothing);	return 0;//������ ����������� ����� �����
		case VK_SPACE:	if (game->get_playerAction() == shotKey)	game->set_playerAction(nothing);	return 0;//������� �� ������
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
		"gameWndClass",												//��� ������
		"Game",														//��������� ����
		WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX,	//����� ����
		100,														//��������� ���� �� ������ �� �
		100,														//��������� �� �
		static_cast<int>(game->map.get_length()) + 16,								//������
		static_cast<int>(game->map.get_height()) + 38,								//������
		NULL,														//������������� ������������� ����
		NULL,														//������������� ����
		hInstance,													//������������� ���������� ���������
		NULL														//���������� �������������� ����������
	);
	ShowWindow(gameWindow, SW_SHOW);				//������� ���� �� ������ �� �����
	UpdateWindow(gameWindow);						//������� ���������� ����
	SetTimer(gameWindow, 1, 20, NULL);

	MSG messge_code;
	while (GetMessage(&messge_code, NULL, 0, 0))	//�������� ��������� �� �������
	{
		TranslateMessage(&messge_code);				//����������� ��������� ������ � �������
		DispatchMessage(&messge_code);				//������� ��������� ��������������� ������� ����(Function_WNDCLASS_Game)
	}
	UnregisterClass("gameWndClass", hInstance);
	delete game;
	return(messge_code.wParam);
}


