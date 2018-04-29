#include "stdafx.h"
#include "PixelCol.h"

PixelCol::PixelCol()
{
}


PixelCol::~PixelCol()
{
}

HRESULT PixelCol::init(int _proveWidth, int _proveHeight)
{
	proveWidth = _proveWidth;
	proveHeight = _proveHeight;
	return S_OK;
}

void PixelCol::Release()
{
}

void PixelCol::UpdatePosition(int _x, int _y)
{
	x = _x;
	y = _y;
}

void PixelCol::render(HDC hdc)
{
	for (int i = y; i <= y + proveHeight; i++)
	{
		COLORREF color = GetPixel(hdc, x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			if (r == 255 && g == 0 && b == 0)
			{
				LineMake(hdc, x, y + proveHeight / 2, x, i);
			}
		}
	}
	for (int i = y; i <= y + proveHeight / 2; i++)
	{
		for (int j = x; j <= x + proveWidth; j++)
		{
			COLORREF color = GetPixel(hdc, j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 0 && b == 255))
			{
				float angle = getAngle(x, y + proveHeight / 2, j, i);
				if (angle>0)
					LineMake(hdc, x, y + proveHeight / 2, j, i);
			}
		}
		for (int j = x - proveWidth; j < x; j++)
		{
			COLORREF color = GetPixel(hdc, j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == 0 && g == 0 && b == 255))
			{
				float angle = getAngle(x, y + proveHeight / 2, j, i);
				if (angle<PI)
					LineMake(hdc, x, y + proveHeight / 2, j, i);
			}
		}
	}
}

bool PixelCol::RayCastingUpY(HDC hdc, int rValue, int bValue, int gValue)
{
	//중점부터 중점보다 아래의 탐색범위까지 탐색
	for (int i = y - proveHeight; i < y; i++)
	{
		COLORREF color = GetPixel(hdc, x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if ((r == rValue && g == gValue && b == bValue))
		{
			collisionUpY = i;
			return true;
		}
	}
	return false;
}

bool PixelCol::RayCastingDownY(HDC hdc, int rValue, int bValue, int gValue)
{
	//중점부터 중점보다 위의 탐색범위까지 탐색
	for (int i = y; i <= y + proveHeight; i++)
	{
		COLORREF color = GetPixel(hdc, x, i);

		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (!(r == 255 && g == 0 && b == 255))
		{
			if (r == rValue&&g == gValue&&b == bValue)
			{
				collisionDownY = i;
				return true;
			}
		}
	}

	return false;
}

bool PixelCol::RayCastingX(HDC hdc, float risAngle, int rValue, int bValue, int gValue)
{
	//이중 포문을 사용하여 Y축의 측정범위를 기준으로 X축을 탐색한다
	for (int i = y; i <= y + proveHeight / 2; i++)
	{
		for (int j = x; j <= x + proveWidth; j++)
		{
			COLORREF color = GetPixel(hdc, j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == rValue && g == gValue && b == bValue))
			{
				float angle = getAngle(x, y + proveHeight / 2, j, i);
				if (angle>risAngle)
					return true;
			}
		}
		for (int j = x - proveWidth; j < x; j++)
		{
			COLORREF color = GetPixel(hdc, j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == rValue && g == gValue && b == bValue))
			{
				float angle = getAngle(x, y + proveHeight / 2, j, i);
				if (PI - angle>risAngle)
					return true;
			}
		}
	}
	return false;
}

bool PixelCol::RayCastRange(HDC hdc, int rValue, int gValue, int bValue)
{
	for (int i = y - proveHeight / 2; i <= y + proveHeight / 2; i++)
	{
		for (int j = x - proveWidth / 2; j <= x + proveWidth / 2; j++)
		{
			COLORREF color = GetPixel(hdc, j, i);

			int r = GetRValue(color);
			int g = GetGValue(color);
			int b = GetBValue(color);

			if ((r == rValue && g == gValue && b == bValue))
			{
				return true;
			}
		}
	}
	return false;
}
