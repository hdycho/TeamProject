#pragma once
#include "gameNode.h"
#include "PixelCol.h"

class player;

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
	image* Lweapon;
	image* Rweapon;
	RECT rc;	//충돌렉트
	ENEMYSTATE eState;  //미니언들의 상태값
	animation* eMotion; //애니메이션
	player* _player;    //플레이어 좌표값 받아오기용
	PixelCol *epCol;	//픽셀콜리젼 처리

	float speed;		//에너미 스피드
	int currentFrameX;	//에너미 프레임 번호
	int currentFrameY;
	float x, y;
	float gravity;
	float getTime;
	float getDelayTime; //적 총알 쿨타임

	int eHP = 1;			//체력
	bool isRight;
	bool isOffence;
	bool isEnemyDie;
	bool isCollision;
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
	virtual void enemyCollision();

	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	inline RECT getRect() { return rc; }
	bool &GetisEnemyDie() { return isEnemyDie; }
	int &GetEnemyHp() { return eHP; }	//에너미 HP 접근자&설정자
	RECT getEnemyRect() { return rc; }  //에너미 RC 접근자
};

