#include "stdafx.h"
#include "BulletManager.h"


BulletManager::BulletManager()
{
}


BulletManager::~BulletManager()
{
}

//이미지메니저로 미리만든 이미지삽입해야함
void BulletManager::BulletSetting(string bulletName, image * img, int bulletNum, bool isAnim, int animSpeed)
{
	bulletVec bVec;
	if (isAnim)//에니메이션 총알이미지일때
	{
		for (int i = 0; i < bulletNum; i++)
		{
			Bullet*bullet = new Bullet;
			bullet->rc = { 0,0,0,0 };
			bullet->img = img;

			bullet->anim = new animation;
			bullet->anim->init(img->getWidth(), img->getHeight(), img->getFrameWidth(), img->getFrameHeight());
			bullet->anim->setFPS(animSpeed);
			bullet->anim->setDefPlayFrame(false, true);
			bullet->anim->stop();

			bullet->bulletName = bulletName;
			bullet->speed = 0;
			bullet->gravity = 0;
			bullet->addGravity = 0;
			bullet->isShot = false;
			bullet->isAnimation = isAnim;
			bullet->useCollision = false;

			bVec.push_back(bullet);
		}
	}
	else//단일 총알이미지일때
	{
		for (int i = 0; i < bulletNum; i++)
		{
			Bullet*bullet = new Bullet;
			bullet->rc = { 0,0,0,0 };
			bullet->img = img;
			bullet->bulletName = bulletName;
			bullet->speed = 0;
			bullet->gravity = 0;
			bullet->addGravity = 0;
			bullet->isShot = false;
			bullet->isAnimation = isAnim;
			bullet->useCollision = false;

			bVec.push_back(bullet);
		}
	}
	
	bulletMapIter bMapIter = bMap.find(bulletName);
	if (bMapIter != bMap.end())
		return;
	bMap.insert(pair<string, bulletVec>(bulletName, bVec));
	bIdxMap.insert(pair<string, int>(bulletName, 0));
}

void BulletManager::BulletUpdate()
{
	bulletMapIter bMapIter = bMap.begin();
	bulletIter	  bIter;
	
	for (; bMapIter != bMap.end(); bMapIter++)
	{
		bIter = bMapIter->second.begin();
		for (; bIter != bMapIter->second.end(); bIter++)
		{
			if (!(*bIter)->isShot)continue;
			
			(*bIter)->gravity += (*bIter)->addGravity;

			(*bIter)->x += cosf((*bIter)->angle)*(*bIter)->speed;
			(*bIter)->y += -sinf((*bIter)->angle)*(*bIter)->speed+ (*bIter)->gravity;
			if ((*bIter)->isAnimation)
				(*bIter)->rc = RectMakeCenter((*bIter)->x, (*bIter)->y, (*bIter)->img->getFrameWidth(), (*bIter)->img->getFrameHeight());
			else
				(*bIter)->rc = RectMakeCenter((*bIter)->x, (*bIter)->y, (*bIter)->img->getWidth(), (*bIter)->img->getHeight());
			if (getDistance((*bIter)->initX, (*bIter)->initY, (*bIter)->x, (*bIter)->y) > 600)
			{
				(*bIter)->isShot = false;
				(*bIter)->rc = { 0,0,0,0 };
				(*bIter)->gravity = 0;
				(*bIter)->addGravity = 0;
			}

			if ((*bIter)->isAnimation)
			{
				(*bIter)->anim->frameUpdate(TIMEMANAGER->getElapsedTime());
			}

			if ((*bIter)->useCollision)
				(*bIter)->pcol->UpdatePosition((*bIter)->x, (*bIter)->y);
		}
	}
}

void BulletManager::BulletRender(HDC hdc)
{
	bulletMapIter bMapIter = bMap.begin();
	bulletIter	  bIter;

	for (; bMapIter != bMap.end(); bMapIter++)
	{
		bIter = bMapIter->second.begin();
		for (; bIter != bMapIter->second.end(); bIter++)
		{
			if (!(*bIter)->isShot)continue;

			if ((*bIter)->isAnimation)
				(*bIter)->img->aniRender(hdc, (*bIter)->rc.left, (*bIter)->rc.top, (*bIter)->anim);
			else
				(*bIter)->img->render(hdc, (*bIter)->rc.left, (*bIter)->rc.top);
		}
	}
}

void BulletManager::Shot(string bulletName, float x, float y, float angle, float gravity, int speed)
{
	bulletMapIter bMapIter = bMap.find(bulletName);
	bulletIdxMapIter bIdxMapIter = bIdxMap.find(bulletName);

	if (bMapIter->second[bIdxMapIter->second]->isAnimation)
	{
		bMapIter->second[bIdxMapIter->second]->x = x;
		bMapIter->second[bIdxMapIter->second]->y = y;
		bMapIter->second[bIdxMapIter->second]->initX = x;
		bMapIter->second[bIdxMapIter->second]->initY = y;

		bMapIter->second[bIdxMapIter->second]->rc = RectMakeCenter(x, y,
			bMapIter->second[bIdxMapIter->second]->img->getFrameWidth(),
			bMapIter->second[bIdxMapIter->second]->img->getFrameHeight());

		bMapIter->second[bIdxMapIter->second]->speed = speed;
		bMapIter->second[bIdxMapIter->second]->angle = angle;
		bMapIter->second[bIdxMapIter->second]->addGravity = gravity;
		bMapIter->second[bIdxMapIter->second]->gravity = 0;
		bMapIter->second[bIdxMapIter->second]->isShot = true;
		bMapIter->second[bIdxMapIter->second]->anim->start();
	}
	else
	{
		bMapIter->second[bIdxMapIter->second]->x = x;
		bMapIter->second[bIdxMapIter->second]->y = y;
		bMapIter->second[bIdxMapIter->second]->initX = x;
		bMapIter->second[bIdxMapIter->second]->initY = y;


		bMapIter->second[bIdxMapIter->second]->rc = RectMakeCenter(x, y,
			bMapIter->second[bIdxMapIter->second]->img->getWidth(),
			bMapIter->second[bIdxMapIter->second]->img->getHeight());

		bMapIter->second[bIdxMapIter->second]->speed = speed;
		bMapIter->second[bIdxMapIter->second]->angle = angle;
		bMapIter->second[bIdxMapIter->second]->addGravity = gravity;
		bMapIter->second[bIdxMapIter->second]->gravity = 0;
		bMapIter->second[bIdxMapIter->second]->isShot = true;
	}
	
	bIdxMapIter->second++;
	if (bIdxMapIter->second > bMapIter->second.size() - 1)
		bIdxMapIter->second = 0;
}

void BulletManager::Destroy(string bulletName, int bulletIdx)
{
	bulletMapIter bMapIter = bMap.find(bulletName);

	bMapIter->second[bulletIdx]->isShot = false;
	bMapIter->second[bulletIdx]->rc = { 0,0,0,0 };
	bMapIter->second[bulletIdx]->gravity = 0;
	bMapIter->second[bulletIdx]->addGravity = 0;
}

void BulletManager::UseCollision(string bulletName, int proveX, int proveY)
{
	bulletMapIter bMapIter = bMap.find(bulletName);

	bulletIter bIter = bMapIter->second.begin();
	for (;bIter != bMapIter->second.end(); bIter++)
	{
		(*bIter)->useCollision = true;
		(*bIter)->pcol = new PixelCol;
		(*bIter)->pcol->init(proveX, proveY);

	}
}

bool BulletManager::IsCollision(string bulletName, int*bulletPosX, int*bulletPosY, bool isMapCollision, HDC hdc, RECT rc)
{
	bulletMapIter bMapIter = bMap.find(bulletName);

	if (isMapCollision)
	{
		for (int i = 0; i < bMapIter->second.size(); i++)
		{
			if (!bMapIter->second[i]->isShot)continue;
			if (bMapIter->second[i]->pcol->RayCastRange(hdc, 255, 0, 0)
				|| bMapIter->second[i]->pcol->RayCastRange(hdc, 0, 0, 255))
			{
				*bulletPosX = GetCenterPos(bMapIter->second[i]->rc).x;
				*bulletPosY = GetCenterPos(bMapIter->second[i]->rc).y;
				Destroy(bulletName, i);
				return true;
			}
		}
	}
	else
	{
		RECT temp;
		for (int i = 0; i < bMapIter->second.size(); i++)
		{
			if (!bMapIter->second[i]->isShot)continue;
			if (IntersectRect(&temp, &bMapIter->second[i]->rc, &rc))
			{
				*bulletPosX = GetCenterPos(bMapIter->second[i]->rc).x;
				*bulletPosY = GetCenterPos(bMapIter->second[i]->rc).y;
				Destroy(bulletName, i);
				return true;
			}
		}
	}
	return false;
}


