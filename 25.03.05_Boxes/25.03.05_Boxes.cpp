#include <Windows.h>
#include <iostream>
using namespace std;
HINSTANCE g_hInstance; //프로그램 인스턴스 핸들
HWND g_hwnd; //윈도우 핸들
LPCWSTR g_lpszClassName = (LPCWSTR)TEXT("윈도우 API 사용하기");

void RenderRectAtCenter(HDC hdc, int centerX, int centerY, int width, int height);

bool RectHaveRect(RECT rc1, RECT rc2)
{
	if (rc1.left > rc2.left) return false;
	if (rc1.right < rc2.right) return false;
	if (rc1.top > rc2.top) return false;
	if (rc1.bottom < rc2.bottom) return false;

	return true;
}
bool RectInRect(RECT rc1, RECT rc2)
{
	if (rc1.left > rc2.right || rc1.right < rc2.left)
		return false;
	if (rc1.top > rc2.bottom || rc1.bottom < rc2.top)
		return false;
	return true;
}

enum class BoxType : uint8_t
{
	None,
	Big,
	Small
};
struct Box {
	POINT _pt;
	RECT _rc;
	BoxType _type = BoxType::None;
	int _size = 0;
	bool _canMove = false;
};
void UpdateBoxRc(Box& box);
void UpdateActiveIndex(Box boxes[2], Box& smallBox, int& activeIndex);
/*
	1. 자동차그리기
	2. 움직이기
	3. 네모 동그라미 그리고 드래그 드랍
	4. 별이되어라! -> 바닥에 네모 10개를 그린다 -> 마우스 드래그를 통해서 위로 이동을 시킨다
				   -> 특정 높이 이상 위치에 드랍을 하면 네모 -> 별 모양으로 바뀐다.
*/

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
	static Box boxes[2];
	static Box smallBox;
	static int activeIndex = 0;
	switch (iMessage)
	{
	case WM_CREATE:
		for (int i = 0; i < 2; ++i)
		{
			boxes[i]._type = BoxType::Big;
			boxes[i]._size = 200;
			boxes[i]._pt.x = 200 + 250 * i;
			boxes[i]._pt.y = 200;
		}
		smallBox._type = BoxType::Small;
		smallBox._size = 50;
		smallBox._pt.x = boxes[0]._pt.x;
		smallBox._pt.y = boxes[0]._pt.y;
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 'A': case 'a':
			boxes[activeIndex]._pt.x -= 5;
			for (int i = 0; i < 2; ++i)
				UpdateBoxRc(boxes[i]);
			UpdateBoxRc(smallBox);

			UpdateActiveIndex(boxes, smallBox, activeIndex);
			break;
		case 'D': case 'd':
			boxes[activeIndex]._pt.x += 5;
			for (int i = 0; i < 2; ++i)
				UpdateBoxRc(boxes[i]);
			UpdateBoxRc(smallBox);

			UpdateActiveIndex(boxes, smallBox, activeIndex);
			break;
		case 'W': case 'w':
			boxes[activeIndex]._pt.y -= 5;
			for (int i = 0; i < 2; ++i)
				UpdateBoxRc(boxes[i]);
			UpdateBoxRc(smallBox);

			UpdateActiveIndex(boxes, smallBox, activeIndex);
			break;
		case 'S': case 's':
			boxes[activeIndex]._pt.y += 5;
			for (int i = 0; i < 2; ++i)
				UpdateBoxRc(boxes[i]);
			UpdateBoxRc(smallBox);

			UpdateActiveIndex(boxes, smallBox, activeIndex);
			break;
		}
		InvalidateRgn(g_hwnd, NULL, true);
		break;
	case WM_PAINT:
		hdc = BeginPaint(g_hwnd, &ps);

		for (int i = 0; i < 2; ++i)
			RenderRectAtCenter(hdc, boxes[i]._pt.x, boxes[i]._pt.y, boxes[i]._size, boxes[i]._size);
		RenderRectAtCenter(hdc, smallBox._pt.x, smallBox._pt.y, smallBox._size, smallBox._size);
		break;
	case WM_DESTROY:
		PostQuitMessage(0); // 창을 끄면 프로그램이 종료됨
		break;
	}
	return DefWindowProc(hWnd, iMessage, wParam, lParam);
}

void RenderRectAtCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Rectangle(hdc, centerX - width / 2, centerY - height / 2, centerX + width / 2, centerY + height / 2);
}
void UpdateBoxRc(Box& box)
{
	box._rc.left = box._pt.x - box._size / 2;
	box._rc.top = box._pt.y - box._size / 2;
	box._rc.right = box._pt.x + box._size / 2;
	box._rc.bottom = box._pt.y + box._size / 2;
	
}

void UpdateActiveIndex(Box boxes[2], Box& smallBox, int& activeIndex) {
	
	int otherIndex = (activeIndex + 1) % 2;
	if (!RectHaveRect(boxes[activeIndex]._rc, smallBox._rc)) {
		if (!RectInRect(boxes[activeIndex]._rc, boxes[otherIndex]._rc))
		{
			if (smallBox._rc.left <= boxes[activeIndex]._rc.left)
				smallBox._pt.x = boxes[activeIndex]._rc.left + smallBox._size / 2;
			if (smallBox._rc.right >= boxes[activeIndex]._rc.right)
				smallBox._pt.x = boxes[activeIndex]._rc.right - smallBox._size / 2;
			if (smallBox._rc.top <= boxes[activeIndex]._rc.top)
				smallBox._pt.y = boxes[activeIndex]._rc.top + smallBox._size / 2;
			if (smallBox._rc.bottom >= boxes[activeIndex]._rc.bottom)
				smallBox._pt.y = boxes[activeIndex]._rc.bottom - smallBox._size / 2;
		}
	}

	// 두 상자 간 충돌 체크
	if (RectInRect(boxes[activeIndex]._rc, boxes[otherIndex]._rc)) {
		// 충돌 시, 작은 상자의 좌표를 다른 상자로 옮기고 제어권 전환
		smallBox._pt.x = boxes[otherIndex]._pt.x;
		smallBox._pt.y = boxes[otherIndex]._pt.y; // 필요하면 y 좌표도 업데이트
		activeIndex = otherIndex;
	}
}