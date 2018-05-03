#pragma once
#include <math.h>
#define PI 3.14

//==============================================
// ## 18.02.07 ## - Macro Function - ##
//==============================================

//Line
inline void LineMake(HDC hdc, int x1, int y1, int x2, int y2)
{
	MoveToEx(hdc, x1, y1, NULL);
	LineTo(hdc, x2, y2);
}

//Rect
inline RECT RectMake(int x, int y, int width, int height)
{
	RECT rc = { x, y, x + width, y + height };

	return rc;
}

inline RECT RectMakeCenter(int x, int y, int width, int height)
{
	RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };

	return rc;
}

inline POINT GetCenterPos(const RECT&rect)
{
	POINT pos;
	pos.x = rect.left + (rect.right - rect.left) / 2;
	pos.y = rect.top + (rect.bottom - rect.top) / 2;

	return pos;
}

//Rectangle
//left, top 기준으로 사각형이 생성되는 함수 dc영역, 중점좌표 X, Y, 가로크기, 세로크기
inline void RectangleMake(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x, y, x + width, y + height);
}

//중점 기준으로 사각형이 생성되는 함수 dc영역, 중점좌표 X, Y, 가로크기, 세로크기
inline void RectangleMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Rectangle(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}

//Ellipse
//Left, top기준으로 원이 생성되는 함수 (DC영역, left, Top, 가로크기, 세로크기)
inline void EllipseMake(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x, y, x + width, y + height);
}

//중점 기준으로 원이 생성되는 함수 dc영역, 중점좌표 X, Y, 가로크기, 세로크기
inline void EllipseMakeCenter(HDC hdc, int x, int y, int width, int height)
{
	Ellipse(hdc, x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2));
}


//원충돌 함수
inline bool CircleCollision(RECT&r1, RECT&r2)
{
	POINT cPos1 = GetCenterPos(r1); //r1의 중점
	POINT cPos2 = GetCenterPos(r2); //r2의 중점

	float r1Radius = (r1.right - r1.left) / 2; // r1의 반지름
	float r2Radius = (r2.right - r2.left) / 2; // r2의 반지름

	float distance = sqrtf(pow(cPos1.x - cPos2.x, 2) + pow(cPos1.y - cPos2.y, 2));

	//두원의 반지름의 합이 원의 중심과의 거리보다 클때
	if (r1Radius + r2Radius >= distance)
		return true;
	else
		return false;
}

//원과 사각형충돌함수
inline bool ColCircleToRect(RECT rect, RECT circle)
{
	POINT cPos = { GetCenterPos(circle).x,GetCenterPos(circle).y };//원의 중점
	POINT rPos = { GetCenterPos(rect).x,GetCenterPos(rect).y };//사각형의 중점
	float radius = (circle.right - circle.left) / 2;//원의 반지름

	float halfRectWidth = (rect.right - rect.left) / 2;//사각형 폭길이의 반
	float halfRectHeight = (rect.bottom - rect.top) / 2;//사각형 높이길이의 반

														//렉트에 충돌하는 반지름길이만큼 늘린 사각형
	RECT outRect = RectMakeCenter(GetCenterPos(rect).x, GetCenterPos(rect).y,
		(rect.right - rect.left) + 2 * radius, (rect.bottom - rect.top) + 2 * radius);
	//렉트의 외부를감싸는 사각형의 반지름
	float outRadius = sqrtf(powf(halfRectWidth, 2) + powf(halfRectHeight, 2));

	//확장사각형의 범위에 원에 중점이 들어오면
	if (PtInRect(&outRect, cPos))
	{
		//렉트를 감싸는 원의반지름+원의반지름이 거리보다 커질때
		if (outRadius + radius >= sqrtf(powf(cPos.x - rPos.x, 2) + powf(cPos.y - rPos.y, 2)))
			return true;
		else
			return false;
	}
	else // 확장사각형의 범위에 원에 중점이 들어오지 않으면
		return false;
}

//만약 폴더가 두개라면 폴더이름\\폴더이름 이런식으로 인자보내줘야함
inline string PathFile(string FolderName, string FileName)
{
	/*char totalPathName[256]="";
	char folderName[256]="";
	char fileName[256]="";

	strcpy(folderName, FolderName);
	strcat(folderName, "\\");

	strcpy(fileName, FileName);
	strcat(fileName, ".bmp");

	strcpy(totalPathName, folderName);
	strcat(totalPathName, fileName);*/

	

	return FolderName+"\\"+FileName+".bmp";
}

inline void DrawRect(HDC hdc, RECT rc, int penSize, COLORREF color)
{
	HPEN pen, oldPen;
	pen = CreatePen(PS_SOLID, penSize, color);
	oldPen = (HPEN)SelectObject(hdc, pen);

	LineMake(hdc, rc.left, rc.top, rc.right, rc.top);
	LineMake(hdc, rc.left, rc.bottom, rc.right, rc.bottom);
	LineMake(hdc, rc.left, rc.top, rc.left, rc.bottom);
	LineMake(hdc, rc.right, rc.top, rc.right, rc.bottom);

	SelectObject(hdc, oldPen);
	DeleteObject(pen);
}
