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
	image* img; //�̹���
	image* Lweapon;
	image* Rweapon;
	RECT rc;	//�浹��Ʈ
	ENEMYSTATE eState;  //�̴Ͼ���� ���°�
	animation* eMotion; //�ִϸ��̼�
	player* _player;    //�÷��̾� ��ǥ�� �޾ƿ����
	PixelCol *epCol;	//�ȼ��ݸ��� ó��

	float speed;		//���ʹ� ���ǵ�
	int currentFrameX;	//���ʹ� ������ ��ȣ
	int currentFrameY;
	float x, y;
	float gravity;
	float getTime;
	float getDelayTime; //�� �Ѿ� ��Ÿ��

	int eHP = 1;			//ü��
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
	virtual void render();		//������ �׷���

	virtual void move();
	virtual void draw();		//�׷��ִ� �Լ�
	virtual void enemyCollision();

	void setPlayerMemoryAddressLink(player* player) { _player = player; }
	inline RECT getRect() { return rc; }
	bool &GetisEnemyDie() { return isEnemyDie; }
	int &GetEnemyHp() { return eHP; }	//���ʹ� HP ������&������
	RECT getEnemyRect() { return rc; }  //���ʹ� RC ������
};

