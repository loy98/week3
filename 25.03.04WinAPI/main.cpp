#include <Windows.h>
#include <string>
#define PI 3.141592
using namespace std;
HINSTANCE g_hInstance; //프로그램 인스턴스 핸들
HWND g_hwnd; //윈도우 핸들
LPCWSTR g_lpszClassName = (LPCWSTR)TEXT("윈도우 API 사용하기"); 

enum class ShapeType : uint8_t
{
	Nemo,
	Star
};

struct BeingStar
{
	POINT _pt;
	ShapeType _type;
	int size;
};

/*
	1. 자동차그리기
	2. 움직이기
	3. 네모 동그라미 그리고 드래그 드랍
	4. 별이되어라! -> 바닥에 네모 10개를 그린다 -> 마우스 드래그를 통해서 위로 이동을 시킨다
				   -> 특정 높이 이상 위치에 드랍을 하면 네모 -> 별 모양으로 바뀐다.
*/
void RenderRect(HDC hdc, int x, int y, int width, int height);
void RenderRectAtCenter(HDC hdc, int centerX, int centerY, int width, int height);
void RenderCircle(HDC hdc, int x, int y, int width, int height);
void RenderCircleAtCenter(HDC hdc, int centerX, int centerY, int width, int height);
void RenderCar(HDC hdc, int x, int y, double degree);
void RenderWheelLine(HDC hdc, int x, int y, double degree);
bool PointInRect(POINT ptMouse, RECT rc);
void UpdateRect(RECT& rc, POINT pt);
void RenderStar(HDC hdc, RECT rc);
void RenderRects(HDC hdc, RECT* rcs);
void RenderSkyLine(HDC hdc);

bool RectInRect(RECT rc1, RECT rc2)
{
	if (rc1.left > rc2.right || rc1.right < rc2.left)
		return false;
	if (rc1.top > rc2.bottom || rc1.bottom < rc2.top)
		return false;
	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdParam, int nCmdShow)
{
	g_hInstance = hInstance;

	//윈도우 생성을 위한 데이터 셋팅
	WNDCLASS wndClass;
	wndClass.cbClsExtra = 0;
	wndClass.cbWndExtra = 0;
	wndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); //배경색
	wndClass.hCursor = LoadCursor(g_hInstance, IDC_ARROW); //커서모양
	wndClass.hIcon = LoadIcon(g_hInstance, IDI_APPLICATION); //아이콘
	wndClass.hInstance = g_hInstance;
	wndClass.lpfnWndProc = WndProc; //함수의 이름은 메모리 주소이다.
	wndClass.lpszClassName = g_lpszClassName; // TEXT("윈도우 API 사용하기"); //위에 뜨는 이름
	wndClass.lpszMenuName = NULL;
	wndClass.style = CS_HREDRAW | CS_VREDRAW; // 상하좌우로 바뀔때 다시그리기

	RegisterClass(&wndClass); //클래스 등록

	g_hwnd = CreateWindow(g_lpszClassName, g_lpszClassName, WS_OVERLAPPEDWINDOW, 
		50, 50, 1080, 720, NULL, NULL, g_hInstance, NULL); // 윈도우 생성 -> 윈도우 핸들 반환

	ShowWindow(g_hwnd, nCmdShow); // 윈도우 띄우기 -> bool 타입을 반환하기 때문에 실행이 잘 됐는지 확인 가능

	MSG message; // 구조체 -> 이벤트 관련된 데이터를 담아준다

	while (GetMessage(&message, 0, 0, 0)) // 누락되는 이벤트가 생기지 않도록 queue에 이벤트를 담아두었다가 순차적으로 실행한다.
	{
		TranslateMessage(&message);
		DispatchMessage(&message);
	}

	return message.wParam; //종료될 때 오류가 있었는지 wParam에 들어감
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam) //LPARAM에 마우스 위치정보가 들어옴
{
	HDC hdc;
	PAINTSTRUCT ps;
	static int mousePosX = 0;
	static int mousePosY = 0;
	static int dan = 1;
	static int carPosX = 300;
	static int carPosY = 400;
	static int posX = 0;
	static int posY = 0;
	static double degree = 90;
	wchar_t szText[128];
	static bool isGrab = false;
	//static RECT rc { 10, 10, 110, 110 };
	static POINT pt;

	static RECT rcs[10];
	static int index;

	static BeingStar stars[10];
	static int selectedIndex = -1;

	static RECT destroyer;
	static bool isDistroyerGrab = false;

	switch (iMessage)
	{
	case WM_CREATE:
		for (int i = 0; i < 10; ++i)
		{
			rcs[i].left = (i + 1) * 80;
			rcs[i].right = rcs[i].left + 60;
			rcs[i].top = 500;
			rcs[i].bottom = rcs[i].top + 60;
		}
		destroyer = { 100, 50, 150, 100 };
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'a': case 'A':
			carPosX -= 20;
			degree -= 15;
			InvalidateRgn(g_hwnd, NULL, true);
			break;
		case 'd': case 'D':
			carPosX += 20;
			degree += 15;
			InvalidateRgn(g_hwnd, NULL, true);
			break;
		case 'w': case 'W':
			carPosY -= 20;
			InvalidateRgn(g_hwnd, NULL, true);
			break;
		case 's': case 'S':
			carPosY += 20;
			InvalidateRgn(g_hwnd, NULL, true);
			break;
		}

	case WM_RBUTTONDOWN:
		//dan++;
		//if (dan > 9)
		//	dan = 9;
		InvalidateRgn(g_hwnd, NULL, false);
		break;
	case WM_MOUSEMOVE:
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);
		if (isGrab)
		{
			UpdateRect(rcs[index], POINT{mousePosX, mousePosY});
		}
		if (isDistroyerGrab)
			UpdateRect(destroyer, POINT{ mousePosX, mousePosY });
		for (int i = 0; i < 10; ++i)
		{
			if (RectInRect(destroyer, rcs[i]))
			{
				rcs[i].left = 0;
				rcs[i].right = 0;
				rcs[i].bottom = 0;
				rcs[i].right = 0;
			}
		}
		//InvalidateRect(g_hwnd, NULL, true);
		InvalidateRgn(g_hwnd, NULL, true);
		break;
	case WM_LBUTTONDOWN:
		//dan--;
		//if (dan < 2)
		//	dan = 2;
		mousePosX = LOWORD(lParam);
		mousePosY = HIWORD(lParam);
		
		pt.x = mousePosX;
		pt.y = mousePosY;
		isDistroyerGrab = PointInRect(pt, destroyer);
		for (int i = 0; i < 10; ++i)
		{
			isGrab = PointInRect(pt, rcs[i]);
			
			if (isGrab) {
				index = i;
				break;
			}
		}
		InvalidateRgn(g_hwnd, NULL, true);
		break;
	case WM_LBUTTONUP:
		isGrab = false;
		isDistroyerGrab = false;
		InvalidateRgn(g_hwnd, NULL, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hwnd, &ps);

		//TextOut(hdc, 100, 100, L"Hello, World", strlen("Hello, World")); //(핸들, x위치, y위치, 문자열, 문자 길이)
		//wsprint(/*문자열 공간*/, /*형태*/, /*값1, 2, 3...*/)
		//wsprintf(szText, TEXT("mousePos {%d, %d}"), mousePosX, mousePosY);
		//TextOut(hdc, 100, 120, szText, wcslen(szText));
		//구구단
		//for (int j = 2; j <= dan; j++)
		//{
		//	for (int i = 1; i < 10; ++i)
		//	{
		//		wsprintf(szText, TEXT("%d * %d = %d"), j, i, j * i);
		//		TextOut(hdc, 100 + 100 * (j - 2), 140 + 20 * i, szText, wcslen(szText));
		//	}
		//}
		
		// 동그라미와 네모를 그려봅시다
		//Rectangle(hdc, 300, 400, 500, 600);
		//RenderCar(hdc, carPosX, carPosY, degree);
		//RenderCircleAtCenter(hdc, posX, posY, 100, 100);
		//Ellipse(hdc, rc.left, rc.top, rc.right, rc.bottom);
		//EndPaint(g_hwnd, &ps);
		RenderSkyLine(hdc);
	   	RenderRects(hdc, rcs);
		RenderRect(hdc, destroyer.left, destroyer.top, 50, 50);
		break;
	case WM_DESTROY: 
		PostQuitMessage(0); // 창을 끄면 프로그램이 종료됨
		break;
	}


	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void RenderRect(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}
void RenderRectAtCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Rectangle(hdc, centerX - width / 2, centerY - height / 2, centerX + width / 2, centerY + height / 2);
}
void RenderCircle(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}
void RenderCircleAtCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Ellipse(hdc, centerX - width / 2, centerY - height / 2, centerX + width / 2, centerY + height / 2);
}
void RenderCar(HDC hdc, int x, int y, double degree)
{
	RenderRect(hdc, x - 50, y - 80, 100, 100);
	RenderRectAtCenter(hdc, x, y, 200, 60);
	RenderCircleAtCenter(hdc, x - 50, y + 30, 50, 50);
	RenderCircleAtCenter(hdc, x + 50, y + 30, 50, 50);
	
	RenderWheelLine(hdc, x - 50, y + 30, degree);
	RenderWheelLine(hdc, x + 50, y + 30, degree);
}
void RenderWheelLine(HDC hdc, int x, int y, double degree)
{
	double rad_1 = degree * PI / 180;
	double rad_2 = (degree + 45) * PI / 180;
	double rad_3 = (degree + 90) * PI / 180;
	double rad_4 = (degree + 135) * PI / 180;

	MoveToEx(hdc, x - 25 * cos(rad_1), y - 25 * sin(rad_1), NULL);
	LineTo(hdc, x + 25 * cos(rad_1), y + 25 * sin(rad_1));
	MoveToEx(hdc, x - 25 * cos(rad_2), y - 25 * sin(rad_2), NULL);
	LineTo(hdc, x + 25 * cos(rad_2), y + 25 * sin(rad_2));
	MoveToEx(hdc, x - 25 * cos(rad_3), y - 25 * sin(rad_3), NULL);
	LineTo(hdc, x + 25 * cos(rad_3), y + 25 * sin(rad_3));
	MoveToEx(hdc, x - 25 * cos(rad_4), y - 25 * sin(rad_4), NULL);
	LineTo(hdc, x + 25 * cos(rad_4), y + 25 * sin(rad_4));
}
bool PointInRect(POINT ptMouse, RECT rc)
{
	if (ptMouse.x < rc.left || ptMouse.x > rc.right)
		return false;
	if (ptMouse.y < rc.top || ptMouse.y > rc.bottom)
		return false;
	return true;
}
void UpdateRect(RECT& rc, POINT pt)
{
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	rc.left = pt.x - width / 2;
	rc.right = pt.x + width / 2;
	rc.top = pt.y - height / 2;
	rc.bottom = pt.y + height / 2;
}
void RenderStar(HDC hdc, RECT rc)
{
	
	MoveToEx(hdc, rc.left, rc.top + 20, NULL);
	LineTo(hdc, rc.right, rc.top + 20);
	LineTo(hdc, rc.left + 12, rc.bottom);
	LineTo(hdc, rc.left + 30, rc.top);
	LineTo(hdc, rc.right - 12, rc.bottom);
	LineTo(hdc, rc.left, rc.top + 20);

	
}
void RenderRects(HDC hdc, RECT* rcs)
{
	for (int i = 0; i < 10; ++i)
	{
		if (rcs[i].left == rcs[i].right && rcs[i].top == rcs[i].bottom)
			continue;
		else if (rcs[i].top < 100)
			RenderStar(hdc, rcs[i]);
		else
			Rectangle(hdc, rcs[i].left, rcs[i].top, rcs[i].right, rcs[i].bottom);
	}
}
void RenderSkyLine(HDC hdc)
{
	MoveToEx(hdc, 0, 130, NULL);
	LineTo(hdc, 1080, 130);
}