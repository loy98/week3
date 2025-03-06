#include "pch.h"

bool RectInRect(RECT rc1, RECT rc2)
{
	if (rc1.left > rc2.right || rc1.right < rc2.left)
		return false;
	if (rc1.top > rc2.bottom || rc1.bottom < rc2.top)
		return false;
	return true;
}
void RenderRectAtCenter(HDC hdc, int centerX, int centerY, int width, int height)
{
	Rectangle(hdc, centerX - width / 2, centerY - height / 2, centerX + width / 2, centerY + height / 2);
}

void Missile::Draw(HDC hdc)
{
	if (!canUse)
		RenderRectAtCenter(hdc, _pt.x, _pt.y, _size, _size);
}

void Unit::Draw(HDC hdc)
{
	if (!isDead)
		RenderRectAtCenter(hdc, _pt.x, _pt.y, _size, _size);
}
void Unit::CheckIsDead(Unit other)
{
	if (isDead == true)
		return;
	else if (RectInRect(_rc, other._missile._rc))
		isDead = true;
}