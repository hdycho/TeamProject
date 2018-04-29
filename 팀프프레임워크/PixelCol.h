#pragma once
//#include "gameNode.h"
class PixelCol 
{
private:
	//픽셀콜리전을 사용할 객체는 이 클래스를 불러와서 사용해야함
	int proveWidth; // 가로 탐색범위
	int proveHeight; // 세로 탐색범위

	int x, y;
	float collisionDownY; // 충돌포인트아래
	float collisionUpY; //충돌포인트 위에
public:
	PixelCol();
	~PixelCol();

	//충돌처리할 이미지의 너비와 높이셋팅
	HRESULT init(int _proveWidth, int _proveHeight);
	void Release();

	//실시간으로 충돌좌표 바꿔주는 함수
	void UpdatePosition(int _x, int _y);
	void render(HDC hdc);


	//=================픽셀충돌 함수=====================//
	//Y축을 탐색하고 밑을 기준잡아 떨어지지않게 맞춰주는 함수
	bool RayCastingUpY(HDC hdc, int rValue, int bValue, int gValue);
	bool RayCastingDownY(HDC hdc, int rValue, int bValue, int gValue);

	//X축을 탐색하는 함수 
	bool RayCastingX(HDC hdc, float risAngle, int rValue, int bValue, int gValue);

	//범위탐색하는 함수
	bool RayCastRange(HDC hdc, int rValue, int gValue, int bValue);

	//getter,setter
	inline void setPosDownY(float&_y) { _y = collisionDownY - proveHeight; }
	inline void setPosUpY(float&_y) { _y = collisionUpY + proveHeight; }
	inline int getX() { return x; }
	inline int getY() { return y; }
};

