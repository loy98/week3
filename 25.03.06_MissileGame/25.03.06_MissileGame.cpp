#include "pch.h"
#include "MainGame.h"
HINSTANCE g_hInstance; //프로그램 인스턴스 핸들
HWND g_hWnd;
LPCWSTR g_lpszClassName = (LPCWSTR)TEXT("윈도우 API 사용하기");
MainGame g_mainGame;

/*
	실습 1. 플레이어(좌측)와 적(우측)을 하나씩 만든다.
	플레이어는 w,s키로 상하 이동이 가능하다.
	적은 자동으로 상하로 이동

	실습 2. 마우스 왼쪽 버튼을 누르면 미사일을 발사
	적도 랜덤 타이밍에 미사일을 발사

	실습 3. 각자 미사일에 맞으면 사라진다...
	적에게 맞거나 화면 밖으로 사라지면 재장전
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

	g_hWnd = CreateWindow(g_lpszClassName, g_lpszClassName, WS_OVERLAPPEDWINDOW,
		50, 50, 1080, 720, NULL, NULL, g_hInstance, NULL); // 윈도우 생성 -> 윈도우 핸들 반환

	ShowWindow(g_hWnd, nCmdShow); // 윈도우 띄우기 -> bool 타입을 반환하기 때문에 실행이 잘 됐는지 확인 가능

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
	return g_mainGame.MainProc(hWnd, iMessage, wParam, lParam);
}
