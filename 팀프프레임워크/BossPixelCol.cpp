#include "stdafx.h"
#include "Boss.h"
#include "player.h"

void Boss::PixelColUpdate()
{
        if (_bossPixelCol->RayCastingDownY(IMAGEMANAGER->findImage("보스방충돌맵")->getMemDC(), 255, 0, 0))
        {
        	if (_bossJumpPower <= 0 )
        	{
        		_bossPixelCol->setPosDownY(_bossProbeY);
        
        		_bossJumpPower    = 0.0f;
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

	// 벽 충돌
	/*if (_bossPixelCol->RayCastingX(IMAGEMANAGER->findImage("보스방충돌맵")->getMemDC(), 0, 0, 255, 0))
	{						
		static float BLUE = 0;
		BLUE += TIMEMANAGER->getElapsedTime();


		 if (
			_bossState == R_IDLE      ||
			_bossState == R_MOVE      ||
			_bossState == R_BACK_MOVE ||
			_bossState == R_SATK      ||
			_bossState == R_GATK      ||
			_bossState == R_JUMP      ||
			_bossState == R_STAY      ||
			_bossState == R_FALL
			 )
		 {
			 _bossState = L_MOVE;
				 
		 }
		 if (
		     _bossState == L_IDLE ||
		     _bossState == L_MOVE ||
		     _bossState == L_BACK_MOVE ||
		     _bossState == L_SATK ||
		     _bossState == L_GATK ||
		     _bossState == L_JUMP ||
		     _bossState == L_STAY ||
		     _bossState == L_FALL
			 )
		 {
			 
			 _bossState = R_MOVE;
				
		 }
	}       */
}
