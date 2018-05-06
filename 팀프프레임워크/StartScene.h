#pragma once
#include "gameNode.h"
#include "button.h"

struct ScoreData
{
	int min;
	int sec;
	int time;
};
class StartScene :public gameNode
{
private:
	RECT rc;
	button*start;
	button*edit;
	button*score;

	image*fadeout;

	int alpha;

	vector<ScoreData>		scoreVec;
	bool isonce;

public:
	StartScene();
	~StartScene();

	virtual HRESULT init();
	virtual void release();
	virtual void update();
	virtual void render();

	void ScoreUpdate();	//	스코어 실시간비교
	void ScoreShow();

	void LoadScore();
	void LoadAllScore();
	void SaveScore();

};

