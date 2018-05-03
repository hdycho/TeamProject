#include "stdafx.h"
#include "StartScene.h"


StartScene::StartScene()
{
	IMAGEMANAGER->addFrameImage("����ȭ��", PathFile("image", "����ȭ��").c_str(), 800, 600, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����ȭ��", PathFile("image", "����ȭ��").c_str(), 800, 600, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ư", PathFile("image", "��ư").c_str(), 250, 121, 1, 2, true, RGB(255, 0, 255));
}


StartScene::~StartScene()
{
}

HRESULT StartScene::init()
{
	//===============ī�޶� ����===============//
	CAM->CamInit(DYNAMIC_CAMERA, 0, 0, 300, 150, 4);
	//========================================//

	start = new button;
	start->Init(IMAGEMANAGER->findImage("��ư"), "����", WINSIZEX / 2+150, WINSIZEY / 2+100);

	edit = new button;
	edit->Init(IMAGEMANAGER->findImage("��ư"), "����", WINSIZEX / 2 + 150, WINSIZEY / 2 + 200);

	fadeout = IMAGEMANAGER->findImage("����ȭ��");

	alpha = 0;
	return S_OK;
}

void StartScene::release()
{
}

void StartScene::update()
{
	start->Update(VK_LBUTTON,true);
	edit->Update(VK_LBUTTON,true);

	if (start->IsClick())
	{
		alpha+=4;
		if (alpha>254)
		{
			SCENEMANAGER->changeScene("���Ӿ�");
			alpha = 0;
		}
	}

	if (edit->IsClick())
	{
		alpha += 4;
		if (alpha>254)
		{
			SCENEMANAGER->changeScene("������");
			alpha = 0;
		}
	}

}

void StartScene::render()
{
	IMAGEMANAGER->findImage("����ȭ��")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
	start->Render();
	edit->Render();
	fadeout->alphaRender(getMemDC(),0,0, alpha);
}
