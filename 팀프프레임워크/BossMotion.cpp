#include "stdafx.h"
#include "Boss.h"
#include "player.h"
#include "pixelCol.h"

//렉트 점선 확인법
//DrawFocusRect(gemtMemDC(), &_bossRc)

void Boss::BossMoveUpdate()
{
	if(_isMotion1 == true)
	{

		if (0 < _bossHp < 40)
		{
			_bossImg = IMAGEMANAGER->findImage("HURT");
			_bossAni = KEYANIMANAGER->findAnimation("H_EF");
			_bossAni->start();
		}

		switch (_bossState)
		{
				//====================================================================//
	     case L_IDLE:
		 {				
			 static float ONE = 0;
			 ONE += TIMEMANAGER->getElapsedTime();
			 
			 if (_bossHp <= 0)
			 {
				 _bossState = L_DEAD;

				 _bossImg = IMAGEMANAGER->findImage("DEAD");
				 _bossAni = KEYANIMANAGER->findAnimation("LDEAD");
				 _bossAni->start();
			 }
			 _isBossJumping   = false;

			 if (_centerX >= _plyCenterX ||
				 _centerX <= _plyCenterX)
			 {
				 if(_centerX >= _plyCenterX)
				 {
					 if (_centerX - _plyCenterX >= 100)
					 {
						 if (ONE >= 2)
						 {
							 _bossState = L_MOVE;

							 _bossImg   = IMAGEMANAGER->findImage("BOSSMOVE");
							 _bossAni   = KEYANIMANAGER->findAnimation("L_MOVE");

							 _bossAni->start();

							 ONE = 0;
							 
						 }
					 }

					 else if (30 < _centerX - _plyCenterX < 100)
					 {
						 if (ONE >= 1)
						 {

							 _bossState = R_BACK_MOVE;

							 _bossImg = IMAGEMANAGER->findImage("BACK");
							 _bossAni = KEYANIMANAGER->findAnimation("RBACK");

							 _bossAni->start();

							 ONE = 0;
						
						 }
					 }

					 else if (_centerX - _plyCenterX <= 30)
					 {
						 if (ONE >= 1)
						 {
							 _bossState = L_SATK;

							 _bossImg   = IMAGEMANAGER->findImage("SWORD");
							 _bossAni   = KEYANIMANAGER->findAnimation("LSA");

							 ONE        = 0;
						 }
					 }
				 }

				 else if (_centerX <= _plyCenterX)
				 {

					 if (_plyCenterX - _centerX >= 100)
					 {
						 if (ONE >= 1)
						 {

							 _bossState = R_GATK;


							 _bossImg   = IMAGEMANAGER->findImage("BOSS_GUN_ATK");
							 _bossAni   = KEYANIMANAGER->findAnimation("RG");

							 _bossAni->start();

							 BULLET->Shot("RGF", _centerX + 120, _centerY - 10, 0, 0.1f, 5);
							 BULLET->Shot("RGF", _centerX + 100, _centerY - 30, 0, 0.1f, 5);
							 BULLET->Shot("RGF", _centerX + 120, _centerY - 80, 0, 0.1f, 5);
							 BULLET->Shot("RGF", _centerX + 90,  _centerY + 10, 0, 0.1f, 5);
							 BULLET->Shot("RGF", _centerX + 120, _centerY + 50, 0, 0.1f, 5);

							 ONE        = 0;

						 }
					 }
					 else if(30 <_plyCenterX - _centerX < 100)
					 {
						 if (ONE >= 1)
						 {
							 _bossState = L_SATK;

							 _bossImg = IMAGEMANAGER->findImage("SWORD");
							 _bossAni = KEYANIMANAGER->findAnimation("LSA");

							 _bossAni->start();

							 ONE = 0;
						 }

					 }
					 else if (_plyCenterX - _centerX <= 30)
					 {
						 if (ONE >= 1)
						 {
							 _bossState = R_SATK;

							 _bossImg = IMAGEMANAGER->findImage("SWORD");
							 _bossAni = KEYANIMANAGER->findAnimation("RSA");
							 _bossAni->start();


							 ONE        = 0;
						 }
					 }
				 }
			 }
		 }
		 break;
		
				//====================================================================//
	     case L_MOVE:
		 {

			 static float TWO = 0;
			 TWO += TIMEMANAGER->getElapsedTime();

			 if (_bossHp <= 0)
			 {
				 _bossState = L_DEAD;

				 _bossImg = IMAGEMANAGER->findImage("DEAD");
				 _bossAni = KEYANIMANAGER->findAnimation("LDEAD");
				 _bossAni->start();
			 }

				_isBossJumping = false;

				if (_bossRc.left - BOSS_BACK > 290)
				{

					_centerX		 -= BOSS_SPEED;
					_bossRc.right	 -= BOSS_SPEED;
					_bossRc.left	 -= BOSS_SPEED;
				}
				
					if (_centerX <= _plyCenterX ||
						_centerX >= _plyCenterX)
					{
						if (_centerX <= _plyCenterX)
						{
							if (_plyCenterX - _centerX >= 100)
							{
								if (TWO >= 1)
								{
									_bossState = R_IDLE;

									_bossImg = IMAGEMANAGER->findImage("BOSS");
									_bossAni = KEYANIMANAGER->findAnimation("R_IDLE");
									_bossAni->start();

									TWO = 0;

									
								}
							}

							else if (30 < _plyCenterX - _centerX < 100)
							{
								if (TWO >= 2)
								{
									_bossState = R_GATK;

									_bossImg = IMAGEMANAGER->findImage("BOSS_GUN_ATK");
									_bossAni = KEYANIMANAGER->findAnimation("RG");

									_bossAni->start();

									BULLET->Shot("RGF", _centerX + 100, _centerY - 30, 0, 0.1f, 5);
									BULLET->Shot("RGF", _centerX + 120, _centerY - 80, 0, 0.1f, 5);
									BULLET->Shot("RGF", _centerX + 90,  _centerY + 10, 0, 0.1f, 5);
									BULLET->Shot("RGF", _centerX + 120, _centerY + 50, 0, 0.1f, 5);
									BULLET->Shot("RGF", _centerX + 120, _centerY - 10, 0, 0.1f, 5);

									TWO = 0;
								}
							}

							else if (_plyCenterX - _centerX <= 30)
							{
								if (TWO >= 1)
								{
									_bossState = L_BACK_MOVE;

									_bossImg = IMAGEMANAGER->findImage("BACK");
									_bossAni = KEYANIMANAGER->findAnimation("LBACK");

									_bossAni->start();

									TWO = 0;
								}
							}
						}

						else if (_centerX >= _plyCenterX)
						{

							if (_centerX - _plyCenterX >= 100)
							{
								if (TWO >= 1)
								{
									_bossState = L_IDLE;

									_bossImg = IMAGEMANAGER->findImage("BOSS");
									_bossAni = KEYANIMANAGER->findAnimation("L_IDLE");

									_bossAni->start();

									TWO = 0;
								}
							}

							else if (50 < _centerX - _plyCenterX < 100)
							{
								

								_bossState = L_GATK;

								_bossImg = IMAGEMANAGER->findImage("BOSS_GUN_ATK");
								_bossAni = KEYANIMANAGER->findAnimation("LG");

								_bossAni->start();


								BULLET->Shot("LGF", _centerX - 100, _centerY - 30, PI, 0.1f, 5);
								BULLET->Shot("LGF", _centerX - 120, _centerY - 80, PI, 0.1f, 5);
								BULLET->Shot("LGF", _centerX - 120, _centerY - 10, PI, 0.1f, 5);
								BULLET->Shot("LGF", _centerX - 90,  _centerY + 10, PI, 0.1f, 5);
								BULLET->Shot("LGF", _centerX - 120, _centerY + 50, PI, 0.1f, 5);


								TWO = 0;
							}


							else if (_centerX - _plyCenterX <= 50)
							{
								if (TWO >= 2)
								{
									_bossState = R_BACK_MOVE;

									_bossImg = IMAGEMANAGER->findImage("BACK");
									_bossAni = KEYANIMANAGER->findAnimation("LBACK");

									_bossAni->start();

									TWO = 0;
								}
							}
						}
					}
				
		 }
		 break;
			

				//====================================================================//
			case L_SATK:
			{
				static float THREE = 0;
				THREE += TIMEMANAGER->getElapsedTime();

				if (_bossHp <= 0)
				{
					_bossState = L_DEAD;

					_bossImg = IMAGEMANAGER->findImage("DEAD");
					_bossAni = KEYANIMANAGER->findAnimation("LDEAD");
					_bossAni->start();
				}

				_isBossJumping = false;

				_atkBoxCenterX = _centerX - 120;
				_atkBoxCenterY = _centerY;

				EFFECTMANAGER->play("좌검기", _atkBoxCenterX - 30, _atkBoxCenterY - 20);
				EFFECTMANAGER->play("좌검기", _atkBoxCenterX - 130, _atkBoxCenterY);
				EFFECTMANAGER->play("좌검기", _atkBoxCenterX - 30, _atkBoxCenterY + 20);

				_boxCount = 0;

				if (_centerX <= _plyCenterX ||
					_centerX >= _plyCenterX)
				{
					if (_centerX <= _plyCenterX)
					{
						if (_plyCenterX - _centerX <= 30)
						{
							if (THREE >= 1)
							{
								_bossState = L_BACK_MOVE;

								_bossImg   = IMAGEMANAGER->findImage("BACK");
								_bossAni   = KEYANIMANAGER->findAnimation("LBACK");
								_bossAni->start();

								THREE      = 0;
							}
						}

						else if (30 < _plyCenterX - _centerX < 100)
						{
							if (THREE >= 1)
							{
								_bossState = R_IDLE;

								_bossImg = IMAGEMANAGER->findImage("BOSS");
								_bossAni = KEYANIMANAGER->findAnimation("R_IDLE");
								_bossAni->start();

								THREE = 0;
							}
						}

						else if (_plyCenterX - _centerX >= 100)
						{
							if (THREE >= 1)
							{
								_bossState = R_SATK;

								_bossImg = IMAGEMANAGER->findImage("SWORD");
								_bossAni = KEYANIMANAGER->findAnimation("RSA");
								_bossAni->start();

								/*_bossState = R_GATK;

								_bossImg = IMAGEMANAGER->findImage("BOSS_GUN_ATK");
								_bossAni = KEYANIMANAGER->findAnimation("RG");

								_bossAni->start();


								BULLET->Shot("RGF", _centerX + 100, _centerY - 30, 0, 0.1f, 5);
								BULLET->Shot("RGF", _centerX + 120, _centerY - 80, 0, 0.1f, 5);
								BULLET->Shot("RGF", _centerX + 120, _centerY - 10, 0, 0.1f, 5);
								BULLET->Shot("RGF", _centerX + 90, _centerY + 10, 0, 0.1f, 5);
								BULLET->Shot("RGF", _centerX + 120, _centerY + 50, 0, 0.1f, 5);*/

								THREE = 0;
							}
						}
					}

					else if (_centerX >= _plyCenterX)
					{
						if (_centerX - _plyCenterX >= 120)
						{
							if (THREE >= 1)
							{

								_bossState        = L_JUMP;
							

								_bossJumpPower    = 15.0f;
								_bossGravityPower = 0.3f;

							
								_bossImg          = IMAGEMANAGER->findImage("JUMP");
								_bossAni          = KEYANIMANAGER->findAnimation("LJ");
										          
								_bossAni->start();

								THREE			  = 0;
							}

						}

						else if (60 < _centerX - _plyCenterX < 120)
						{
							if (THREE >= 1)
							{
								_bossState = L_JUMP;

								_bossJumpPower = 15.0f;
								_bossGravityPower = 0.3f;

								_bossImg = IMAGEMANAGER->findImage("JUMP");
								_bossAni = KEYANIMANAGER->findAnimation("LJ");

								_bossAni->start();

								THREE = 0;
							}
						}

						else if (_centerX - _plyCenterX <= 60)
						{
							if (THREE >= 1)
							{
								_bossState        = R_JUMP;

								_bossJumpPower   = 15.0f;
								_bossGravityPower = 0.3f;

								_bossImg          = IMAGEMANAGER->findImage("JUMP");
								_bossAni          = KEYANIMANAGER->findAnimation("RJ");

								_bossAni->start();

								THREE = 0;
							}
						}
					}
				
				}
			}
			break;
				//====================================================================//
			case L_BACK_MOVE:
					{
						static float FOUR = 0;
						FOUR += TIMEMANAGER->getElapsedTime();


						if (_bossHp <= 0)
						{
							_bossState = L_DEAD;

							_bossImg = IMAGEMANAGER->findImage("DEAD");
							_bossAni = KEYANIMANAGER->findAnimation("LDEAD");
							_bossAni->start();
						}

						_isBossJumping = false;

						if (_bossRc.left - BOSS_BACK > 290)
						{
							_centerX -= BOSS_BACK;
							_bossRc.right -= BOSS_BACK;
							_bossRc.left -= BOSS_BACK;
						}

							if (_plyCenterX <= _centerX ||
								_centerX <= _plyCenterX)
							{
								if (_plyCenterX <= _centerX)
								{

									if (_centerX - _plyCenterX >= 100)
									{

										if (FOUR >= 2)
										{
											_bossState = L_MOVE;

											_bossImg = IMAGEMANAGER->findImage("BOSSMOVE");
											_bossAni = KEYANIMANAGER->findAnimation("L_MOVE");

											_bossAni->start();

											FOUR = 0;
										}
									}
									else if (30 < _centerX - _plyCenterX < 100)
									{
										if (FOUR >= 1)
										{
											_bossState = L_GATK;

											_bossImg = IMAGEMANAGER->findImage("BOSS_GUN_ATK");
											_bossAni = KEYANIMANAGER->findAnimation("LG");

											_bossAni->start();

											BULLET->Shot("LGF", _centerX - 100, _centerY - 30, PI, 0.1f, 5);
											BULLET->Shot("LGF", _centerX - 120, _centerY - 80, PI, 0.1f, 5);
											BULLET->Shot("LGF", _centerX - 120, _centerY - 10, PI, 0.1f, 5);
											BULLET->Shot("LGF", _centerX - 90, _centerY + 10, PI, 0.1f, 5);
											BULLET->Shot("LGF", _centerX - 120, _centerY + 50, PI, 0.1f, 5);

											FOUR = 0;
											
										}
									}
									else if (_centerX - _plyCenterX <= 30)
									{

										if (FOUR >= 1)
										{
											_bossState = R_BACK_MOVE;

											_bossImg = IMAGEMANAGER->findImage("BACK");
											_bossAni = KEYANIMANAGER->findAnimation("RBACK");
											_bossAni->start();

											FOUR = 0;
										}
									}
								}

								else if (_centerX <= _plyCenterX)
								{
									if (_plyCenterX - _centerX <= 50)
									{
										if (FOUR >= 2)
										{
											_bossState = L_BACK_MOVE;

											_bossImg = IMAGEMANAGER->findImage     ("BACK");
											_bossAni = KEYANIMANAGER->findAnimation("L_MOVE");
											_bossAni->start();

											FOUR = 0;
										}
									}

									else if (50 < _plyCenterX - _centerX <= 100)
									{
										if (FOUR >= 2)
										{
											_bossState = R_IDLE;

											_bossImg = IMAGEMANAGER->findImage("BOSS");
											_bossAni = KEYANIMANAGER->findAnimation("R_IDLE");

											_bossAni->start();

											FOUR = 0;
										}
									}

									else if (_plyCenterX - _centerX > 100)
									{
										if (FOUR >= 2)
										{
											_bossState = R_MOVE;

											_bossImg = IMAGEMANAGER->findImage("BOSSMOVE");
											_bossAni = KEYANIMANAGER->findAnimation("R_MOVE");
											_bossAni->start();

											FOUR = 0;

										}
									}
								}
							}
						
					}
					break;
				//====================================================================//
			case R_SATK:
			{
				static float FIVE = 0;
				FIVE += TIMEMANAGER->getElapsedTime();


				if (_bossHp <= 0)
				{
					_bossState = R_DEAD;

					_bossImg = IMAGEMANAGER->findImage("DEAD");
					_bossAni = KEYANIMANAGER->findAnimation("RDEAD");
					_bossAni->start();
				}

				_isBossJumping = false;

				_boxCount++;

				_atkBoxCenterX = _centerX + 250;
				_atkBoxCenterY = _centerY;

				_swordBox      = RectMakeCenter(_atkBoxCenterX + 30, _atkBoxCenterY, 200, 200);

				EFFECTMANAGER->play("우검기", _atkBoxCenterX, _atkBoxCenterY - 20);
				EFFECTMANAGER->play("우검기", _atkBoxCenterX - 30, _atkBoxCenterY);
				EFFECTMANAGER->play("우검기", _atkBoxCenterX, _atkBoxCenterY + 20);

				if (_plyCenterX <= _centerX ||
					_plyCenterX >= _centerX)
				{

					if (_plyCenterX <= _centerX)
					{
						if (_centerX - _plyCenterX <= 30)
						{
							if (FIVE >= 1)
							{
								_bossState = L_BACK_MOVE;


								_bossImg = IMAGEMANAGER->findImage("BACK");
								_bossAni = KEYANIMANAGER->findAnimation("LBACK");
								_bossAni->start();

								FIVE = 0;
							}
						}

						else if (30 < _centerX - _plyCenterX < 100)
						{
							if (FIVE >= 2)
							{
								_bossState = L_SATK;

								_bossImg = IMAGEMANAGER->findImage("SWORD");
								_bossAni = KEYANIMANAGER->findAnimation("LSA");
								_bossAni->start();

								FIVE = 0;
							}
						}

						else if (_centerX - _plyCenterX >= 100)
						{
							if (FIVE >= 4)
							{
								_bossState = L_MOVE;

								_bossImg = IMAGEMANAGER->findImage("BOSSMOVE");
								_bossAni = KEYANIMANAGER->findAnimation("L_MOVE");
								_bossAni->start();


								FIVE = 0;
							}
						}
					}

					else if (_plyCenterX >= _centerX )
					{
						if (_plyCenterX - _centerX <= 30)
						{
							if (FIVE >= 1)
							{
								_bossState = R_SATK;

								_bossImg = IMAGEMANAGER->findImage("SWORD");
								_bossAni = KEYANIMANAGER->findAnimation("RSA");
								_bossAni->start();


								FIVE = 0;
							}

						}

						else if (30 < _plyCenterX - _centerX <= 100)
						{
							if (FIVE >= 1)
							{

								_bossState = R_MOVE;

								_bossImg = IMAGEMANAGER->findImage     ("BOSSMOVE");
								_bossAni = KEYANIMANAGER->findAnimation("R_MOVE");
								_bossAni->start();
							

								FIVE = 0;
							}
						}

						else if (_plyCenterX - _centerX > 100)
						{
							if (FIVE >= 1)
							{

								_bossState = R_GATK;

								_bossImg = IMAGEMANAGER->findImage("BOSS_GUN_ATK");
								_bossAni = KEYANIMANAGER->findAnimation("RG");

								_bossAni->start();

								BULLET->Shot("RGF", _centerX + 120, _centerY - 80, 0, 0.1f, 5);
								BULLET->Shot("RGF", _centerX + 100, _centerY - 30, 0, 0.1f, 5);
								BULLET->Shot("RGF", _centerX + 90, _centerY + 10, 0, 0.1f, 5);
								BULLET->Shot("RGF", _centerX + 120, _centerY - 10, 0, 0.1f, 5);
								BULLET->Shot("RGF", _centerX + 120, _centerY + 50, 0, 0.1f, 5);

								FIVE = 0;
							}
						}
						
					}
				}
			}
			break;
				//=======================================================================//
	        case L_GATK:
			{
				static float SIX = 0;
				SIX   += TIMEMANAGER->getElapsedTime();

				if (_bossHp <= 0)
				{
					_bossState = L_DEAD;

					_bossImg = IMAGEMANAGER->findImage("DEAD");
					_bossAni = KEYANIMANAGER->findAnimation("LDEAD");
					_bossAni->start();
				}

				_isBossJumping = false;

				_angle = getAngle(_centerX, _centerY, _plyCenterX, _plyCenterY);

				if (_plyCenterX <= _centerX ||
					_plyCenterX >= _centerX)
				{
					if (_plyCenterX <= _centerX)
					{
						if (_centerX - _plyCenterX < 30)
						{
							if (SIX >= 2)
							{
								_bossState = R_BACK_MOVE;

								_bossImg = IMAGEMANAGER->findImage("BACK");
								_bossAni = KEYANIMANAGER->findAnimation("RBACK");

								_bossAni->start();

								SIX = 0;
							}
						}

						else if (30 <= _centerX - _plyCenterX < 100)
						{
							if (SIX >= 2)
							{
								_bossState = R_BACK_MOVE;

								_bossImg = IMAGEMANAGER->findImage("BACK");
								_bossAni = KEYANIMANAGER->findAnimation("RBACK");

								_bossAni->start();

								SIX = 0;
							}
						}

						else if (_centerX - _plyCenterX >= 100)
						{
							if (SIX >= 2)
							{
								_bossState = L_MOVE;

								_bossImg = IMAGEMANAGER->findImage("BOSSMOVE");
								_bossAni = KEYANIMANAGER->findAnimation("L_MOVE");

								_bossAni->start();

								SIX = 0;
							}
						}
					}

					else if (_plyCenterX >= _centerX)
					{
						if (_plyCenterX - _centerX >= 100)
						{
							if (SIX >= 2)
							{
								_bossState = R_MOVE;

								_bossImg = IMAGEMANAGER->findImage("BOSSMOVE");
								_bossAni = KEYANIMANAGER->findAnimation("R_MOVE");

								_bossAni->start();

								SIX = 0;
							}
						}

						else if (30 < _plyCenterX - _centerX < 100)
						{
							if (SIX >= 1)
							{
								_bossState = R_MOVE;

								_bossImg = IMAGEMANAGER->findImage("BOSSMOVE");
								_bossAni = KEYANIMANAGER->findAnimation("R_MOVE");

								_bossAni->start();

								SIX = 0;
							}
						}

						else if (_plyCenterX - _centerX <= 30)
						{
							if (SIX >= 1)
							{
								_bossState = R_JUMP;

								_bossJumpPower    = 15.0f;
								_bossGravityPower = 0.3f;

								_bossImg = IMAGEMANAGER->findImage("JUMP");
								_bossAni = KEYANIMANAGER->findAnimation("RJ");

								_bossAni->start();
								
								SIX = 0;
							}
						}

					}
				}
			}
			break;
				//====================================================================//
			case R_BACK_MOVE:
			{
				static float SEVEN = 0;
				SEVEN += TIMEMANAGER->getElapsedTime();

				if (_bossHp <= 0)
				{
					_bossState = R_DEAD;

					_bossImg = IMAGEMANAGER->findImage("DEAD");
					_bossAni = KEYANIMANAGER->findAnimation("RDEAD");
					_bossAni->start();
				}

				_isBossJumping = false;

				if (_bossRc.right + BOSS_BACK <= 1300)
				{
					_centerX		+= BOSS_BACK;
					_bossRc.right	+= BOSS_BACK;
					_bossRc.left	+= BOSS_BACK;
				}

				if (_plyCenterX <= _centerX ||
					_plyCenterX >= _centerX)
				{
					if (_plyCenterX <= _centerX)
					{
						if(_centerX - _plyCenterX <= 30)
						{						
							if (SEVEN >= 2)
							{

								_bossState = R_SATK;

								_bossImg   = IMAGEMANAGER->findImage("SWORD");
								_bossAni   = KEYANIMANAGER->findAnimation("RSA");
								_bossAni->start();

								SEVEN = 0;
							}
						}

						else if (30 < _centerX - _plyCenterX < 100)
						{
							if (SEVEN >= 2)
							{
								_bossState = L_GATK;

								_bossImg   = IMAGEMANAGER->findImage("BOSS_GUN_ATK");
								_bossAni   = KEYANIMANAGER->findAnimation("LG");

								_bossAni->start();

								BULLET->Shot("LGF", _centerX - 100, _centerY - 30, PI, 0.1f, 5);
								BULLET->Shot("LGF", _centerX - 120, _centerY - 80, PI, 0.1f, 5);
								BULLET->Shot("LGF", _centerX - 120, _centerY - 10, PI, 0.1f, 5);
								BULLET->Shot("LGF", _centerX - 90, _centerY + 10, PI, 0.1f, 5);
								BULLET->Shot("LGF", _centerX - 120, _centerY + 50, PI, 0.1f, 5);

							}
						}
						else if (_centerX - _plyCenterX >= 100)
						{
							if (SEVEN >= 2)
							{
								_bossState = L_MOVE;

								_bossImg   = IMAGEMANAGER->findImage("BOSSMOVE");
								_bossAni   = KEYANIMANAGER->findAnimation("L_MOVE");

								_bossAni->start();

							}
						}
					}

					else if (_plyCenterX >= _centerX)
					{

						if (_plyCenterX - _centerX >= 100)
						{
							if (SEVEN >= 2)
							{
								_bossState = R_GATK;

								_bossImg   = IMAGEMANAGER->findImage("BOSS_GUN_ATK");
								_bossAni   = KEYANIMANAGER->findAnimation("RG");

								_bossAni->start();

								BULLET->Shot("RGF", _centerX + 120, _centerY - 10, 0, 0.1f, 5);
								BULLET->Shot("RGF", _centerX + 100, _centerY - 30, 0, 0.1f, 5);
								BULLET->Shot("RGF", _centerX + 120, _centerY - 80, 0, 0.1f, 5);
								BULLET->Shot("RGF", _centerX + 90, _centerY + 10, 0, 0.1f, 5);
								BULLET->Shot("RGF", _centerX + 120, _centerY + 50, 0, 0.1f, 5);


								SEVEN = 0;
							}
						}

						else if (_plyCenterX - _centerX < 30)
						{
							if (SEVEN >= 2)
							{
								_bossState = R_SATK;

								_bossImg   = IMAGEMANAGER->findImage("SWORD");
								_bossAni   = KEYANIMANAGER->findAnimation("RSA");
								_bossAni->start();


								SEVEN = 0;
							}
						}

						else if (30 <= _plyCenterX - _centerX < 100)
						{
							if (SEVEN >= 2)
							{
								_bossState = R_JUMP;

								_bossJumpPower = 15.0f;
								_bossGravityPower = 0.3f;

								_bossImg = IMAGEMANAGER->findImage("JUMP");
								_bossAni = KEYANIMANAGER->findAnimation("RJ");

								_bossAni->start();

								SEVEN = 0;
							}
						}
					}

				}
			}
			break;
			//====================================================================//
			case R_MOVE:
			{

				static float EIGHT = 0;
				EIGHT += TIMEMANAGER->getElapsedTime();
		
				if (_bossHp <= 0)
				{
					_bossState = R_DEAD;

					_bossImg = IMAGEMANAGER->findImage("DEAD");
					_bossAni = KEYANIMANAGER->findAnimation("RDEAD");
					_bossAni->start();
				}

				_isBossJumping = false;

				if (_bossRc.right + BOSS_BACK < 1304)
				{

					_centerX		+= BOSS_SPEED;
					_bossRc.right	+= BOSS_SPEED;
					_bossRc.left	+= BOSS_SPEED;

				}
				
						if (_centerX <= _plyCenterX ||
							_centerX >= _plyCenterX)
						{
							if (_centerX <= _plyCenterX)
							{
								if (_plyCenterX - _centerX <= 30)
								{
									if (EIGHT >= 1)
									{
										_bossState = R_SATK;

										_bossImg = IMAGEMANAGER->findImage("SWORD");
										_bossAni = KEYANIMANAGER->findAnimation("RSA");
										_bossAni->start();

										EIGHT = 0;
									}
								}

								else if (30 < _plyCenterX - _centerX < 100)
								{
									if (EIGHT >= 1)
									{
										_bossState = R_GATK;

										_bossImg = IMAGEMANAGER->findImage("BOSS_GUN_ATK");
										_bossAni = KEYANIMANAGER->findAnimation("RG");

										_bossAni->start();

										BULLET->Shot("RGF", _centerX + 120, _centerY - 10, 0, 0.1f, 5);
										BULLET->Shot("RGF", _centerX + 100, _centerY - 30, 0, 0.1f, 5);
										BULLET->Shot("RGF", _centerX + 120, _centerY - 80, 0, 0.1f, 5);
										BULLET->Shot("RGF", _centerX + 90, _centerY + 10, 0, 0.1f, 5);
										BULLET->Shot("RGF", _centerX + 120, _centerY + 50, 0, 0.1f, 5);

										EIGHT = 0;
									}
								}

								else if (_plyCenterX - _centerX >= 100)
								{
									if (EIGHT >= 1)
									{
										_bossState = R_JUMP;

										_bossImg = IMAGEMANAGER->findImage("JUMP");
										_bossAni = KEYANIMANAGER->findAnimation("RJ");
										_bossAni->start();

										EIGHT = 0;
									}
								}
							}

							else if (_centerX >= _plyCenterX)
							{
								if (_centerX - _plyCenterX >= 100)
								{
									if (EIGHT >= 1)
									{
										_bossState = R_GATK;

										_bossImg = IMAGEMANAGER->findImage("BOSS_GUN_ATK");
										_bossAni = KEYANIMANAGER->findAnimation("RG");

										_bossAni->start();

										BULLET->Shot("RGF", _centerX + 120, _centerY - 10, 0, 0.1f, 5);
										BULLET->Shot("RGF", _centerX + 100, _centerY - 30, 0, 0.1f, 5);
										BULLET->Shot("RGF", _centerX + 120, _centerY - 80, 0, 0.1f, 5);
										BULLET->Shot("RGF", _centerX + 90, _centerY + 10, 0, 0.1f, 5);
										BULLET->Shot("RGF", _centerX + 120, _centerY + 50, 0, 0.1f, 5);


										EIGHT = 0;

									}
								}
								else if (50 < _centerX - _plyCenterX < 100)
								{
									if (EIGHT >= 3)
									{
										_bossState = L_SATK;

										_bossImg = IMAGEMANAGER->findImage("SWORD");
										_bossAni = KEYANIMANAGER->findAnimation("LSA");
										_bossAni->start();

										EIGHT = 0;
									}
								}

								else  if (_centerX - _plyCenterX <= 50)
								{
									if (EIGHT >= 1)
									{
										_bossState = L_JUMP;

										_bossImg = IMAGEMANAGER->findImage("JUMP");
										_bossAni = KEYANIMANAGER->findAnimation("LJ");
										_bossAni->start();
									}
								}
							}
						}
					
			}
			break;
			//====================================================================//
			case R_GATK:
			{
				static float NINE = 0;
				NINE += TIMEMANAGER->getElapsedTime();

				if (_bossHp <= 0)
				{
					_bossState = R_DEAD;

					_bossImg = IMAGEMANAGER->findImage("DEAD");
					_bossAni = KEYANIMANAGER->findAnimation("RDEAD");
					_bossAni->start();
				}

				_isBossJumping = false;

				_angle = getAngle(_centerX, _centerY, _plyCenterX, _plyCenterY);

				if (_plyCenterX <= _centerX ||
					_plyCenterX >= _centerX)
				{
					if (_plyCenterX <= _centerX)
					{
						if (_centerX - _plyCenterX <= 30)
						{
							if (NINE >= 2)
							{
								_bossState = L_JUMP;

								_bossJumpPower = 15.0f;
								_bossGravityPower = 0.3f;
								
								_bossImg = IMAGEMANAGER->findImage("JUMP");
								_bossAni = KEYANIMANAGER->findAnimation("LJ");

								_bossAni->start();

								NINE = 0;
							}
						}

						else if (30 < _centerX - _plyCenterX < 100)
						{
							if (NINE >= 2)
							{
									_bossState = L_JUMP;

									_bossJumpPower = 15.0f;
									_bossGravityPower = 0.3f;
									

									_bossImg = IMAGEMANAGER->findImage("JUMP");
									_bossAni = KEYANIMANAGER->findAnimation("LJ");

									_bossAni->start();

									NINE = 0;
							}
						}

						else if (_centerX - _plyCenterX >= 100)
						{
							if (NINE >= 2)
							{
								_bossState = L_MOVE;

								_bossImg = IMAGEMANAGER->findImage("BOSSMOVE");
								_bossAni = KEYANIMANAGER->findAnimation("LMOVE");
								_bossAni->start();

								NINE = 0;
							}
						}
					}

					else if (_plyCenterX >= _centerX)
					{
						if (_plyCenterX - _centerX >= 100)
						{
							if (NINE >= 2)
							{
								_bossState = R_MOVE;

								_bossImg = IMAGEMANAGER->findImage("BOSSMOVE");
								_bossAni = KEYANIMANAGER->findAnimation("R_MOVE");

								_bossAni->start();


								NINE = 0;
							}
						}

						else if (60 <= _plyCenterX - _centerX < 100)
						{
							if (NINE >= 3)
							{

								_bossState = R_IDLE;

								_bossImg = IMAGEMANAGER->findImage("BOSS");
								_bossAni = KEYANIMANAGER->findAnimation("R_IDLE");

								_bossAni->start();


								NINE = 0;
							}
						}

						else if (_plyCenterX - _centerX < 60)
						{
							if (NINE >= 1)
							{
								_bossState = R_BACK_MOVE;

								_bossImg = IMAGEMANAGER->findImage("BACK");
								_bossAni = KEYANIMANAGER->findAnimation("RBACK");

								_bossAni->start();

								NINE = 0;

							}
						}
					}
				}
			}
			break;
			//====================================================================//	
			//====================================================================//
			case R_JUMP:
			{
				static float TWEL = 0;
				TWEL    += TIMEMANAGER->getElapsedTime();

				if (_bossHp <= 0)
				{
					_bossState = R_DEAD;

					_bossImg = IMAGEMANAGER->findImage("DEAD");
					_bossAni = KEYANIMANAGER->findAnimation("RDEAD");
					_bossAni->start();
				}
				_isBossJumping   = true;

				_bossRc.top		-= _bossJumpPower;
				_bossRc.bottom  -= _bossJumpPower;
				_bossJumpPower  -= _bossGravityPower;
				


				//_bossRc = RectMakeCenter(_centerX, _centerY, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());

				if (_bossJumpPower <= 0)//(TWEL >= 1)//(_bossJumpPower <= 0)////|| _bossRc.top >= CAM->getCamRc().top + 10)
				{
					_bossState = R_STAY;

					_bossImg = IMAGEMANAGER->findImage("STAY");
					_bossAni = KEYANIMANAGER->findAnimation("RJS");

					_bossAni->start();

					_centerX = _bossRc.left + (_bossRc.right - _bossRc.left) / 2;
					_centerY = _bossRc.top + (_bossRc.bottom - _bossRc.top) / 2;

					BULLET->Shot("CC",  _centerX  -10, _centerY + 50, _angle,         0, 6);
					BULLET->Shot("CC1", _centerX  -10, _centerY + 70, PI / 3 * 4,     0, 5);
					BULLET->Shot("CC2", _centerX - 10, _centerY + 60, PI / 6 * 9,     0, 6);
					BULLET->Shot("CC3", _centerX - 10, _centerY + 60, PI / 3 * 5,     0, 6);
				
					TWEL = 0;
				}
			}
			break;
			//====================================================================//
			case R_STAY:
			{
				static float STAY = 0;
				STAY += TIMEMANAGER->getElapsedTime();

				if (_bossHp <= 0)
				{
					_bossState = R_DEAD;

					_bossImg = IMAGEMANAGER->findImage("DEAD");
					_bossAni = KEYANIMANAGER->findAnimation("RDEAD");
					_bossAni->start();
				}

				_isBossJumping = false;

				_bossJumpPower    = 0;
				_bossGravityPower = 0;

				if (STAY >= 4)
				{
					_bossState = R_FALL;


					
					_bossImg = IMAGEMANAGER->findImage("FALL");
					_bossAni = KEYANIMANAGER->findAnimation("RJF");

					_bossAni->start();

					STAY = 0;
				}
			}
			break;
			//====================================================================//
			case R_FALL:
			{

				static float RFALL = 0;
				RFALL += TIMEMANAGER->getElapsedTime();

				if (_bossHp <= 0)
				{
					_bossState = R_DEAD;

					_bossImg = IMAGEMANAGER->findImage("DEAD");
					_bossAni = KEYANIMANAGER->findAnimation("RDEAD");
					_bossAni->start();
				}

				_bossJumpPower = 0.0f;
				_bossGravityPower = 5.0f;
				_bossRc.top    += _bossGravityPower;
				_bossRc.bottom += _bossGravityPower;

				if (_plyCenterX <= _centerX ||
					_plyCenterX >= _centerX)
				{
						if (_bossPixelCol->RayCastingDownY(IMAGEMANAGER->findImage("보스방충돌맵")->getMemDC(), 255, 0, 0))
						{
							_bossPixelCol->setPosDownY(_centerY);
							
							_bossGravityPower = 0.0f;

							_bossState = R_IDLE;


							_bossImg = IMAGEMANAGER->findImage("BOSS");
							_bossAni = KEYANIMANAGER->findAnimation("R_IDLE");

							_bossAni->start();
						}
				}
			}
			break;
			//====================================================================//

			case L_JUMP:
			{
				static float THIR = 0;
				THIR += TIMEMANAGER->getElapsedTime();

				_isBossJumping   = true;

				if (_bossHp <= 0)
				{
					_bossState = L_DEAD;

					_bossImg = IMAGEMANAGER->findImage("DEAD");
					_bossAni = KEYANIMANAGER->findAnimation("LDEAD");
					_bossAni->start();
				}

				_bossRc.top		-= _bossJumpPower;
				_bossRc.bottom  -= _bossJumpPower;
				_bossJumpPower  -= _bossGravityPower;

				//_bossRc = RectMakeCenter(_centerX, _centerY, _bossImg->getFrameWidth(), _bossImg->getFrameHeight());

				if (_bossJumpPower <= 0) //(THIR >= 2 )//|| _bossRc.top >= CAM->getCamRc().top + 10)
				{
					_bossState = L_STAY;

					_isBossJumping == false;

					_bossImg = IMAGEMANAGER->findImage("STAY");
					_bossAni = KEYANIMANAGER->findAnimation("LJS");

					_bossAni->start();

					_centerX = _bossRc.left + (_bossRc.right - _bossRc.left) / 2;
					_centerY = _bossRc.top  + (_bossRc.bottom - _bossRc.top) / 2;

					BULLET->Shot("CC",  _centerX  -10,  _centerY + 50, _angle,         0, 6);
					BULLET->Shot("CC1",  _centerX  -10,  _centerY + 70, PI / 3 * 4,     0, 5);
					BULLET->Shot("CC2",  _centerX - 10,  _centerY + 60, PI / 6 * 9,     0, 6);
					BULLET->Shot("CC3",  _centerX - 10,  _centerY + 60, PI / 3 * 5,     0, 6);

					THIR = 0;
				}
			}
			break;
			//====================================================================//
			case L_STAY:
			{
				static float LSTAY = 0;
				LSTAY += TIMEMANAGER->getElapsedTime();

				_isBossJumping = false;

				if (_bossHp <= 0)
				{
					_bossState = L_DEAD;

					_bossImg = IMAGEMANAGER->findImage("DEAD");
					_bossAni = KEYANIMANAGER->findAnimation("LDEAD");
					_bossAni->start();
				}

				_bossJumpPower    = 0;
				_bossGravityPower = 0;

				if (LSTAY >= 4)
				{
					_bossState = L_FALL;
					
					_bossImg = IMAGEMANAGER->findImage("FALL");
					_bossAni = KEYANIMANAGER->findAnimation("LJF");

					_bossAni->start();

					LSTAY = 0;
				}
			}
			break;
			//====================================================================//
			case L_FALL:
			{
				static float LFALL = 0;
				LFALL += TIMEMANAGER->getElapsedTime();

				if (_bossHp <= 0)
				{
					_bossState = L_DEAD;

					_bossImg = IMAGEMANAGER->findImage("DEAD");
					_bossAni = KEYANIMANAGER->findAnimation("LDEAD");
					_bossAni->start();
				}

				_bossJumpPower = 0.0f;
				_bossGravityPower = 5.0f;

				_bossRc.top    += _bossGravityPower;
				_bossRc.bottom += _bossGravityPower;
				

				if (_plyCenterX <= _centerX ||
					_plyCenterX >= _centerX)
				{

				
						if (_bossPixelCol->RayCastingDownY(IMAGEMANAGER->findImage("보스방충돌맵")->getMemDC(), 255, 0, 0))
						{
							
								_bossPixelCol->setPosDownY(_centerY);
								

								_bossJumpPower = 0.0f;
								_bossGravityPower = 0.0f;

									_bossState = L_IDLE;


									_bossImg = IMAGEMANAGER->findImage("BOSS");
									_bossAni = KEYANIMANAGER->findAnimation("L_IDLE");

									_bossAni->start();
								
								
				

						}
				}
			}
			break;
			//=========================================================================//
			case R_IDLE:
			{
				static float END = 0;
				END += TIMEMANAGER->getElapsedTime();

				if (_bossHp <= 0)
				{
					_bossState = R_DEAD;

					_bossImg = IMAGEMANAGER->findImage("DEAD");
					_bossAni = KEYANIMANAGER->findAnimation("RDEAD");
					_bossAni->start();
				}

				_isBossJumping = false;

				if (_plyCenterX <= _centerX ||
					_plyCenterX >= _centerX)
				{
					if (_plyCenterX >= _centerX)
					{
						if (END >= 1)
						{
							if (_plyCenterX - _centerX < 30)
							{
								_bossState = R_BACK_MOVE;

								_bossImg = IMAGEMANAGER->findImage("BACK");
								_bossAni = KEYANIMANAGER->findAnimation("RBACK");

								_bossAni->start();
								END = 0;
							}

							else if (30 <= _plyCenterX - _centerX < 100)
							{
								_bossState = R_MOVE;

								_bossImg = IMAGEMANAGER->findImage("BOSSMOVE");
								_bossAni = KEYANIMANAGER->findAnimation("R_MOVE");

								_bossAni->start();

								END = 0;
							}


							else if (_plyCenterX - _centerX >= 100)
							{
								_bossState = R_MOVE;

								_bossImg = IMAGEMANAGER->findImage("BOSSMOVE");
								_bossAni = KEYANIMANAGER->findAnimation("R_MOVE");

								_bossAni->start();

								END = 0;
							}
						}
					}

					else if (_plyCenterX <= _centerX)
					{
						if (END >= 1)
						{
							if (_centerX - _plyCenterX > 100)
							{
								_bossState = L_MOVE;

								_bossImg = IMAGEMANAGER->findImage("BOSSMOVE");
								_bossAni = KEYANIMANAGER->findAnimation("L_MOVE");

								_bossAni->start();
								END = 0;
							}

							else if (30 < _centerX - _plyCenterX <= 100)
							{
								_bossState = L_IDLE;

								_bossImg = IMAGEMANAGER->findImage("BOSS");
								_bossAni = KEYANIMANAGER->findAnimation("L_IDLE");

								_bossAni->start();

								END = 0;
							}


							else if (_centerX - _plyCenterX <= 30)
							{
								_bossState = R_BACK_MOVE;

								_bossImg = IMAGEMANAGER->findImage("BACK");
								_bossAni = KEYANIMANAGER->findAnimation("RBACK");

								_bossAni->start();

								END = 0;
							}

						}
					}

				}
			}
			break;

			case R_DEAD : 
			{

			}
			break;
			case L_DEAD :
			{

			}
			break;
	    }
	
    }		
 

}



void Boss::SpecialAtk()
{
	_specialAtkCount++;
}


void Boss::OtherRender()
{
	/*예외처리*/
	if (_bossState      == L_IDLE)
	{
		_bossImg->aniRender(getMemDC(), _bossRc.left, _bossRc.top, _bossAni);
	}

	else if (_bossState == R_GATK)
	{
		_bossImg->aniRender(getMemDC(), _bossRc.left - 30, _bossRc.top, _bossAni);
	}

	else if (_bossState == L_GATK)
	{
		_bossImg->aniRender(getMemDC(), _bossRc.left - 30, _bossRc.top, _bossAni);
	}

	else if (_bossState == L_SATK)
	{
		_bossImg->aniRender(getMemDC(), _bossRc.left - 110, _bossRc.top, _bossAni);
	}

	else if (_bossState == R_SATK)
	{
		_bossImg->aniRender(getMemDC(), _bossRc.left, _bossRc.top, _bossAni);
	}
	
	else if (_bossState == L_MOVE)
	{
		_bossImg->aniRender(getMemDC(), _bossRc.left, _bossRc.top, _bossAni);
	}
	else if (_bossState == L_DEAD)
	{
		_bossImg->aniRender(getMemDC(), _bossRc.left, _bossRc.top + 120, _bossAni);
	}
	else if (_bossState == R_DEAD)
	{
		_bossImg->aniRender(getMemDC(), _bossRc.left, _bossRc.top + 120, _bossAni);
	}
	else
	{
		_bossImg->aniRender(getMemDC(), _bossRc.left, _bossRc.top, _bossAni);
	}

}


void Boss::CreateAtkBox()
{
	if (_bossState  == R_SATK)
	{
		_boxCount++;
		_swordBox = RectMakeCenter(_atkBoxCenterX + 30, _atkBoxCenterY, 200, 200);
	}

	 if (_bossState == L_SATK)
	{
		_boxCount++;
		_swordBox = RectMakeCenter(_atkBoxCenterX,      _atkBoxCenterY, 200, 200);
	}

	 if (_boxCount == 0)
	 {
		 _swordBox = RectMakeCenter(-2000, -2000, 0, 0);
	 }

}







