#include "Enemy.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <wrl.h>

using namespace std;

void Enemy::Initialize(Model* model, Vector3 pos, Vector3 rot, Vector3 scale) {
	enemyModel = model;
	enemy = Object3d::Create(enemyModel);
	enemy->SetPosition(pos);
	enemy->SetRotation(rot);
	enemy->SetScale(scale);

	//testEnemyModel = FbxLoader::GetInstance()->LoadModelFromFile(modelName);
    //testEnemy = new FBXObject3d;
	//testEnemy->Initialize();
	//testEnemy->SetModel(testEnemyModel);
	//testEnemy->SetPosition(pos);
	//testEnemy->SetRotation(rot);
	//testEnemy->SetScale(scale);
	//testEnemy->PlayAnimation();
}

void Enemy::Update() {
	if (enemy != nullptr) {
		enemy->Update();
	}
}

void Enemy::Draw(DirectXCommon* dxCommon) {
	enemy->Draw();
}

void Enemy::OnCollision() {
	isDead = true;
}