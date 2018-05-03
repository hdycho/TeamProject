#include "stdafx.h"
#include "Skill.h"

Skill::Skill() {}
Skill::~Skill() {}

HRESULT Skill::init()
{
	string name = "slash";
	string slashName = "slash";
	IMAGEMANAGER->addFrameImage("slash", "image/slash.bmp", 800, 74, 8, 1, true, RGB(255, 0, 255));

	return S_OK;
}

void Skill::release()
{

}

void Skill::update()
{
	for (int i = 0; i < _vSlash.size(); ++i)
	{
		_vSlash[i]->gravity += 0.3f;
		_vSlash[i]->move();
		_vSlash[i]->slashMotion->frameUpdate(TIMEMANAGER->getElapsedTime());
		if (fabs(_vSlash[i]->fireX - _vSlash[i]->x) >= 400)//if (!_vSlash[i]->slashMotion->isPlay())
		{	
			SAFE_DELETE(_vSlash[i]);
			_vSlash.erase(_vSlash.begin() + i);
		}
	}
}

void Skill::render()
{
	for (int i = 0; i < _vSlash.size(); ++i)
		_vSlash[i]->image->aniRender(getMemDC(), _vSlash[i]->rc.left, _vSlash[i]->rc.top, _vSlash[i]->slashMotion);
}

void Skill::makeSlash(float x, float y, int damage, bool isLeft)
{
	SLASH* _slash;
	_slash = new SLASH;
	string imageName = "slash";
	imageName += ++imageCount;
	_slash->image = IMAGEMANAGER->addFrameImage(imageName, "image/slash.bmp", 800, 74, 8, 1, true, RGB(255, 0, 255));
	//IMAGEMANAGER->findImage(imageName);
	_slash->damage = damage;
	//_slash->damage = 4;
	if (isLeft) {				// 왼쪽으로 스킬 각도 조절
		_slash->x = x - _slash->image->getFrameWidth() / 8;
		_slash->speedX = 10;
		_slash->angle = getAngle(10, 10, 0, 0);
	}
	else {										// 오른쪽으로 스킬 각도 조절
		_slash->x = x + _slash->image->getFrameWidth() / 8;
		_slash->speedX = 10;
		_slash->angle = getAngle(10, 10, 20, 0);
	}
	_slash->gravity = 0;
	_slash->speedY = 10;
	_slash->y = y;
	_slash->rc = RectMakeCenter(_slash->x, _slash->y, _slash->image->getFrameWidth()
		, _slash->image->getFrameHeight());
	_slash->image->setX(_slash->x);
	_slash->image->setY(_slash->y);

	_slash->fireX = _slash->x;
	_slash->fireY = _slash->y;
	string slashName = "slash";
	slashName += imageCount;
	int arrSlash[] = { 0, 1, 2, 3, 4, 5, 6, 7 };
	KEYANIMANAGER->addArrayFrameAnimation(slashName, "slash", arrSlash, 8, 10, true);
	_slash->slashMotion = KEYANIMANAGER->findAnimation(slashName);

	_slash->slashMotion->start();
	_vSlash.push_back(_slash);
}