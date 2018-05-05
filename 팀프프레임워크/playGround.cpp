#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
	IMAGEMANAGER->addFrameImage("�浹��", PathFile("image", "�浹��").c_str(), 20000, 1000, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("��������", PathFile("image", "��������").c_str(), 20000, 1000, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("������", PathFile("image", "������").c_str(), 1600, 800, 1, 1, false, NULL);
	IMAGEMANAGER->addFrameImage("�������浹��", PathFile("image", "�������浹��").c_str(), 1600, 800, 1, 1, false, NULL);
}


playGround::~playGround()
{

}

//�ʱ�ȭ ���ִ� ����
HRESULT playGround::init()
{
	gameNode::init(true);
	gameScene = new GameScene;
	gameScene->init();

	startScene = new StartScene;
	startScene->init();

	editScene = new EditScene;
	editScene->init();

	gameoverScene = new GameOverScene;
	gameoverScene->init();

	clearScene = new ClearScene;
	clearScene->init();

	SCENEMANAGER->addScene("���۾�", startScene);
	SCENEMANAGER->addScene("���Ӿ�", gameScene);
	SCENEMANAGER->addScene("������", editScene);
	SCENEMANAGER->addScene("���ӿ�����", gameoverScene);
	SCENEMANAGER->addScene("Ŭ�����", clearScene);

	SCENEMANAGER->changeScene("���۾�");

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
