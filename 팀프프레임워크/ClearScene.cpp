#include "stdafx.h"
#include "ClearScene.h"
#include "StartScene.h"

ClearScene::ClearScene()
{
	IMAGEMANAGER->addFrameImage("클리어화면", PathFile("image", "클리어화면").c_str(), 800, 600, 1, 1, true, RGB(255, 0, 255));
}


ClearScene::~ClearScene()
{
}

HRESULT ClearScene::init()
{
	//===============카메라 셋팅===============//
	//CAM->CamInit(DYNAMIC_CAMERA, 0, 0, 300, 150, 4);
	//========================================//
	CAM->CamInit(DYNAMIC_CAMERA, WINSIZEX / 2, WINSIZEY / 2 + 400, 300, 150, 4);
	alpha = 255;
	fadeout = IMAGEMANAGER->findImage("검은화면");

	Loby = new button;
	Loby->Init(IMAGEMANAGER->findImage("버튼"), "LOBY", WINSIZEX / 2 - 240, WINSIZEY / 2 + 160, "휴먼둥근헤드라인");

	Quit = new button;
	Quit->Init(IMAGEMANAGER->findImage("버튼"), "QUIT", WINSIZEX / 2 - 240, WINSIZEY / 2 + 240, "휴먼둥근헤드라인");
	sceneChange = false;
	metaData = 2;
	LoadTime();
	return S_OK;
}

void ClearScene::release()
{
}

void ClearScene::update()
{
	RECT rc = RectMake(0, 0, 70, 56);
	CAM->CamUpdate(rc, 0, 1600, 0, 1200);
	if (!sceneChange)
	{
		if (alpha > 1)
			alpha -= 3;
		else
			alpha = 0;
	}
	Loby->Update(VK_LBUTTON, true);
	Quit->Update(VK_LBUTTON, true);
	if (Loby->IsClick())
	{
		sceneChange = true;
		metaData = 0;
	}

	if (Quit->IsClick())
	{
		sceneChange = true;
		metaData = 1;
	}

	if (sceneChange)
	{
		alpha += 3;

		if (alpha > 254)
		{
			if (metaData == 0)
			{
				SCENEMANAGER->changeScene("시작씬");
				alpha = 0;
			}
			else if (metaData == 1)
			{
				PostQuitMessage(0);
			}
		}
	}
}

void ClearScene::render()
{
	IMAGEMANAGER->render("클리어화면", getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top);
	Quit->Render();
	Loby->Render();

	HFONT font, oldFont;
	SetTextColor(getMemDC(), RGB(255, 0, 0));
	font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "휴먼둥근헤드라인");
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	TextOut(getMemDC(), CAM->getCamRc().left + 490, CAM->getCamRc().top + 495, time.c_str(), time.size());
	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	fadeout->alphaRender(getMemDC(), CAM->getCamRc().left, CAM->getCamRc().top, alpha);
}

void ClearScene::LoadTime()
{
	FILE*fp = nullptr;
	fopen_s(&fp, "임시저장소.txt", "r");

	if (!fp)return;

	char temp[256];
	int minute;
	int second;
	while (true)
	{
		fscanf_s(fp, "%s", temp, sizeof(temp));
		if (string(temp).find("Time", 0) != string::npos)//데이터찾으면
			break;
	}

	while (true)
	{
		fscanf_s(fp, "%s", temp, sizeof(temp));
		if (temp[0] == '@')break;

		fscanf_s(fp, "%d%d", &minute, &second);
	}

	if (minute < 10)
	{
		if (second < 10)
		{
			time = '0' + to_string(minute) + ':' + '0' + to_string(second);
		}
		else
		{
			time = '0' + to_string(minute) + ':' + to_string(second);
		}
	}
	else
	{
		if (second < 10)
		{
			time = to_string(minute) + ':' + '0' + to_string(second);
		}
		else
		{
			time = to_string(minute) + ':' + to_string(second);
		}
	}
	fclose(fp);
}

