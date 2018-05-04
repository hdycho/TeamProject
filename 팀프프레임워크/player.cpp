#include "stdafx.h"
#include "player.h"
#include "Store.h"


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

	_playerX = 600;
	_playerY = 200;

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

	_knight.rc = RectMakeCenter(_playerX, _playerY, _knight.img->getFrameWidth(), _knight.img->getFrameX());

	_count = _index = _indexExtra = 0;
	_countAttack = 0;
	_countSkill = 0;
	_countSkill2 = 0;

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
	_money = 2000;

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	// idle
	if (KEYMANAGER->isOnceKeyUp('D'))
	{
		_knightDirection = RIGHT_STAND;
	}
	if (KEYMANAGER->isOnceKeyUp('A'))
	{
		_knightDirection = LEFT_STAND;
	}
	// move
	if (KEYMANAGER->isStayKeyDown('D'))
	{
		_knightDirection = RIGHT_RUN;
		_playerX += _speed;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_knightDirection = LEFT_RUN;
		_playerX -= _speed;
	}
	// (speed reset) for 벽 충돌
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		_speed = KNIGHTSPEED;
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		_speed = KNIGHTSPEED;
	}

	// jump 함수
	knightJump(); // Key: W

	 // attack 함수
	knightAttack(); // Key : F

	// Skill_1 함수
	knightSkill_1(); // key : Q
	// Skill_2 함수
	knightSkill_2(); // key : E

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
					_skill_2_Right.x = _playerX - 100; // skill_2_Right 'x' position
					_skill_2_Right.y = _playerY; // skill_2_Right 'y' position
					_skill_2_Left.x = _playerX - 100; // skill_2_Right 'x' position
					_skill_2_Left.y = _playerY; // skill_2_Right 'y' position

					_index = 0;
					_countSkill2 = 0;
					_knightDirection = RIGHT_STAND;
					_isSkill2 = false;
				}
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
			if (_index > 18) _index = 0;
		}
		else if (_knightDirection == LEFT_ATTACK)
		{
			_knight.img = _attack;
			_knight.img->setFrameY(1);
			_knight.img->setFrameX(_index);
			_index--;
			if (_index < 0) _index = 18;
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
	PlayerCollision();
	_knight.rc = RectMakeCenter(_playerX, _playerY, _knight.img->getFrameWidth(), _knight.img->getFrameHeight());
	pCol->UpdatePosition(GetCenterPos(_knight.rc).x, GetCenterPos(_knight.rc).y);

	_skill->update();
}

void player::render()
{
	_knight.img->frameRender(getMemDC(), _knight.rc.left, _knight.rc.top);
	_skill->render();

	if (_isSkill2 == true)
	{
		_skill_2_Right.img->frameRender(getMemDC(), _skill_2_Right.rc.left + 30, _skill_2_Right.rc.top - 30);
		_skill_2_Left.img->frameRender(getMemDC(), _skill_2_Left.rc.left + 30, _skill_2_Left.rc.top - 30);
	}
}

void player::knightJump()
{
	// stand,move 방향에 따른 jump 방향/jump 키
	if (_knightDirection == RIGHT_STAND || _knightDirection == RIGHT_RUN)
	{
		if (KEYMANAGER->isOnceKeyDown('W'))
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
		if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_index = 8;
			_gravity = 0.1f;
			_jumpPower = 5.0f;
			_knightDirection = LEFT_JUMP;
			_isJump = true;
		}
	}

	_playerY -= _jumpPower;
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
		if (KEYMANAGER->isStayKeyDown('F'))
		{
			_index = 0;
			_isAttack = true;
			_skill->makeSlash(_playerX, _playerY, 40, false);
		}
	}
	if (_knightDirection == LEFT_STAND || _knightDirection == LEFT_RUN)
	{
		if (KEYMANAGER->isStayKeyDown('F'))
		{
			_index = 18;
			_isAttack = true;
			_skill->makeSlash(_playerX, _playerY, 40, true);
		}
	}

	// 공격을 멈췄을때
	if (_knightDirection == RIGHT_ATTACK)
	{
		if (KEYMANAGER->isOnceKeyUp('F'))
		{
			_index = 0;
			_isAttack = false;
		}
	}
	if (_knightDirection == LEFT_ATTACK)
	{
		if (KEYMANAGER->isOnceKeyUp('F'))
		{
			_index = 18;
			_isAttack = false;
		}
	}
	

	// attack
	if (_isAttack == true)
	{
		if (_knightDirection == RIGHT_STAND)
		{
			_knightDirection = RIGHT_ATTACK;
			_attackRange.rc = RectMakeCenter(_playerX + 30, _playerY, 80, 50);
		}
		if (_knightDirection == LEFT_STAND)
		{
			_knightDirection = LEFT_ATTACK;
			_attackRange.rc = RectMakeCenter(_playerX - 30, _playerY, 80, 50);
		}
		// move 도중 attack 했을때
		if (_knightDirection == RIGHT_RUN)
		{
			_index = 0;
			_knightDirection = RIGHT_ATTACK;
		}
		if (_knightDirection == LEFT_RUN)
		{
			_index = 18;
			_knightDirection = LEFT_ATTACK;
		}
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
			BULLET->Shot("bulletSwordRight", _playerX, _playerY, 0, 0, 10);
			BULLET->Shot("bulletSwordRight", _playerX, _playerY - 15, 0, 0, 10);
		}
	}
	if (_knightDirection == LEFT_STAND || _knightDirection == LEFT_RUN || _knightDirection == LEFT_JUMP)
	{
		if (KEYMANAGER->isOnceKeyDown('Q'))
		{
			_knightDirection = LEFT_SKILL1;
			BULLET->Shot("bulletSwordLeft", _playerX, _playerY, PI, 0, 10);
			BULLET->Shot("bulletSwordLeft", _playerX, _playerY - 15, PI, 0, 10);
		}
	}
}

void player::knightSkill_2()
{
	if (_isAvailable2 == true)
	{
		if (KEYMANAGER->isOnceKeyDown('E'))
		{
			_skill_2_Right.x = _playerX - 100; // skill_2_Right 'x' position
			_skill_2_Right.y = _playerY; // skill_2_Right 'y' position
			_skill_2_Left.x = _playerX - 100; // skill_2_Right 'x' position
			_skill_2_Left.y = _playerY; // skill_2_Right 'y' position

			_knightDirection = KNIGHT_SPIN;
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

void player::PlayerCollision()
{
	// 바닥충돌
	if (pCol->RayCastingDownY(IMAGEMANAGER->findImage("충돌맵")->getMemDC(), 255, 0, 0))
	{
		if (_jumpPower <= 0)
		{
			pCol->setPosDownY(_playerY);
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
	if (pCol->RayCastingUpY(IMAGEMANAGER->findImage("충돌맵")->getMemDC(), 255, 0, 0))
	{
		if (_jumpPower > 0)
		{
			pCol->setPosUpY(_playerY);

			_jumpPower = 0;
		}
	}

	// 벽 충돌
	if (pCol->RayCastingX(IMAGEMANAGER->findImage("충돌맵")->getMemDC(), 0, 0, 255, 0))
	{
		if (_knightDirection == RIGHT_RUN || _knightDirection == RIGHT_JUMP)
		{
			_speed = 0;
			_playerX -= 4;
		}
		if (_knightDirection == LEFT_RUN || _knightDirection == LEFT_JUMP)
		{
			_speed = 0;
			_playerX += 4;
		}
	}
}