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
	image* img; //�̹���
	RECT rc;	//�浹��Ʈ
	ENEMYSTATE eState;  //�̴Ͼ���� ���°�
	animation* eMotion;

	float speed;		//���ʹ� ���ǵ�
	int currentFrameX;	//���ʹ� ������ ��ȣ
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
	virtual void render();		//������ �׷���

	virtual void move();
	virtual void draw();		//�׷��ִ� �Լ�

								//bool bulletCountFire();

	inline RECT getRect() { return rc; }
};

