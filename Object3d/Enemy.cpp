#include "Enemy.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <wrl.h>

using namespace std;

void Enemy::Initialize(const std::string& modelName, Vector3 pos, Vector3 rot, Vector3 scale) {
	enemyModel = Model::CreateModel(modelName);
	enemy = Object3d::Create(enemyModel);
	enemy->SetPosition(pos);
	enemy->SetRotation(rot);
	enemy->SetScale(scale);
}

void Enemy::Update() {
	if (enemy != nullptr) {
		enemy->Update();
	}
}

void Enemy::Draw() {
	enemy->Draw();
}

void Enemy::OnCollision() {
	isDead = true;
}