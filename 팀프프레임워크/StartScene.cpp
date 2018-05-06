#include "stdafx.h"
#include "StartScene.h"

StartScene::StartScene()
{
	IMAGEMANAGER->addFrameImage("시작화면", PathFile("image", "시작화면").c_str(), 800, 600, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("검은화면", PathFile("image", "검은화면").c_str(), 800, 600, 1, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("버튼", PathFile("image", "버튼").c_str(), 250, 121, 1, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("점수판", PathFile("image", "점수판").c_str(), 400, 500, 1, 1, true, RGB(255, 0, 255));
	isonce = false;
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
	start->Init(IMAGEMANAGER->findImage("버튼"), "START", WINSIZEX / 2 + 200, WINSIZEY / 2 + 50, "휴먼둥근헤드라인");

	edit = new button;
	edit->Init(IMAGEMANAGER->findImage("버튼"), "EDIT", WINSIZEX / 2 + 200, WINSIZEY / 2 + 150, "휴먼둥근헤드라인");

	score = new button;
	score->Init(IMAGEMANAGER->findImage("버튼"), "SCORE", WINSIZEX / 2 + 200, WINSIZEY / 2 + 250, "휴먼둥근헤드라인");

	fadeout = IMAGEMANAGER->findImage("검은화면");
	alpha = 0;


	LoadAllScore();	//먼저 전체데이터 로드하고
	LoadScore(); // 그뒤에 새로운데이터 추가
				 //그리고 임시데이터 지워줘야한다
	remove("임시저장소.txt");
	
	return S_OK;
}

void StartScene::release()
{
	SaveScore();
	scoreVec.clear();
	isonce = false;
}

void StartScene::update()
{
	ScoreUpdate();
	start->Update(VK_LBUTTON, true);
	edit->Update(VK_LBUTTON, true);
	score->Update(VK_LBUTTON, true);
	if (start->IsClick())
	{
		alpha += 4;
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

	else if (!score->IsClick() && scoreShow)
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
		IMAGEMANAGER->findImage("점수판")->render(getMemDC(), CAM->getCamRc().left + 200, CAM->getCamRc().top + 50, CAM->getCamRc().left, CAM->getCamRc().top, 400, 500);
		ScoreShow();
	}
}

void StartScene::ScoreUpdate()
{
	for (int i = 0; i < scoreVec.size(); i++)
	{
		scoreVec[i].time = scoreVec[i].min * 60 + scoreVec[i].sec;
	}


	for (int i = 0; i < scoreVec.size(); i++)
	{
		for (int j = 0; j < (scoreVec.size() - (i + 1)); j++)
		{
			if (scoreVec[j].time > scoreVec[j + 1].time)
			{
				ScoreData temp = scoreVec[j];
				scoreVec[j] = scoreVec[j + 1];
				scoreVec[j + 1] = temp;
			}
		}
	}
}

void StartScene::ScoreShow()
{
	char temp[256];

	HFONT font, oldFont;
	font = CreateFont(25, 0, 0, 0, 0, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, "휴먼둥근헤드라인");
	oldFont = (HFONT)SelectObject(getMemDC(), font);
	SetTextColor(getMemDC(), RGB(255, 255, 255));

	for (int i = 0; i < scoreVec.size(); i++)
	{
		if (scoreVec[i].min < 10)
		{
			if (scoreVec[i].sec < 10)
			{
				sprintf(temp, "[%dst].0%d:0%d", i + 1, scoreVec[i].min, scoreVec[i].sec);

			}
			else
			{
				sprintf(temp, "[%dst].0%d:%d", i + 1, scoreVec[i].min, scoreVec[i].sec);
			}
		}
		else
		{
			if (scoreVec[i].sec < 10)
			{
				sprintf(temp, "[%dst].%d:0%d", i + 1, scoreVec[i].min, scoreVec[i].sec);
			}
			else
			{
				sprintf(temp, "[%dst].%d:%d", i + 1, scoreVec[i].min, scoreVec[i].sec);
			}
		}
		TextOut(getMemDC(), CAM->getCamRc().left + 320, CAM->getCamRc().top + 200 + i * 50, temp, strlen(temp));
	}
}

void StartScene::LoadScore()
{
	FILE*fp = nullptr;
	fopen_s(&fp, "임시저장소.txt", "r");

	if (!fp)return;

	char name[256];

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof(name));
		if (string(name).find("Time", 0) != string::npos)
			break;
	}

	while (true)
	{
		ScoreData sd;
		fscanf_s(fp, "%s", name, sizeof(name));
		if (name[0] == '@')break;

		fscanf_s(fp, "%d%d", &sd.min, &sd.sec);

		if (strcmp(name, "CLEAR") == 0)
		{
			scoreVec.push_back(sd);
		}
	}
	fclose(fp);
}

void StartScene::LoadAllScore()
{
	FILE*fp = nullptr;
	fopen_s(&fp, "전체저장소.txt", "r");
	if (!fp)return;

	char name[256];

	while (true)
	{
		ScoreData sd;
		fscanf_s(fp, "%s", name, sizeof(name));
		if (name[0] == '@')break;
		fscanf_s(fp, "%d%d", &sd.min, &sd.sec);
		scoreVec.push_back(sd);
	}
	fclose(fp);
}


void StartScene::SaveScore()
{
	FILE*fp = nullptr;
	fopen_s(&fp, "전체저장소.txt", "w+t");

	string temp;
	string name = "name";
	char end = '@';
	for (int i = 0; i < scoreVec.size(); i++)
	{
		temp = name + '\t' + to_string(scoreVec[i].min) + '\t' + to_string(scoreVec[i].sec) + '\n';
		fwrite(temp.c_str(), temp.size(), 1, fp);
	}
	fwrite(&end, sizeof(end), 1, fp);
	fclose(fp);
}
