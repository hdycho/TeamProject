#pragma once
#include "gameNode.h"
#include "player.h"

struct SLASH
{
	image* image;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float angle;
	float gravity;
	animation* slashMotion;
	int damage;
	float speedX, speedY;
	void SLASH::move()
	{
		x += cosf(angle) * speedX;
		image->setX(x);
		y += -sinf(angle) * speedY;
		y += gravity;
		image->setY(y);
		rc = RectMakeCenter(x, y, image->getFrameWidth(),
			image->getFrameHeight());
	}
};

class Skill : public gameNode
{
private:
	vector<SLASH*> _vSlash;
	int imageCount = 0;
public:
	Skill();
	~Skill();

	HRESULT init();
	void release();
	void update();
	void render();
	void makeSlash(float x, float y, int damage, bool isLeft);
	void move();

	vector<SLASH*> getVSlash() { return _vSlash; }
};