#include "stdafx.h"
#include "Bomb.h"


Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}

HRESULT Bomb::init(int _x, int _y, string oName)
{
	Obstacle::init(_x, _y, oName);
	img = IMAGEMANAGER->findImage("��ź��ֹ�");
	rc = RectMakeCenter(_x, _y, 50, 50);

	return S_OK;
}

void Bomb::ObstacleUpdate()
{
	//���⼭ �÷��̾�� ������ �������Ѵ�
}
