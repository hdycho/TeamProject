#include "stdafx.h"
#include "player.h"
#include "Store.h"
#include "PlayerUI.h"


player::player()
{
}


player::~player()
{
}

HRESULT player::init()
{
	_run = IMAGEMANAGER->addFrameImage("run", PathFile("image", "run_sprite").c_str(), 700, 112, 10, 2, true, RGB(255, 0, 255));
	_stand = IMAGEMANAGER->addFrameImage("stand", PathFile("image", "stand_sprite").c_str(), 70, 112, 1, 2, true, RGB(255, 0, 255));
	_jump = IMAGEMANAGER->addFrameImage("jump", PathFile("image", "jump_sprite").c_str(), 603, 144, 9, 2, true, RGB(255, 0, 255));
	_attack = IMAGEMANAGER->addFrameImage("attack", PathFile("image", "attack_sprite").c_str(), 2700, 172, 19, 2, true, RGB(255, 0, 255));

	_knight.x = 600;
	_knight.y = 200;

	// Skill_Heal image
	_knightHeal.img = IMAGEMANAGER->addFrameImage("knightHeal", PathFile("image", "healing_sprite").c_str(), 1020, 233, 10, 1, true, RGB(255, 0, 255));
	_knightHeal.rc = RectMakeCenter(_knight.x, _knight.y, _knightHeal.img->getFrameWidth(), _knightHeal.img->getFrameHeight());
	// Skill_Heal bool
	_isSkillHeal = false;

	// Skill_1 images
	_skill_1 = IMAGEMANAGER->addFrameImage("skill1", PathFile("image", "Skill1_sprite").c_str(), 1850, 180, 11, 2, true, RGB(255, 0, 255));
	_bulletSwordRight = IMAGEMANAGER->addFrameImage("knightBulletRight", PathFile("image", "Skill1_bullet_right_sprite").c_str(), 45, 17, 1, 1, true, RGB(255, 0, 255));
	_bulletSwordLeft = IMAGEMANAGER->addFrameImage("knightBulletLeft", PathFile("image", "Skill1_bullet_left_sprite").c_str(), 45, 17, 1, 1, true, RGB(255, 0, 255));
	// for _bulletSword (bullet)
	BULLET->BulletSetting("bulletSwordRight", IMAGEMANAGER->findImage("knightBulletRight"), 30, true, 1);
	BULLET->BulletSetting("bulletSwordLeft", IMAGEMANAGER->findImage("knightBulletLeft"), 30, true, 1);

	// Skill_2 image,position
	_skill_2_Right.img = IMAGEMANAGER->addFrameImage("skill2Right", PathFile("image", "Skill2_sprite").c_str(), 2520, 1500, 12, 1, true, RGB(255, 0, 255));
	_skill_2_Left.img = IMAGEMANAGER->addFrameImage("skill2Left  ", PathFile("image", "Skill2_sprite").c_str(), 2520, 1500, 12, 1, true, RGB(255, 0, 255));
	_spin = IMAGEMANAGER->addFrameImage("spin", PathFile("image", "spin_sprite").c_str(), 620, 119, 8, 1, true, RGB(255, 0, 255));
	_tornado = IMAGEMANAGER->addFrameImage("tornado", PathFile("image", "tornado_sprite").c_str(), 500, 118, 5, 1, true, RGB(255, 0, 255));
	// Skill_2 rect
	_skill_2_Right.rc = RectMakeCenter(_skill_2_Right.x, _skill_2_Right.y, _skill_2_Right.img->getFrameWidth(), _skill_2_Right.img->getFrameHeight());
	_skill_2_Left.rc = RectMakeCenter(_skill_2_Left.x, _skill_2_Left.y, _skill_2_Left.img->getFrameWidth(), _skill_2_Left.img->getFrameHeight());
	// Skill_2 bool
	_isSkill2 = false;
	_isAvailable2 = false;

	_knight.img = _stand;
	_knightDirection = RIGHT_STAND;

	_knight.rc = RectMakeCenter(_knight.x, _knight.y, _knight.img->getFrameWidth(), _knight.img->getFrameX());

	_count = _index = _indexExtra = _indexHeal = 0;
	_countAttack = 0;
	_countSkill = 0;
	_countSkill2 = 0;
	_countHeal = 0;

	_speed = KNIGHTSPEED;

	// for Jump
	_jumpPower = 0.0f;
	_gravity = 0.1f;
	_isJump = false;

	// for Attack
	_isAttack = false;
	pCol = new PixelCol;

	pCol->init(20, 20);

	//====== Skill ======
	_skill = new Skill;
	_skill->init();

	// player (money)
	_money = 4000;

	_playerHP = 100;
	_playerMP = 100;

	return S_OK;
}

void player::release()
{
}

void player::update(HDC hdc)
{
	// idle
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_knightDirection = RIGHT_STAND;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_knightDirection = LEFT_STAND;
	}
	// move
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_knightDirection = RIGHT_RUN;
		_knight.x += _speed;
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_knightDirection = LEFT_RUN;
		_knight.x -= _speed;
	}
	// (speed reset) for 벽 충돌
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_speed = KNIGHTSPEED;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		_speed = KNIGHTSPEED;
	}

	// jump 함수
	knightJump(); // Key: W

	 // attack 함수
	knightAttack(); // Key : F

	// Skill_1 함수
	knightSkill_1(); // key : Q
	// Skill_Heal 함수
	knightSkill_Heal(); // Key : W
	// Skill_2 함수
	knightSkill_2(); // key : E

	// for player's MP
	if (_playerMP >= 100)
	{
		_playerMP = 100;
	}
	else _playerMP += 0.1f;
	// for player's HP
	if (_playerHP >= 100)
	{
		_playerHP = 100;
	}
	if (_playerHP <= 0)
	{
		_playerHP = 0;
	}

	// 메타나이트 FrameImage
	_count++;
	if (_count > 4)
	{
		if (_knightDirection == RIGHT_STAND)
		{
			_knight.img = _stand;
			_knight.img->setFrameY(0);
			_knight.img->setFrameX(0);
		}
		else if (_knightDirection == LEFT_STAND)
		{
			_knight.img = _stand;
			_knight.img->setFrameY(1);
			_knight.img->setFrameX(0);
		}
		else if (_knightDirection == RIGHT_RUN)
		{
			_knight.img = _run;
			_knight.img->setFrameY(0);
			_knight.img->setFrameX(_index);
			_index++;
			if (_index > 9) _index = 0;
		}
		else if (_knightDirection == LEFT_RUN)
		{
			_knight.img = _run;
			_knight.img->setFrameY(1);
			_knight.img->setFrameX(_index);
			_index--;
			if (_index < 0) _index = 9;
		}
		else if (_knightDirection == RIGHT_JUMP)
		{
			_knight.img = _jump;
			_knight.img->setFrameY(0);
			_knight.img->setFrameX(_index);
			_index++;
			if (_index > 8) _index = 8;
		}
		else if (_knightDirection == LEFT_JUMP)
		{
			_knight.img = _jump;
			_knight.img->setFrameY(1);
			_knight.img->setFrameX(_index);
			_index--;
			if (_index < 0) _index = 0;
		}
		if (_isSkill2 == true)
		{
			_skill_2_Right.img->setFrameX(_indexExtra);
			_skill_2_Left.img->setFrameX(_indexExtra);
			_indexExtra++;
			if (_indexExtra > 11)
			{
				_indexExtra = 4;
				_countSkill2++;

				if (_countSkill2 == 4)
				{
					_skill_2_Right.x = _knight.x - 100; // skill_2_Right 'x' position
					_skill_2_Right.y = _knight.y; // skill_2_Right 'y' position
					_skill_2_Left.x = _knight.x - 100; // skill_2_Right 'x' position
					_skill_2_Left.y = _knight.y; // skill_2_Right 'y' position

					_index = 0;
					_countSkill2 = 0;
					_knightDirection = RIGHT_STAND;
					_isSkill2 = false;
				}
			}
		}
		if (_isSkillHeal == true)
		{
			_knightHeal.img->setFrameX(_indexHeal);
			_indexHeal++;
			if (_indexHeal == 9)
			{
				_indexHeal = 0;
				_isSkillHeal = false;
			}
		}

		_count = 0;
	}

	_countAttack++;
	if (_countAttack > 2)
	{
		if (_knightDirection == RIGHT_ATTACK)
		{
			_knight.img = _attack;
			_knight.img->setFrameY(0);
			_knight.img->setFrameX(_index);
			_index++;
			if (_index >= 18)
			{
				_isAttack = false;
				_knightDirection = RIGHT_STAND;
				_index = 0;
			}
		}
		else if (_knightDirection == LEFT_ATTACK)
		{
			_knight.img = _attack;
			_knight.img->setFrameY(1);
			_knight.img->setFrameX(_index);
			_index--;
			if (_index < 0)
			{
				_isAttack = false;
				_knightDirection = LEFT_STAND;
				_index = 18;
			}
		}
		else if (_knightDirection == RIGHT_SKILL1)
		{
			_knight.img = _skill_1;
			_knight.img->setFrameY(0);
			_knight.img->setFrameX(_index);
			_index++;
			if (_index > 10)
			{
				_knightDirection = RIGHT_STAND;
				_index = 0;
			}
		}
		else if (_knightDirection == LEFT_SKILL1)
		{
			_knight.img = _skill_1;
			_knight.img->setFrameY(1);
			_knight.img->setFrameX(_index);
			_index--;
			if (_index < 0)
			{
				_knightDirection = LEFT_STAND;
				_index = 10;
			}
		}
		else if (_knightDirection == KNIGHT_SPIN)
		{
			_knight.img = _spin;
			_knight.img->setFrameX(_index);
			_index++;
			if (_index > 7)
			{
				_index = 0;
				_knightDirection = KNIGHT_TORNADO;
			}
		}
		else if (_knightDirection == KNIGHT_TORNADO)
		{
			_skill_2_Right.rc = RectMakeCenter(_skill_2_Right.x, _skill_2_Right.y, 100, 1000);
			_skill_2_Left.rc = RectMakeCenter(_skill_2_Left.x, _skill_2_Left.y, 100, 1000);
			_knight.img = _tornado;
			_knight.img->setFrameX(_index);
			_index++;
			if (_index == 4)
			{
				_index = 0;
				_countSkill++;

				if (_countSkill == 4)
				{
					_skill_2_Right.rc = RectMakeCenter(_skill_2_Right.x, _skill_2_Right.y, 100, 1000);
					_skill_2_Left.rc = RectMakeCenter(_skill_2_Left.x, _skill_2_Left.y, 100, 1000);
					_countSkill = 0;
					_isSkill2 = true;
				}
			}
		}

		_countAttack = 0;
	}
	PlayerCollision(hdc);
	_knight.rc = RectMakeCenter(_knight.x, _knight.y, _knight.img->getFrameWidth(), _knight.img->getFrameHeight());
	_knightHeal.rc = RectMakeCenter(_knight.x + 3, _knight.y - 14, _knightHeal.img->getFrameWidth(), _knightHeal.img->getFrameHeight());
	pCol->UpdatePosition(GetCenterPos(_knight.rc).x, GetCenterPos(_knight.rc).y);

	_skill->update();
	_Ui->update();

	// player HP/MP
	_Ui->SetHpLine(_playerHP, 100);
	_Ui->SetPtLine(_playerMP, 100);
}

void player::render()
{
	_knight.img->frameRender(getMemDC(), _knight.rc.left, _knight.rc.top);
	_skill->render();

	if (_isSkillHeal == true)
	{
		_knightHeal.img->frameRender(getMemDC(), _knightHeal.rc.left, _knightHeal.rc.top);
	}
	if (_isSkill2 == true)
	{
		_skill_2_Right.img->frameRender(getMemDC(), _skill_2_Right.rc.left + 30, _skill_2_Right.rc.top - 30);
		_skill_2_Left.img->frameRender(getMemDC(), _skill_2_Left.rc.left + 30, _skill_2_Left.rc.top - 30);
	}

	_Ui->render();
}

void player::knightJump()
{
	// stand,move 방향에 따른 jump 방향/jump 키
	if (_knightDirection == RIGHT_STAND || _knightDirection == RIGHT_RUN)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_index = 0;
			_gravity = 0.1f;
			_jumpPower = 5.0f;
			_knightDirection = RIGHT_JUMP;
			_isJump = true;
		}
	}
	if (_knightDirection == LEFT_STAND || _knightDirection == LEFT_RUN)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
		{
			_index = 8;
			_gravity = 0.1f;
			_jumpPower = 5.0f;
			_knightDirection = LEFT_JUMP;
			_isJump = true;
		}
	}

	_knight.y -= _jumpPower;
	_jumpPower -= _gravity;

	// jump
	if (_isJump == true)
	{
		// jump 도중 move 했을때
		if (_knightDirection == RIGHT_RUN)
		{
			_knightDirection = RIGHT_JUMP;
		}
		if (_knightDirection == LEFT_RUN)
		{
			_knightDirection = LEFT_JUMP;
		}
	}
}

void player::knightAttack()
{
	// stand,move 방향에 따른 attack 방향/attack 키
	if (_knightDirection == RIGHT_STAND || _knightDirection == RIGHT_RUN)
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_isAttack = true;
			_index = 0;
			_knightDirection = RIGHT_ATTACK;
			_skill->makeSlash(_knight.x, _knight.y, 40, false);
		}
	}
	if (_knightDirection == LEFT_STAND || _knightDirection == LEFT_RUN)
	{
		if (KEYMANAGER->isOnceKeyDown('F'))
		{
			_isAttack = true;
			_index = 18;
			_knightDirection = LEFT_ATTACK;
			_skill->makeSlash(_knight.x, _knight.y, 40, true);
		}
	}

	//// 공격을 멈췄을때
	//if (_knightDirection == RIGHT_ATTACK)
	//{
	//	if (KEYMANAGER->isOnceKeyUp('F'))
	//	{
	//		_index = 0;
	//		_isAttack = false;
	//	}
	//}
	//if (_knightDirection == LEFT_ATTACK)
	//{
	//	if (KEYMANAGER->isOnceKeyUp('F'))
	//	{
	//		_index = 18;
	//		_isAttack = false;
	//	}
	//}
	

	// attack
	if (_isAttack == true)
	{
		if (_knightDirection == RIGHT_STAND)
		{
			_knightDirection = RIGHT_ATTACK;
			_attackRange.rc = RectMakeCenter(_knight.x + 30, _knight.y, 80, 50);
		}
		if (_knightDirection == LEFT_STAND)
		{
			_knightDirection = LEFT_ATTACK;
			_attackRange.rc = RectMakeCenter(_knight.x - 30, _knight.y, 80, 50);
		}
		//// move 도중 attack 했을때
		//if (_knightDirection == RIGHT_RUN)
		//{
		//	_index = 0;
		//	_knightDirection = RIGHT_ATTACK;
		//}
		//if (_knightDirection == LEFT_RUN)
		//{
		//	_index = 18;
		//	_knightDirection = LEFT_ATTACK;
		//}
	}
	if (_isAttack == false)
	{
		if (_knightDirection == RIGHT_ATTACK)
		{
			_knightDirection = RIGHT_STAND;
		}
		if (_knightDirection == LEFT_ATTACK)
		{
			_knightDirection = LEFT_STAND;
		}
	}
}

void player::knightSkill_1()
{
	// stand,move 방향에 따른 bullet 방향
	if (_knightDirection == RIGHT_STAND || _knightDirection == RIGHT_RUN || _knightDirection == RIGHT_JUMP)
	{
		if (KEYMANAGER->isOnceKeyDown('Q'))
		{
			_knightDirection = RIGHT_SKILL1;
			BULLET->Shot("bulletSwordRight", _knight.x, _knight.y, 0, 0, 10);
			BULLET->Shot("bulletSwordRight", _knight.x, _knight.y - 15, 0, 0, 10);
			
			// for player's MP
			_playerMP -= 10;
		}
	}
	if (_knightDirection == LEFT_STAND || _knightDirection == LEFT_RUN || _knightDirection == LEFT_JUMP)
	{
		if (KEYMANAGER->isOnceKeyDown('Q'))
		{
			_knightDirection = LEFT_SKILL1;
			BULLET->Shot("bulletSwordLeft", _knight.x, _knight.y, PI, 0, 10);
			BULLET->Shot("bulletSwordLeft", _knight.x, _knight.y - 15, PI, 0, 10);
		
			// for player's MP
			_playerMP -= 10;
		}
	}
}

void player::knightSkill_Heal()
{
	if (_isAvailableHeal == true)
	{
		_Ui->setSkillHealUIBool(true);

		if (_playerMP >= 20)
		{
			if (KEYMANAGER->isOnceKeyDown('W'))
			{
				_isSkillHeal = true;
				_playerHP += 20;

				_Ui->setSkillHealUIBool(true);
				_Ui->_frameSkillW = true;
				_Ui->_indexHeal = 0;

				// for player's MP
				_playerMP -= 20;
			}
		}
	}
}

void player::knightSkill_2()
{
	if (_isAvailable2 == true)
	{
		_Ui->setSkill2UIBool(true);

		if (_playerMP >= 100)
		{
			if (KEYMANAGER->isOnceKeyDown('E'))
			{
				_skill_2_Right.x = _knight.x - 100; // skill_2_Right 'x' position
				_skill_2_Right.y = _knight.y; // skill_2_Right 'y' position
				_skill_2_Left.x = _knight.x - 100; // skill_2_Right 'x' position
				_skill_2_Left.y = _knight.y; // skill_2_Right 'y' position

				_knightDirection = KNIGHT_SPIN;

				_Ui->setSkill2UIBool(true);
				_Ui->_frameSkillE = true;
				_Ui->_index = 0;

				// for player's MP
				_playerMP -= 100;
			}
		}
	}
	if (_isSkill2 == true)
	{
		_skill_2_Right.x += 3;
		_skill_2_Left.x -= 3;

		_skill_2_Right.rc = RectMakeCenter(_skill_2_Right.x, _skill_2_Right.y, 100, 1000);
		_skill_2_Left.rc = RectMakeCenter(_skill_2_Left.x, _skill_2_Left.y, 100, 1000);
	}
}

void player::PlayerCollision(HDC hdc)
{
	// 바닥충돌
	if (pCol->RayCastingDownY(hdc, 255, 0, 0))
	{
		if (_jumpPower <= 0)
		{
			pCol->setPosDownY(_knight.y);
			_isJump = false;

			_jumpPower = 0.0f;
			_gravity = 0;

			if (_knightDirection == RIGHT_JUMP)
			{
				_knightDirection = RIGHT_STAND;
				_index = 0;
			}
			if (_knightDirection == LEFT_JUMP)
			{
				_knightDirection = LEFT_STAND;
				_index = 8;
			}
		}
	}
	else
	{
		_gravity = 0.1f;
	}

	// 천장충돌
	if (pCol->RayCastingUpY(hdc, 255, 0, 0))
	{
		if (_jumpPower > 0)
		{
			pCol->setPosUpY(_knight.y);

			_jumpPower = 0;
		}
	}

	// 벽 충돌
	if (pCol->RayCastingX(hdc, 0, 0, 255, 0))
	{
		if (_knightDirection == RIGHT_RUN || _knightDirection == RIGHT_JUMP)
		{
			_speed = 0;
			_knight.x -= 4;
		}
		if (_knightDirection == LEFT_RUN || _knightDirection == LEFT_JUMP)
		{
			_speed = 0;
			_knight.x += 4;
		}
	}
}