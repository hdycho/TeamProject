#pragma once
#include "gameNode.h"

#define KNIGHTSPEED 2.5f;

enum KNIGHTDIRECTION
{
	KNIGHTDIRECTION_RIGHT_STOP,
	KNIGHTDIRECTION_LEFT_STOP,
	KNIGHTDIRECTION_RIGHT_MOVE,
	KNIGHTDIRECTION_LEFT_MOVE,
	KNIGHTDIRECTION_RIGHT_SIT,
	KNIGHTDIRECTION_LEFT_SIT,
	KNIGHTDIRECTION_RIGHT_ATTACK,
	KNIGHTDIRECTION_LEFT_ATTACK,
	KNIGHTDIRECTION_RIGHT_SIT_ATTACK,
	KNIGHTDIRECTION_LEFT_SIT_ATTACK,
	KNIGHTDIRECTION_RIGHT_JUMP,
	KNIGHTDIRECTION_LEFT_JUMP,
	KNIGHTDIRECTION_RIGHT_MOVE_JUMP,
	KNIGHTDIRECTION_LEFT_MOVE_JUMP
};

class knight : public gameNode
{
private:
	KNIGHTDIRECTION _knightDirection;

	image* _image;
	float _x, _y;
	RECT _rc;

	animation* _knightMotion;

public:
	knight();
	~knight();

	HRESULT init();
	void release();
	void update();
	void render();

	static void rightFire(void* obj);
	static void leftFire(void* obj);
	static void rightSitFire(void* obj);
	static void leftSitFire(void* obj);

	//기사의 상태에 대한 접근,설정자
	KNIGHTDIRECTION getKnightDirection() { return _knightDirection; }
	void setKnightDirection(KNIGHTDIRECTION direction) { _knightDirection = direction; }

	//기사의 모션에 대한 접근,설정자
	animation* getKnightMotion() { return _knightMotion; }
	void setKnightMotion(animation* ani) { _knightMotion = ani; }
};

