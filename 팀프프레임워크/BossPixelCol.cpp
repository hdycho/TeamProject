#include "stdafx.h"
#include "Boss.h"
#include "player.h"

void Boss::PixelColUpdate()
{
	if (_bossPixelCol->RayCastingDownY(IMAGEMANAGER->findImage("보스방충돌맵")->getMemDC(), 255, 0, 0))
	{
		if (_bossJumpPower <= 0)
		{
			_bossPixelCol->setPosDownY(_bossProbeY);

			_bossJumpPower = 0.0f;
			_bossGravityPower = 0.0f;
		}

	}

	else
	{
		_bossGravityPower = 0.3f;
	}

	// 천장충돌
	if (_bossPixelCol->RayCastingUpY(IMAGEMANAGER->findImage("보스방충돌맵")->getMemDC(), 255, 0, 0))
	{
		if (_bossJumpPower > 0)
		{
			_bossPixelCol->setPosUpY(_bossProbeY);

			_bossJumpPower = 0;
		}
	}
}