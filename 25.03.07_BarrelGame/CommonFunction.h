#pragma once
#include "pch.h"
inline RECT GetRect(int left, int top, int width, int height)
{
	RECT rc{ left, top, left + width, top + height };
	return rc;
}

inline RECT GetRectAtCenter(int x, int y, int width, int height)
{
	RECT rc{ x - (width / 2), y - (height / 2),
		x + (width / 2), y + (height / 2) };
	return rc;
}

inline void RenderStar(HDC hdc, int posX, int posY)
{
	MoveToEx(hdc, posX + 60, posY + 20, NULL);
	LineTo(hdc, posX - 60, posY + 20);
	LineTo(hdc, posX + 40, posY - 60);
	LineTo(hdc, posX, posY + 60);
	LineTo(hdc, posX - 40, posY - 60);
	LineTo(hdc, posX + 60, posY + 20);
}

// �»�� ����
inline void RenderRect(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

// ��� ����
inline void RenderRectAtCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Rectangle(hdc, centerX - (width / 2), centerY - (height / 2),
		centerX + (width / 2), centerY + (height / 2));
}

// �»�� ����
inline void RenderEllipse(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

// ��� ����
inline void RenderEllipseAtCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Ellipse(hdc, centerX - (width / 2), centerY - (height / 2),
		centerX + (width / 2), centerY + (height / 2));
}

inline bool PointInRect(POINT ptMouse, RECT rc)
{
	if (ptMouse.x < rc.left || ptMouse.x > rc.right
		|| ptMouse.y < rc.top || ptMouse.y > rc.bottom)
	{
		return false;
	}
	return true;
}

inline bool RectInRect(RECT rc1, RECT rc2)
{
	if (rc1.right < rc2.left || rc1.left > rc2.right
		|| rc1.top > rc2.bottom || rc1.bottom < rc2.top)
	{
		return false;
	}
	return true;
}

inline void UpdateRect(RECT& rc, POINT pt)
{
	int width = rc.right - rc.left;
	int height = rc.bottom - rc.top;

	rc.left = pt.x - (width / 2);
	rc.right = rc.left + width;
	rc.top = pt.y - (height / 2);
	rc.bottom = rc.top + height;
}
