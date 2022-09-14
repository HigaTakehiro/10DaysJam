#include "Player.h"
#include "SafeDelete.h"
#include "Stage.h"

void Player::Initialize(Camera* camera) {
	this->camera = camera;

	Sprite::LoadTexture(1, L"Resources/Aim.png");
	aim = Sprite::Create(1, { 0, 0 });
	aim->SetSize(XMFLOAT2(100.0f, 100.0f));

	playerModel = Model::CreateModel("Player_Jump");
	player = Object3d::Create(playerModel);
	playerScale = { 2, 2, 2 };
	playerLPos = { 50, 950, -50 };
	playerRot = { 0, 180, 0 };
	player->SetScale(playerScale);
	player->SetPosition(playerLPos);
	player->SetRotation(playerRot);
	//player->SetCameraParent(camera);
	aim3dModel = Model::CreateModel("Block");
	aim3d = Object3d::Create(aim3dModel);
	aim3d->SetScale(Vector3(0, 0, 0));
	aim3d->SetPosition(Vector3(0, 0, 50));
	aim3d->SetRotation(Vector3(0, 0, 0));
	//aim3d->SetParent(player);

}

void Player::Finalize() {
	safe_delete(player);
	safe_delete(playerModel);
	safe_delete(aim);
	safe_delete(aim3d);
}

void Player::Update() {
	bullets.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });
	/*if (KeyInput::GetIns()->TriggerKey(DIK_1)) {
		if (fallFlag == false) { fallFlag = true; }
		else { fallFlag = false; }
	}*/
	//if (KeyInput::GetIns()->TriggerKey(DIK_B)) {
	//	static float alpha = 0.1f;
	//	if (alpha + 0.1f <= 1) {
	//		alpha += 0.1f;
	//	}
	//	else {
	//		alpha = 0;
	//	}
	//	aim->SetAlpha(alpha);
	//}

	Move();
	FreeFall();
	JumpUpdate();
	DecelerationBoost();


	AimUpdate();

	if (KeyInput::GetIns()->TriggerKey(DIK_SPACE) && !isShot) {
		//targetAimPos = Vector3(aimPos.x, aimPos.y, 500.0f);
		//targetAimPos.normalize();
		//shotPos = playerWPos;
		//oldShotPos = shotPos;
		//shot->SetPosition(shotPos);
		isShot = true;
	}

	if (isShot) {
		Shot();
	}

	//playerLPos.z = -50.0f;
	//aim3d->SetPosition(Vector3(aimPos.x, aimPos.y, 50));

	aim->SetPosition(XMFLOAT2(aimPos.x - 50.0f, aimPos.y - 50.0f));
	aim3d->Update();
	player->Update();
	for (std::unique_ptr<PlayerBullet>& bullet : bullets) {
		bullet->Update();
	}

	if (boostCapacity < 20) {		
		num = 0.0f;
	}
	if (boostCapacity < 15) {
		num = 3.0f;
	}
	if (boostCapacity < 10) {
		num = 6.0f;
	}
	if (boostCapacity < 5) {
		num = 10.0f;
	}
	if (boostCapacity < 3) {
		num = 15.0f;
	}
}

void Player::SpriteDraw() {
	//aim->Draw();
}

void Player::ObjectDraw() {
	player->Draw();
	aim3d->Draw();

	//if (isShot) {
	//	shot->Draw();
	//}
	for (std::unique_ptr<PlayerBullet>& bullet : bullets) {
		bullet->Draw();
	}
}

void Player::Move() {
	const float moveSpeed = 2.0f;
	const float autoSpeed = 0.2;

	/*if (KeyInput::GetIns()->PushKey(DIK_W)) {
		playerLPos.y += moveSpeed;
	}*/
	/*if (KeyInput::GetIns()->PushKey(DIK_S)) {
		playerLPos.y -= moveSpeed;
	}*/
	//if (KeyInput::GetIns()->PushKey(DIK_A)) {
	//	playerLPos.x -= moveSpeed;
	//}
	//if (KeyInput::GetIns()->PushKey(DIK_D)) {
	//	playerLPos.x += moveSpeed;
	//}

	//•Ç‚ğ’´‚¦‚½‚Æ‚«‚Ì‰Ÿ‚µ–ß‚µˆ—
	if (playerLPos.x < -92) {
		playerLPos.x = -92;
	}
	if (playerLPos.x > 172) {
		playerLPos.x = 172;
	}

	//playerPos.z += autoSpeed;
	//playerWPos = playerLPos * player->GetMatWorld().r->m128_f32[3];

	player->SetPosition(playerLPos);
}

void Player::Shot() {
	//const float bulletSpeed = 1.0f;
	//XMVECTOR velocity = { 0, 0, bulletSpeed };

	//velocity = MatCalc::GetIns()->VecDivided(velocity, player->GetMatWorld());

	//std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
	//newBullet->Initialize(playerWPos, velocity);

	//bullets.push_back(std::move(newBullet));

	//isShot = false;

	//shotPos.z += shotSpeed;
	//shot->SetPosition(shotPos);

	//if (shotPos.z >= playerWPos.z + 100.0f || shotPos.x <= windowOverX_Left || shotPos.x >= windowOverX_Right) {
	//	isShot = false;
	//}
}

void Player::Reset() {
	playerScale = { 2, 2, 2 };
	playerLPos = { 0, 950, -50 };
	playerRot = { 0, 0, 0 };
	fallTime = 0.0f;
	boostCapacity = maxBoostCapacity;
	player->SetPosition(playerLPos);
	bullets.clear();
	num = 0;
}

void Player::AimUpdate() {

	//const float kDistancePlayerTo3DRaticle = 50.0f;
	//XMVECTOR offset = { 0, 0, 1.0f };
	//offset = VecDivided(offset, player->GetMatWorld());
	//offset = XMVector3Normalize(offset) * kDistancePlayerTo3DRaticle;

	//aimPos3d.x = playerWPos.x + offset.m128_f32[0];
	//aimPos3d.y = playerWPos.y + offset.m128_f32[1];
	//aimPos3d.z = playerWPos.z + offset.m128_f32[2];

	/*XMVECTOR raticle2D = { aim3d->GetMatWorld().r[3] };
	XMMATRIX matViewProjectionViewport = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
	raticle2D = Wdivided(raticle2D, matViewProjectionViewport);

	aimPos = { raticle2D.m128_f32[0] - 50.0f, raticle2D.m128_f32[1] - 50.0f };*/
	aimPos = XMFLOAT2(MouseInput::GetIns()->GetMousePoint().x, MouseInput::GetIns()->GetMousePoint().y);

	XMMATRIX matVPV = Camera::GetMatView() * Camera::GetMatProjection() * Camera::GetMatViewPort();
	XMMATRIX matInverseVPV = XMMatrixInverse(nullptr, matVPV);
	XMVECTOR posNear = { (float)aimPos.x, (float)aimPos.y, 0 };
	XMVECTOR posFar = { (float)aimPos.x, (float)aimPos.y, 1 };

	posNear = MatCalc::GetIns()->Wdivided(posNear, matInverseVPV);
	posFar = MatCalc::GetIns()->Wdivided(posFar, matInverseVPV);

	XMVECTOR mouseDirection = posFar - posNear;
	mouseDirection = XMVector3Normalize(mouseDirection);

	const float kDistanceTestObject = 50.0f;
	aimPos3d = (mouseDirection + posNear) * kDistanceTestObject;

	aim3d->SetPosition(aimPos3d);

}

void Player::FreeFall()
{
	if (fallFlag) {
		fallTime += 0.1f;
		//float fallSpeed = 2 / 1 * gravity * fallTime * fallTime;
		fallSpeed = gravity * fallTime * fallTime /1.5;
		if (fallSpeed > 3.5) { fallSpeed = 3.5f; }
		playerLPos.y -= fallSpeed;
		//playerLPos.y = 0.0f;
		player->SetPosition(playerLPos);
	}
}

void Player::JumpUpdate()
{
	if (jumpType != NONE_JUMP)
	{
		fallTime = 0.0f;
		fallFlag = false;
		if (STAMP_JUMP) {
			jumpTime += 0.1f;
			playerLPos.y += jumpTimePower / jumpTime;
			player->SetPosition(playerLPos);
			if ( jumpTime >= 2.3f) {
				jumpTime = 0;
				jumpType = NONE_JUMP;
				fallFlag = true;
			}
		}
	}
}

void Player::StampJump()
{
	jumpType = STAMP_JUMP;
}

void Player::DecelerationBoost()
{
	if (KeyInput::GetIns()->PushKey(DIK_SPACE) && boostCapacity > 0) {
		boostCapacity -= 0.1f;
		boostTime += 0.1f;
		boostSpeed = boostPower * boostTime;
		if (boostSpeed > 3) { boostSpeed = 3; }		
	}
	else
	{
		boostTime = 0;
		boostSpeed -= 0.3;
		if (boostSpeed < 0) { boostSpeed = 0; }
	}
	playerLPos.y += boostSpeed;
	player->SetPosition(playerLPos);
}