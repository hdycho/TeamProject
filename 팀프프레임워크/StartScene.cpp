#include "stdafx.h"
#include "StartScene.h"


StartScene::StartScene()
{
	IMAGEMANAGER->addFrameImage("����ȭ��", PathFile("image", "����ȭ��").c_str(), 800, 600, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("����ȭ��", PathFile("image", "����ȭ��").c_str(), 800, 600, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("��ư", PathFile("image", "��ư").c_str(), 250, 121, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("������", PathFile("image", "������").c_str(), 400, 500, 1, 1, true, RGB(255, 0, 255));
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
	start->Init(IMAGEMANAGER->findImage("��ư"), "START", WINSIZEX / 2+200, WINSIZEY / 2+50,"�޸յձ�������");

	edit = new button;
	edit->Init(IMAGEMANAGER->findImage("��ư"), "EDIT", WINSIZEX / 2 + 200, WINSIZEY / 2 + 150, "�޸յձ�������");

	score = new button;
	score->Init(IMAGEMANAGER->findImage("��ư"), "SCORE", WINSIZEX / 2 + 200, WINSIZEY / 2 + 250, "�޸յձ�������");

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
	score->Update(VK_LBUTTON, true);
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

	static bool scoreShow = false;

	if (score->IsClick())
	{
		scoreShow = true;
		alpha = 100;
	}
	
	else if(!score->IsClick()&&scoreShow)
	{
		scoreShow = false;
		alpha = 0;
	}

}

void StartScene::render()
{
	IMAGEMANAGER->findImage("����ȭ��")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
	start->Render();
	edit->Render();
	score->Render();
	fadeout->alphaRender(getMemDC(), 0, 0, alpha);
	if (score->IsClick())
	{
		IMAGEMANAGER->findImage("������")->render(getMemDC(), CAM->getCamRc().left+200, CAM->getCamRc().top + 50, CAM->getCamRc().left, CAM->getCamRc().top, 400, 500);
	}
}
