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
}

void Stage::Update() {
	if (stage != nullptr) {
		stage->Update();
	}
	time++;
	if (time > 100)	{
		//isDead = true;
	}
}

void Stage::Draw() {
	stage->Draw();
}

void Stage::OnCollision() {
	isDead = true;
}