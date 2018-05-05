#include "stdafx.h"
#include "Obstacle.h"


Obstacle::Obstacle()
{
	IMAGEMANAGER->addFrameImage("������ֹ�", PathFile("image", "������ֹ�").c_str(), 50, 50, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("��ź��ֹ�", PathFile("image", "��ź��ֹ�").c_str(), 50, 50, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("����ֹ�", PathFile("image", "����ֹ�").c_str(), 50, 50, 1, 1, false, NULL);
	EFFECTMANAGER->addEffect("��ֹ�����", PathFile("image", "��ֹ�����").c_str(), 350, 50, 50, 50, 20, 1, 50);
	EFFECTMANAGER->addEffect("��ź��ֹ�����", PathFile("image", "��ź��ֹ�����").c_str(), 640, 80, 80, 80, 20, 1, 50);
}


Obstacle::~Obstacle()
{
}

HRESULT Obstacle::init(int _x, int _y, string oName)
{
	x = _x;
	y = _y;
	isShow = true;
	this->oName = oName;
	return S_OK;
}

void Obstacle::render()
{
	img->render(getMemDC(), rc.left, rc.top);
}

void Obstacle::update()
{
	ObstacleUpdate();
}

void Obstacle::release()
{
}
