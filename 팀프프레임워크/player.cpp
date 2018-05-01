#include "stdafx.h"
#include "player.h"


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

	_knight.img = _stand;
	_knightDirection = RIGHT_STAND;

	_knight.rc = RectMakeCenter(_playerX, _playerY, _knight.img->getFrameWidth(), _knight.img->getFrameX());

	_count = _index = 0;
	_countAttack = 0;

	// for Jump
	_jumpPower = 0.0f;
	_gravity = 0.1f;
	_isJump = false;

	// for Attack
	_isAttack = false;
	pCol = new PixelCol;

	pCol->init(70, 20);
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
		_playerX += KNIGHTSPEED;
	}
	if (KEYMANAGER->isStayKeyDown('A'))
	{
		_knightDirection = LEFT_RUN;
		_playerX -= KNIGHTSPEED;
	}

	// jump 함수
	knightJump(); // Key: W

				  // attack 함수
	knightAttack(); // Key : F

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

		_countAttack = 0;
	}
	PlayerCollision();
	_knight.rc = RectMakeCenter(_playerX, _playerY, _knight.img->getFrameWidth(), _knight.img->getFrameHeight());
	pCol->UpdatePosition(GetCenterPos(_knight.rc).x, GetCenterPos(_knight.rc).y);
}

void player::render()
{
	_knight.img->frameRender(getMemDC(), _knight.rc.left, _knight.rc.top);
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
		}
	}
	if (_knightDirection == LEFT_STAND || _knightDirection == LEFT_RUN)
	{
		if (KEYMANAGER->isStayKeyDown('F'))
		{
			_index = 18;
			_isAttack = true;
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
		}
		if (_knightDirection == LEFT_STAND)
		{
			_knightDirection = LEFT_ATTACK;
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
		KNIGHTSPEED 0;
	}
}