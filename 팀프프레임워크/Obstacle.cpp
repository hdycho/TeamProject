#include "stdafx.h"
#include "Obstacle.h"


Obstacle::Obstacle()
{
	IMAGEMANAGER->addFrameImage("������ֹ�", PathFile("image", "������ֹ�").c_str(), 50, 50, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("��ź��ֹ�", PathFile("image", "��ź��ֹ�").c_str(), 50, 50, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("����ֹ�", PathFile("image", "����ֹ�").c_str(), 50, 50, 1, 1, false, NULL);
}


Obstacle::~Obstacle()
{
}

HRESULT Obstacle::init(int _x, int _y, string oName)
{
	x = _x;
	y = _y;
	isShow = false;
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
