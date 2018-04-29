#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

//초기화 해주는 곳
HRESULT playGround::init()
{
	gameNode::init(true);
	gameScene = new GameScene;
	gameScene->init();
	SCENEMANAGER->addScene("게임씬", gameScene);
	SCENEMANAGER->changeScene("게임씬");

	return S_OK;
}

//메모리 해제 (동적할당 해제등)
void playGround::release()
{
	gameNode::release();

}

//연산
void playGround::update()
{
	gameNode::update();
	EFFECTMANAGER->update();
	SCENEMANAGER->update();
	BULLET->BulletUpdate();
}

//그려주는
void playGround::render()
{
	SCENEMANAGER->render();
	BULLET->BulletRender(getMemDC());
	EFFECTMANAGER->render();
	getBackBuffer()->render(CAM->getCamBuffer()->getMemDC(), 0, 0);
	CAM->CamRender(getHDC());
}
