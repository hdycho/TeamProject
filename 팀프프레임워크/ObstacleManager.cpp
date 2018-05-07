#include "stdafx.h"
#include "ObstacleManager.h"


ObstacleManager::ObstacleManager()
{
}


ObstacleManager::~ObstacleManager()
{
}

HRESULT ObstacleManager::init()
{
	LoadObstacle();
	return S_OK;
}

void ObstacleManager::render()
{
	for (int i = 0; i < obsVec.size(); i++)
	{
		if (obsVec[i]->GetShowState())
			obsVec[i]->render();
	}
}

void ObstacleManager::update()
{
	for (int i = 0; i < obsVec.size(); i++)
	{
		RECT temp;
		if (!IntersectRect(&temp, &CAM->getCamRc(), &obsVec[i]->getRect()))continue;
		if (obsVec[i]->GetShowState())
		{
			obsVec[i]->update();
		}
	}
}

void ObstacleManager::release()
{
}

void ObstacleManager::LoadObstacle()
{
	FILE*fp = nullptr;
	fopen_s(&fp, "오브젝트데이터.txt", "r");

	if (!fp)return;

	char name[256];
	int x, y;

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof(name));
		if (string(name).find("PosY", 0) != string::npos)
			break;
		//문자열의 0번째인덱스부터 PosY까지 탐색을하는데 찾으면 브레이크
	}

	while (true)
	{
		fscanf_s(fp, "%s", name, sizeof(name));
		if (name[0] == '@')break;
		fscanf_s(fp, "%d%d", &x, &y);

		if (strcmp(name, "나무") == 0)
		{
			Obstacle* wood = new Wood;
			wood->init(x, y, "나무장애물");
			wood->GetShowState() = true;
			obsVec.push_back(wood);
		}
		else if (strcmp(name, "쇠") == 0)
		{
			Obstacle* iron = new Iron;
			iron->init(x, y, "쇠장애물");
			iron->GetShowState() = true;
			obsVec.push_back(iron);
		}
		else if (strcmp(name, "폭탄") == 0)
		{
			Obstacle* bomb = new Bomb;
			bomb->init(x, y, "폭탄장애물");
			bomb->GetShowState() = true;
			obsVec.push_back(bomb);
		}
	}
	fclose(fp);
}
