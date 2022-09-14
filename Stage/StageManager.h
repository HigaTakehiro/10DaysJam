#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include "Player.h"
#include "Stage.h"

class StageManager
{
public:
	void Initialize(Player* player, Model* stageModel);
	void Update();
	void Draw();

	std::list<std::unique_ptr<Stage>>& GetStages() { return stages; }

	void ListClear(){ stages.clear(); }

private:
	Model* stageModel = nullptr;
	Player* player = nullptr;
	XMFLOAT3 playerOldPos;
	std::list<std::unique_ptr<Stage>>stages;

	int intervalTime = 0;
	int stageNum = 0;
};