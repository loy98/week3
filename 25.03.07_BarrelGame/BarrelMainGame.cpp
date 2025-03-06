#include "pch.h"
#include "BarrelMainGame.h"

BarrelMainGame::BarrelMainGame()
{
}

BarrelMainGame::~BarrelMainGame()
{
}

void BarrelMainGame::Init()
{
}

void BarrelMainGame::Release()
{
}

void BarrelMainGame::Update()
{
}

void BarrelMainGame::Render(HDC hdc)
{
}

LRESULT BarrelMainGame::MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	switch (iMessage)
	{
	case WM_CREATE:
		hTimer = (HANDLE)SetTimer(hWnd, 0, 100, NULL);

		break;
	case WM_TIMER:

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_KEYDOWN:
		break;
	case WM_LBUTTONDOWN:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);

		InvalidateRect(g_hWnd, NULL, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hWnd, &ps);
		wsprintf(szText, TEXT("Mouse X : %d, Y : %d"), mousePosX, mousePosY);
		TextOut(hdc, 20, 60, szText, wcslen(szText));

		EndPaint(g_hWnd, &ps);
		break;
	case WM_DESTROY:
		KillTimer(hWnd, 0);
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}
