#include "GameScene.h"
#include "FBXObject3d.h"
#include <algorithm>
#include <fstream>

GameScene::GameScene() {

}

GameScene::~GameScene() {
	safe_delete(sprite);
	player->Finalize();
	safe_delete(player);
	safe_delete(map1_a);
	safe_delete(map1_b);
	safe_delete(ground);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Sound* sound) {
	assert(dxCommon);
	assert(sound);

	this->dxCommon = dxCommon;
	this->sound = sound;
	input = KeyInput::GetIns();

	//カメラ初期化
	camera = new Camera;
	camera->SetEye(XMFLOAT3(50, 1, -100));
	camera->SetTarget(XMFLOAT3(50, 0, 0));

	//Sprite & DebugTextの初期化
	Sprite::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);

	Sprite::LoadTexture(debugTextNumber, L"Resources/debugfont.png");
	debugText.Initialize(debugTextNumber);

	//Sprite::LoadTexture(1, L"Resources/Aim.png");
	//sprite = Sprite::Create(1, { 0, 0 });
	Sprite::LoadTexture(2, L"Resources/background.png");
	background = Sprite::Create(2, { 0, 0 });

	Sprite::LoadTexture(4, L"Resources/Title.png");
	title = Sprite::Create(4, { 0, 0 });

	Sprite::LoadTexture(5, L"Resources/Gameover.png");
	gameover = Sprite::Create(5, { 0, 0 });

	Sprite::LoadTexture(6, L"Resources/Clear.png");
	clear = Sprite::Create(6, { 0, 0 });

	//Nombers
	Sprite::LoadTexture(60, L"Resources/Numbers/No0.png");
	Sprite::LoadTexture(61, L"Resources/Numbers/No1.png");
	Sprite::LoadTexture(62, L"Resources/Numbers/No2.png");
	Sprite::LoadTexture(63, L"Resources/Numbers/No3.png");
	Sprite::LoadTexture(64, L"Resources/Numbers/No4.png");
	Sprite::LoadTexture(65, L"Resources/Numbers/No5.png");
	Sprite::LoadTexture(66, L"Resources/Numbers/No6.png");
	Sprite::LoadTexture(67, L"Resources/Numbers/No7.png");
	Sprite::LoadTexture(68, L"Resources/Numbers/No8.png");
	Sprite::LoadTexture(69, L"Resources/Numbers/No9.png");
	for (int i = 0; i < 10; i++)
	{
		score1[i] = Sprite::Create(60 + i, { 0, 0 });
		score1[i]->SetPosition({ scoredis * 1, 100 });
		score2[i] = Sprite::Create(60 + i, { 0, 0 });
		score2[i]->SetPosition({ scoredis * 2, 100 });
		score3[i] = Sprite::Create(60 + i, { 0, 0 });
		score3[i]->SetPosition({ scoredis * 3, 100 });
		score4[i] = Sprite::Create(60 + i, { 0, 0 });
		score4[i]->SetPosition({ scoredis * 4, 100 });
		score5[i] = Sprite::Create(60 + i, { 0, 0 });
		score5[i]->SetPosition({ scoredis * 5, 100 });
		score6[i] = Sprite::Create(60 + i, { 0, 0 });
		score6[i]->SetPosition({ scoredis * 6, 100 });
		score7[i] = Sprite::Create(60 + i, { 0, 0 });
		score7[i]->SetPosition({ scoredis * 7, 100 });
		score8[i] = Sprite::Create(60 + i, { 0, 0 });
		score8[i]->SetPosition({ scoredis * 8, 100 });
		score9[i] = Sprite::Create(60 + i, { 0, 0 });
		score9[i]->SetPosition({ scoredis * 9, 100 });

	}

	//Object3dの初期化
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);

	groundModel = Model::CreateModel("ground");
	ground = Object3d::Create(groundModel);
	groundPos = { 0, -50, 0 };
	ground->SetPosition(groundPos);
	groundScale = { 10, 10, 10 };
	ground->SetScale(groundScale);

	celestialSphereModel = Model::CreateModel("CelestialSphere");
	celetialSphere = Object3d::Create(celestialSphereModel);
	celetialSphere->SetPosition(spherePos);
	celetialSphere->SetScale(sphereScale);

	player = new Player();
	player->Initialize(camera);

	LoadEnemyData();

	//MapChipの初期化
	mapchip = new MapChip;
	mapchip->MapChipInitialize();
	map1_a = mapchip->MapLoad("test1", 7, 4);
	map1_b = mapchip->MapLoad("test2", 7, 4);
	objects = mapchip->MapSet(map1_a, 7, 4, 0);
	objects2 = mapchip->MapSet(map1_b, 7, 4, 1);

	//FBXの初期化
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDev());
	FBXObject3d::SetDevice(dxCommon->GetDev());
	FBXObject3d::SetCamera(camera);
	FBXObject3d::CreateGraphicsPipeline();
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("boneTest");
	object1 = new FBXObject3d;
	object1->Initialize();
	object1->SetModel(model1);
	object1->SetScale({ 5.0f, 5.0f, 5.0f });
	object1->PlayAnimation();

	isDead = false;
	isClear = false;
	isTitle = true;

	//sound
	sound->LoadWave("ice1.wav");
	float a = 0.1;
	sound->SetVolume("ice1.wav", a);

	//Particle
	particleMan = ParticleManager::Create(dxCommon->GetDev());
	particleMan->Initialize(dxCommon->GetDev());

}

void GameScene::Update() {
	enemies.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->IsDead(); });

	// DirectX毎フレーム処理　ここから
	aimPosX = MouseInput::GetIns()->GetMousePoint().x;
	aimPosY = MouseInput::GetIns()->GetMousePoint().y;

	if (isTitle) {
		if (input->GetIns()->TriggerKey(DIK_SPACE)) {
			isTitle = false;
		}
	}

	if (!isTitle && !isClear && !isDead) {

		if (input->PushKey(DIK_RIGHT)) {
			camera->CameraMoveEyeVector({ +2.0f, 0.0f, 0.0f });
		}
		if (input->PushKey(DIK_LEFT)) {
			camera->CameraMoveEyeVector({ -2.0f, 0.0f, 0.0f });
		}
		if (input->PushKey(DIK_UP)) {
			camera->CameraMoveEyeVector({ 0.0f, 0.0f, +2.0f });
		}
		if (input->PushKey(DIK_DOWN)) {
			camera->CameraMoveEyeVector({ 0.0f, 0.0f, -2.0f });
		}
		if (input->PushKey(DIK_Q)) {
			camera->CameraMoveEyeVector({ 0.0f, +2.0f, 0.0f });
		}
		if (input->PushKey(DIK_E)) {
			camera->CameraMoveEyeVector({ 0.0f, -2.0f, 0.0f });
		}

		char xPos[256];
		char yPos[256];
		sprintf_s(xPos, "Xpoint : %f, YPoint : %f, ZPoint : %f", player->GetPlayerPos().x, player->GetPlayerPos().y, player->GetPlayerPos().z);
		sprintf_s(yPos, "Xpoint : %d, YPoint : %d", MouseInput::GetIns()->GetMousePoint().x, MouseInput::GetIns()->GetMousePoint().y);
		debugText.Print(xPos, 0, 0, 2.0f);
		debugText.Print(yPos, 0, 50, 2.0f);

		const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player->GetBullet();

		for (const std::unique_ptr<Enemy>& enemy : enemies) {
			for (const std::unique_ptr<PlayerBullet>& bullet : playerBullets) {
				if (Collision::GetIns()->SphereCollision(bullet->GetBulletObj(), enemy->GetEnemyObj())) {
					enemy->OnCollision();
				}
			}
		}

		EnemyDataUpdate();

		if (enemies.empty()) {
			isClear = true;
		}

		for (std::unique_ptr<Enemy>& enemy : enemies) {
			enemy->Update();
		}

		celetialSphere->Update();
		ground->Update();
		player->Update();
		object1->Update();

		for (auto object : objects) {
			object->Update();
		}
		for (auto object : objects2) {
			object->Update();
		}
	}
	if (input->GetIns()->TriggerKey(DIK_SPACE)) {
		sound->PlayWave("ice1.wav", 0);
	}
	if (isClear) {
		if (input->GetIns()->TriggerKey(DIK_SPACE)) {
			Reset();

		}
	}

	if (isDead) {
		if (input->GetIns()->TriggerKey(DIK_SPACE)) {
			Reset();
		}
	}
	if (input->PushKey(DIK_1))flag = 1;
	if (input->PushKey(DIK_2))flag = 2;
	if (input->PushKey(DIK_3))flag = 3;
	if (input->PushKey(DIK_4))flag = 4;
	if (input->PushKey(DIK_5))flag = 5;
	ParticleUpdate();
	ScoreUP();
}

void GameScene::Draw() {
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCmdList();

	//スプライト描画処理(背景)
	Sprite::PreDraw(dxCommon->GetCmdList());
	//background->Draw();
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(dxCommon->GetCmdList());
	ground->Draw();
	celetialSphere->Draw();

	if (!isDead) {
		player->ObjectDraw();
	}
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->Draw();
	}
	//object1->Draw(dxCommon->GetCmdList());
	Object3d::PostDraw();
	ParticleManager::PreDraw(cmdList);
	particleMan->Draw();
	ParticleManager::PostDraw();
	//スプライト描画処理(UI等)
	Sprite::PreDraw(dxCommon->GetCmdList());
	player->SpriteDraw();
	if (isTitle) {
		title->Draw();
	}
	if (isDead) {
		gameover->Draw();
	}
	if (isClear) {
		clear->Draw();
	}
	ScoreDraw();
	debugText.DrawAll(dxCommon->GetCmdList());
	Sprite::PostDraw();

	// ４．描画コマンドここまで
}

void GameScene::Finalize() {
	safe_delete(camera);
	mapchip->MapChipFinalize();
	objects.clear();
	objects.shrink_to_fit();
	objects2.clear();
	objects2.shrink_to_fit();
	safe_delete(mapchip);
	safe_delete(object1);
	safe_delete(model1);
	FbxLoader::GetInstance()->Finalize();
}

void GameScene::Reset() {
	camera->SetEye(XMFLOAT3(50, 1, -100));
	camera->SetTarget(XMFLOAT3(50, 0, 0));

	player->Reset();

	isDead = false;
	isClear = false;
	isTitle = true;

	LoadEnemyData();
}

void GameScene::LoadEnemyData() {
	//ファイルストリーム
	std::ifstream file;
	enemyData.str("");
	enemyData.clear(std::stringstream::goodbit);
	enemies.clear();

	const std::string filename = "EnemySet.aid";
	const std::string directory = "Resources/";
	file.open(directory + filename);
	if (file.fail()) {
		assert(0);
	}

	enemyData << file.rdbuf();

	file.close();
}

void GameScene::EnemyDataUpdate() {
	std::string line;
	Vector3 pos{};
	Vector3 rot{};
	Vector3 scale{};
	bool isPos = false;
	bool isRot = false;
	bool isScale = false;

	while (getline(enemyData, line)) {
		std::istringstream line_stream(line);
		std::string word;
		//半角区切りで文字列を取得
		getline(line_stream, word, ' ');
		if (word == "#") {
			continue;
		}
		if (word == "Pos") {
			//Vector3 pos{};
			line_stream >> pos.x;
			line_stream >> pos.y;
			line_stream >> pos.z;
			isPos = true;
		}
		if (word == "Rot") {
			//Vector3 rot{};
			line_stream >> rot.x;
			line_stream >> rot.y;
			line_stream >> rot.z;
			isRot = true;
		}
		if (word == "Scale") {
			//Vector3 scale{};
			line_stream >> scale.x;
			line_stream >> scale.y;
			line_stream >> scale.z;
			isScale = true;
		}

		if (isPos && isRot && isScale) {
			std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
			newEnemy->Initialize("Enemy", pos, rot, scale);
			enemies.push_back(std::move(newEnemy));
		}
	}
}

void GameScene::ParticleCoal()
{
	const float rnd_pos = 10.0f;
	const float radius = 0.3f;
	const float rnd_vel = 0.1f;
	for (int i = 0; i < PCount * 2; i++)
	{


		//XMFLOAT3 pos{};
	/*	pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		*/


		XMFLOAT3 acc{};
		const float rnd_acc = 0.00003f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		XMFLOAT3 vel{};
		//vel.z = tan((radian[i * angle] * PI) / 180) * radius;
		//for (int j = 0; j < PCount/2; j++)
		//{
		//	vel.x = cos((radian[j * angle] * PI) / 180) * radius;

		//	vel.y = sin((radian[j * angle] * PI) / 180) * radius;
		//	particleMan->Add(30, pos, vel, acc, 1.0f, 0.0f);
		//}






		if (i % 45 == 0)
		{
			if (i + angle < 360)
			{
				vel.z = sin((radian[i + angle] * PI) / 180) * radius;
				vel.x = cos((radian[i + angle] * PI) / 180) * radius;
				particleMan->Add(100, pos, vel, acc, 1.0f, 1.0f);
			}
			if (i + angle > 360)
			{
				vel.z = sin((radian[i + angle - 360] * PI) / 180) * radius;
				vel.x = cos((radian[i + angle - 360] * PI) / 180) * radius;
				particleMan->Add(100, pos, vel, acc, 1.0f, 1.0f);
			}
		}

		/*
		if (i * angle < 360)
		{
			vel.z = sin((radian[i + angle] * PI) / 180) * radius;
			vel.x = cos((radian[i + angle] * PI) / 180) * radius;
			particleMan->Add(100, pos, vel, acc, 1.0f, 1.0f);
		}
		if (i * angle > 360)
		{
			vel.z = sin((radian[i + angle-360] * PI) / 180) * radius;
			vel.x = cos((radian[i + angle-360] * PI) / 180) * radius;
			particleMan->Add(100, pos, vel, acc, 1.0f, 1.0f);
		}*/
		//vel.y = sin((radian[i * angle] * PI) / 180) * radius;





		/*vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;*/
		//particleMan->Add(60, pos, vel, acc,1.0f,0.0f);

	}
}

void GameScene::ParticleUpdate()
{
	if (input->TriggerKey(DIK_R))
	{
		if (flag == 1)particleMan->PBustr(angle, pos);
		if (flag == 2)particleMan->PArts(angle, pos);
		if (flag == 3)particleMan->PQuik(angle, pos);
		if (flag == 4)particleMan->All(angle, pos);
		if (flag == 5)
		{
			angle++;
			ParticleCoal();
			pos.y = (rand() % 10) + 1;
		}
	}
	if (input->TriggerKey(DIK_Q))
	{
		angle = 0;
		pos = {};
	}
	particleMan->Update();

}

void GameScene::ScoreUP()
{
	Score++;
	if (Score >= 10000)
	{
		Score5 = Score / 10000;
		Score4 = (Score - (Score5 * 10000)) / 1000;
		Score3 = (Score - (Score5 * 10000) - (Score4 * 1000)) / 100;
		Score2 = (Score - (Score5 * 10000) - (Score4 * 1000) - (Score3 * 100)) / 10;
		Score1 = (Score - (Score5 * 10000) - (Score4 * 1000) - (Score3 * 100) - (Score2 * 10));

	}
	if (Score % 100000 == 0)
	{
		Score1++;
		Score = 0;
	}
	if (Score1 % 10 == 0)
	{
		Score1 = 0;
		Score2++;
	}
	if (Score2 % 10 == 0)
	{
		Score2 = 0;
		Score3++;
	}
	if (Score3 % 10 == 0)
	{
		Score3 = 0;
		Score4++;
	}
	if (Score4 % 10 == 0)
	{
		Score4 = 0;
		Score5++;
	}
	if (Score5 % 10 == 0)
	{
		Score5 = 0;
		Score6++;
	}
	if (Score6 % 10 == 0)
	{
		Score6 = 0;
		Score7++;
	}
	if (Score7 % 10 == 0)
	{
		Score7 = 0;
		Score8++;
	}
	if (Score8 % 10 == 0)
	{
		Score8 = 0;
		Score9++;
	}
	if (Score9 % 10 == 0)
	{
		Score9 = 0;
	}
}

void GameScene::ScoreDraw()
{
	for (int i = 0; i < 10; i++)
	{
		if (Score1 == i)score1[i]->Draw();
		if (Score2 == i)score2[i]->Draw();
		if (Score3 == i)score3[i]->Draw();
		if (Score4 == i)score4[i]->Draw();
		if (Score5 == i)score5[i]->Draw();
		if (Score6 == i)score6[i]->Draw();
		if (Score7 == i)score7[i]->Draw();
		if (Score8 == i)score8[i]->Draw();
		if (Score9 == i)score9[i]->Draw();

	}

}
