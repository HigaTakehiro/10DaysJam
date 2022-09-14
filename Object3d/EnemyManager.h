#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "DirectXCommon.h"
#include "Player.h"
#include "Enemy.h"
#include "FBXObject3d.h"

class EnemyManager
{
public:
	void Initialize(Player* player, Model* enemyModel,FBXModel* fbxEnemyModel);
	void Update();
	void Draw(DirectXCommon* dxCommon);

	std::list<std::unique_ptr<Enemy>>& GetEnemies() { return enemies; }

private:
	Model* enemyModel = nullptr;
	Model* energyModel = nullptr;
	FBXModel* fbxEnemyModel = nullptr;
	Player* player = nullptr;
	XMFLOAT3 playerOldPos;
	std::list<std::unique_ptr<Enemy>>enemies;

	int intervalTime = 0;
	int stageNum = 0;
};