#include "StageManager.h"

void StageManager::Initialize(Player* player, Model* stageModel)
{
	this->player = player;
	this->stageModel = stageModel;
	playerOldPos = player->GetPlayerPos();
}

void StageManager::Update()
{
	stages.remove_if([](std::unique_ptr<Stage>& stage) {return stage->IsDead(); });

	//前回地面を生成した時のプレイヤーの位置から現在のプレイヤーの位置を引いて計算したY軸の値（絶対値での計算）が一定距離内になったら生成
	float num1 = fabs(playerOldPos.y);
	float num2 = fabs(player->GetPlayerPos().y);
	float num3 = num1 - num2;
	num3 = fabs(num3);
	if (num3 > 300/*&& stageNum <10*/)
	{
		stageNum++;
		int type = rand() % 3 + 3;
		float height = player->GetPlayerPos().y - 200;
		height -= 100;
		XMFLOAT3 staegepos = { 0,0,0 };
		XMFLOAT3 staegepos2 = { 0,0,0 };
		switch (type) {
		case 0:
			staegepos = { -50.0f,height ,-50 };
			break;
		case 1:
			staegepos = { 40,height ,-50 };
			break;
		case 2:
			staegepos = { 120,height ,-50 };
			break;
		case 3:
			staegepos = { -50,height - 20 ,-50 };
			staegepos2 = { 40,height - 20 ,-50 };
			break;
		case 4:
			staegepos = { 40,height - 20,-50 };
			staegepos2 = { 120,height - 20,-50 };
			break;
		case 5:
			staegepos = { -50,height - 20,-50 };
			staegepos2 = { 120,height - 20,-50 };
			break;
		case 6:
			//stageObj[stageClip]->SetPosition({ -50,height ,-50 });
			break;
		case 7:
			//何もでてこないタイプ
			//stageObj[stageClip]->SetPosition({ -50,height ,-50 });
			break;
		}
		//地面をゲームシーンに追加
		std::unique_ptr<Stage> newStage = std::make_unique<Stage>();
		newStage->Initialize(stageModel, staegepos, { 0,0,0 }, { 90,50,50 });
		stages.push_back(std::move(newStage));
		if (type == 3 || type == 4 || type == 5) {
			std::unique_ptr<Stage> newStage2 = std::make_unique<Stage>();
			newStage2->Initialize(stageModel, staegepos2, { 0,0,0 }, { 90,50,50 });
			stages.push_back(std::move(newStage2));
		}

		playerOldPos = player->GetPlayerPos();
	}


	//ステージがプレイヤーから指定した値分上にいたらデッドフラグを立てる
	for (std::unique_ptr<Stage>& stage : stages) {
		num1 = fabs(stage->GetStagePos().y);
		num2 = fabs(player->GetPlayerPos().y);
		num3 = num1 - num2;
		num3 = fabs(num3);
		if (num3 > 400) {
			stage->SetDead();
		}
	}
	//ステージの更新
	for (std::unique_ptr<Stage>& stage : stages) {
		stage->Update();
	}
}

void StageManager::Draw()
{
	for (std::unique_ptr<Stage>& stage : stages) {
		stage->Draw();
	}
}
