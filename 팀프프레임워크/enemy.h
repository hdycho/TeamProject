#pragma once
#include "gameNode.h"

enum ENEMYSTATE {
	IDLE,
	LEFT_MOVE,
	RIGHT_MOVE,
	LEFT_OFFENCE,
	RIGHT_OFFENCE,
	LEFT_DIE,
	RIGHT_DIE
};

class enemy : public gameNode
{
protected:
	image* img; //이미지
	RECT rc;	//충돌렉트
	ENEMYSTATE eState;  //미니언들의 상태값
	animation* eMotion;

	float speed;		//에너미 스피드
	int currentFrameX;	//에너미 프레임 번호
	int currentFrameY;
	float x, y;
	float gravity;
	bool isRight;

	int count;

public:
	enemy();
	~enemy();

	HRESULT init();
	virtual HRESULT init(int x, int y);
	HRESULT init(const char* imageName, POINT position);
	virtual void release();
	virtual void update();
	virtual void render();		//모조리 그려짐

	virtual void move();
	virtual void draw();		//그려주는 함수

								//bool bulletCountFire();

	inline RECT getRect() { return rc; }
};

