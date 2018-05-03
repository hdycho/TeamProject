#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
	IMAGEMANAGER->addFrameImage("충돌맵", PathFile("image", "충돌맵").c_str(), 20000, 1000, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("스테이지", PathFile("image", "스테이지").c_str(), 20000, 1000, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("보스방", PathFile("image", "보스방").c_str(), 1600, 800, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("보스방충돌맵", PathFile("image", "보스방충돌맵").c_str(), 1600, 800, 1, 1, false, NULL);
}


playGround::~playGround()
{

}

//초기화 해주는 곳임
HRESULT playGround::init()
{
	gameNode::init(true);
	gameScene = new GameScene;
	gameScene->init();

	startScene = new StartScene;
	startScene->init();

	editScene = new EditScene;
	editScene->init();

	SCENEMANAGER->addScene("게임씬", gameScene);
	SCENEMANAGER->addScene("시작씬", startScene);
	SCENEMANAGER->addScene("수정씬", editScene);

	SCENEMANAGER->changeScene("시작씬");

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
