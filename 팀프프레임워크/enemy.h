#pragma once
#include "gameNode.h"
#include "PixelCol.h"

class player;

//�� ���°�
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
	image* Lweapon;	//�����̹���(����)
	image* Rweapon;	//�����̹���(������)
	RECT rc;	//�浹��Ʈ
	ENEMYSTATE eState;  //�̴Ͼ���� ���°�
	animation* eMotion; //�ִϸ��̼�
	player* _player;    //�÷��̾� ��ǥ�� �޾ƿ����
	PixelCol *epCol;	//�ȼ��ݸ��� ó��

	float speed;		//���ʹ� ���ǵ�
	int currentFrameX;	//���ʹ� ������ ��ȣ
	int currentFrameY;
	float x, y;			//���ʹ� ��ǥ��
	int px, py;			//�÷��̾� ��ǥ��
	float gravity;		//�߷°�
	float getTime;		//�̵� �ð�
	float getDelayTime; //�� �Ѿ� ��Ÿ��
	float getCollisionTime; //�ȼ��ø��� 


	int eHP = 1;			//ü��
	bool isRight;			//�Դٰ��� �ϱ����� �Ұ�
	bool isOffence;			//���������� �ƴ���
	bool isEnemyDie;		//�׾����� ��Ҵ���
	bool isCollision;		//�浹�ߴ��� 
	bool isEnemyBulletFire;	//�Ѿ� �߻� �ߴ���
	int  count;

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

	void setPlayerMemoryAddressLink(player* player) { _player = player; }	//��ũ����
	inline RECT getRect() { return rc; }				//���ʹ� ��Ʈ�� ���� �Լ�
	bool &GetisEnemyDie() { return isEnemyDie; }		//���ʹ̰� �׾����� Ȯ���ϴ� �Ұ��� ��
	int &GetEnemyHp() { return eHP; }	//���ʹ� HP ������&������
	RECT getEnemyRect() { return rc; }  //���ʹ� RC ������
};

