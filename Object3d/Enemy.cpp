#include "Enemy.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <wrl.h>

using namespace std;

void Enemy::Initialize(Model* model, FBXModel* fbxModel, Vector3 pos, Vector3 rot, Vector3 scale, int enemyType, Model* energyModel) {
	enemyModel = model;
	enemy = Object3d::Create(enemyModel);
	enemy->SetPosition(pos);
	enemy->SetRotation(rot);
	enemy->SetScale(scale);

	fbxEnemyModel = fbxModel;
	fbxEnemy = new FBXObject3d;
	fbxEnemy->Initialize();
	fbxEnemy->SetModel(fbxEnemyModel);
	fbxEnemy->SetPosition(pos);
	fbxEnemy->SetRotation(rot);
	fbxEnemy->SetScale(scale);
	fbxEnemy->PlayAnimation();

	this->enemyType = enemyType;
	if (enemyType == 4) {
		this->energyModel = energyModel;
		energyObj = Object3d::Create(energyModel);
		pos.x += -5;
		pos.z += -10;
		energyObj->SetPosition(pos);
		energyObj->SetScale({ 5,5,5 });
	}

	direction = rand() % 2;
}

void Enemy::Update() {
	if (fbxEnemy != nullptr) {
		XMFLOAT3 pos = fbxEnemy->GetPosition();
		if (direction == 0) {
			fbxEnemy->SetRotation({ 0,-90,0 });
			pos.x -= speed;
			fbxEnemy->SetPosition(pos);
			if (fbxEnemy->GetPosition().x < -92) {
				pos.x = -92;
				fbxEnemy->SetPosition(pos);
				direction = 1;
			}
		}
		else if (direction == 1) {
			fbxEnemy->SetRotation({ 0,90,0 });
			pos.x += speed;
			fbxEnemy->SetPosition(pos);
			if (fbxEnemy->GetPosition().x > 172) {
				pos.x = 172;
				fbxEnemy->SetPosition(pos);
				direction = 0;
			}
		}

		//enemy->Update();
		fbxEnemy->Update();
		if (enemyType == 4) {
			XMFLOAT3 energypos = fbxEnemy->GetPosition();
			energypos.x += -5;
			energypos.z += -10;
			energyObj->SetPosition(energypos);
			energyObj->Update();
		}
	}
}

void Enemy::Draw(DirectXCommon* dxCommon) {
	//enemy->Draw();
	fbxEnemy->Draw(dxCommon->GetCmdList());
	if (enemyType ==4) {
		energyObj->Draw();
	}
}

void Enemy::OnCollision() {
	isDead = true;
}