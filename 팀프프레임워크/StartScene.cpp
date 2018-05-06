#include "stdafx.h"
#include "StartScene.h"


StartScene::StartScene()
{
	IMAGEMANAGER->addFrameImage("시작화면", PathFile("image", "시작화면").c_str(), 800, 600, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("검은화면", PathFile("image", "검은화면").c_str(), 800, 600, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("버튼", PathFile("image", "버튼").c_str(), 250, 121, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("점수판", PathFile("image", "점수판").c_str(), 400, 500, 1, 1, true, RGB(255, 0, 255));
}


StartScene::~StartScene()
{
}

HRESULT StartScene::init()
{
	//===============카메라 셋팅===============//
	CAM->CamInit(DYNAMIC_CAMERA, 0, 0, 300, 150, 4);
	//========================================//

	start = new button;
	start->Init(IMAGEMANAGER->findImage("버튼"), "START", WINSIZEX / 2+200, WINSIZEY / 2+50,"휴먼둥근헤드라인");

	edit = new button;
	edit->Init(IMAGEMANAGER->findImage("버튼"), "EDIT", WINSIZEX / 2 + 200, WINSIZEY / 2 + 150, "휴먼둥근헤드라인");

	score = new button;
	score->Init(IMAGEMANAGER->findImage("버튼"), "SCORE", WINSIZEX / 2 + 200, WINSIZEY / 2 + 250, "휴먼둥근헤드라인");

	fadeout = IMAGEMANAGER->findImage("검은화면");

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
			SCENEMANAGER->changeScene("게임씬");
			alpha = 0;
		}
	}

	if (edit->IsClick())
	{
		alpha += 4;
		if (alpha>254)
		{
			SCENEMANAGER->changeScene("수정씬");
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
	IMAGEMANAGER->findImage("시작화면")->render(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, CAM->getCamRc().left, CAM->getCamRc().top, WINSIZEX, WINSIZEY);
	start->Render();
	edit->Render();
	score->Render();
	fadeout->alphaRender(getMemDC(), 0, 0, alpha);
	if (score->IsClick())
	{
		IMAGEMANAGER->findImage("점수판")->render(getMemDC(), CAM->getCamRc().left+200, CAM->getCamRc().top + 50, CAM->getCamRc().left, CAM->getCamRc().top, 400, 500);
	}
}
