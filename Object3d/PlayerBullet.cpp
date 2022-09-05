#include "PlayerBullet.h"

void PlayerBullet::Initialize(Vector3 pos, Vector3 velocity) {
	const Vector3 bulletSize = { 2, 2, 2 };

	bulletModel = Model::CreateModel("Block");
	bullet = Object3d::Create(bulletModel);
	bullet->SetScale(bulletSize);
	bullet->SetRotation(Vector3(0, 0, 0));
	this->pos = pos;
	this->velocity = velocity;
	bullet->SetPosition(this->pos);
}

void PlayerBullet::Update() {
	const int timeOver = 0;

	if (--lifeTimer <= timeOver) {
		isDead = true;
	}
	else {
		pos += velocity;
	}

	if (bullet != nullptr) {
		bullet->SetPosition(pos);
		bullet->Update();
	}
}

void PlayerBullet::Draw() {
	bullet->Draw();
}

void PlayerBullet::OnCollision() {
	isDead = true;
}
