#pragma once
#include "gameNode.h"
#include "PixelCol.h"

class player;

//적 상태값
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
	image* Lweapon;	//무기이미지(왼쪽)
	image* Rweapon;	//무기이미지(오른쪽)
	RECT rc;	//충돌렉트
	ENEMYSTATE eState;  //미니언들의 상태값
	animation* eMotion; //애니메이션
	player* _player;    //플레이어 좌표값 받아오기용
	PixelCol *epCol;	//픽셀콜리젼 처리

	float speed;		//에너미 스피드
	int currentFrameX;	//에너미 프레임 번호
	int currentFrameY;
	float x, y;			//에너미 좌표값
	int px, py;			//플레이어 좌표값
	float gravity;		//중력값
	float getTime;		//이동 시간
	float getDelayTime; //적 총알 쿨타임
	float getCollisionTime; //픽셀컬리젼 


	int eHP = 1;			//체력
	bool isRight;			//왔다갔다 하기위한 불값
	bool isOffence;			//공격중인지 아닌지
	bool isEnemyDie;		//죽었는지 살았는지
	bool isCollision;		//충돌했는지 
	bool isEnemyBulletFire;	//총알 발사 했는지
	int  count;

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

	void setPlayerMemoryAddressLink(player* player) { _player = player; }	//링크연결
	inline RECT getRect() { return rc; }				//에너미 렉트를 얻어가는 함수
	bool &GetisEnemyDie() { return isEnemyDie; }		//에너미가 죽었는지 확인하는 불값을 얻어감
	int &GetEnemyHp() { return eHP; }	//에너미 HP 접근자&설정자
	RECT getEnemyRect() { return rc; }  //에너미 RC 접근자
};

