#include "Stage.h"
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <wrl.h>

using namespace std;

void Stage::Initialize(Model* model, Vector3 pos, Vector3 rot, Vector3 scale) {
	stageModel = model;
	stage = Object3d::Create(stageModel);
	stage->SetPosition(pos);
	stage->SetRotation(rot);
	stage->SetScale(scale);

	//testEnemyModel = FbxLoader::GetInstance()->LoadModelFromFile(modelName);
	//testEnemy = new FBXObject3d;
	//testEnemy->Initialize();
	//testEnemy->SetModel(testEnemyModel);
	//testEnemy->SetPosition(pos);
	//testEnemy->SetRotation(rot);
	//testEnemy->SetScale(scale);
	//testEnemy->PlayAnimation();
}

void Stage::Update() {
	if (stage != nullptr) {
		stage->Update();
	}
	time++;
	if (time > 100)	{
		isDead = true;
	}
}

void Stage::Draw() {
	stage->Draw();
}

void Stage::OnCollision() {
	isDead = true;
}