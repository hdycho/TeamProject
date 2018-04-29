#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

//�ʱ�ȭ ���ִ� ��
HRESULT playGround::init()
{
	gameNode::init(true);
	gameScene = new GameScene;
	gameScene->init();
	SCENEMANAGER->addScene("���Ӿ�", gameScene);
	SCENEMANAGER->changeScene("���Ӿ�");

	return S_OK;
}

//�޸� ���� (�����Ҵ� ������)
void playGround::release()
{
	gameNode::release();

}

//����
void playGround::update()
{
	gameNode::update();
	EFFECTMANAGER->update();
	SCENEMANAGER->update();
	BULLET->BulletUpdate();
}

//�׷��ִ�
void playGround::render()
{
	SCENEMANAGER->render();
	BULLET->BulletRender(getMemDC());
	EFFECTMANAGER->render();
	getBackBuffer()->render(CAM->getCamBuffer()->getMemDC(), 0, 0);
	CAM->CamRender(getHDC());
}
