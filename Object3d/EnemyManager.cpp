#include "EnemyManager.h"

void EnemyManager::Initialize(Player* player, Model* enemyModel)
{
	this->player = player;
	this->enemyModel = enemyModel;
	playerOldPos = player->GetPlayerPos();
}

void EnemyManager::Update()
{
	enemies.remove_if([](std::unique_ptr<Enemy>& stage) {return stage->IsDead(); });

	//前回地面を生成した時のプレイヤーの位置から現在のプレイヤーの位置を引いて計算したY軸の値（絶対値での計算）が一定距離内になったら生成
	float num1 = fabs(playerOldPos.y);
	float num2 = fabs(player->GetPlayerPos().y);
	float num3 = num1 - num2;
	num3 = fabs(num3);
	if (num3 > 300/*&& stageNum <10*/)
	{
		stageNum++;
		int type = rand() % 3 + 3;
		float height = player->GetPlayerPos().y - 200 + 70;
		height -= 100;
		XMFLOAT3 enemypos = { 0,0,0 };
		XMFLOAT3 enemypos2 = { 0,0,0 };
		switch (type) {
		case 0:
			enemypos = { -50.0f,height ,-50 };
			break;
		case 1:
			enemypos = { 40,height ,-50 };
			break;
		case 2:
			enemypos = { 120,height ,-50 };
			break;
		case 3:
			enemypos = { -50,height - 20 ,-50 };
			enemypos2 = { 40,height - 20 ,-50 };
			break;
		case 4:
			enemypos = { 40,height - 20,-50 };
			enemypos2 = { 120,height - 20,-50 };
			break;
		case 5:
			enemypos = { -50,height - 20,-50 };
			enemypos2 = { 120,height - 20,-50 };
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
		std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
		newEnemy->Initialize(enemyModel, enemypos, { 0,0,0 }, { 10,10,50 });
		enemies.push_back(std::move(newEnemy));
		//if (type == 3 || type == 4 || type == 5) {
		//	std::unique_ptr<Enemy> newEnemy2 = std::make_unique<Enemy>();
		//	newEnemy2->Initialize(enemyModel, enemypos2, { 0,0,0 }, { 10,10,50 });
		//	enemies.push_back(std::move(newEnemy2));
		//}

		playerOldPos = player->GetPlayerPos();
	}


	//ステージがプレイヤーから指定した値分上にいたらデッドフラグを立てる
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		num1 = fabs(enemy->GetEnemyObj()->GetPosition().y);
		num2 = fabs(player->GetPlayerPos().y);
		num3 = num1 - num2;
		num3 = fabs(num3);
		if (num3 > 400) {
			enemy->SetDead();
		}
	}
	//ステージの更新
	for (std::unique_ptr<Enemy>& stage : enemies) {
		stage->Update();
	}
}

void EnemyManager::Draw(DirectXCommon* dxCommon)
{
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->Draw(dxCommon);
	}
}
