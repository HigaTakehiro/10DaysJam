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
	camera->SetEye(XMFLOAT3(50, 1, -300));
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
	score = new Score();
	score->Initialize();


	Sprite::LoadTexture(7, L"Resources/BoostGauge_Back.png");
	boostBack = Sprite::Create(7, { 0, 0 });

	Sprite::LoadTexture(8, L"Resources/BoostGauge_Frame.png");
	boostFrame = Sprite::Create(8, { 0, 0 });

	Sprite::LoadTexture(9, L"Resources/BoostGauge_Remain.png");
	boostRemain = Sprite::Create(9, { 0, 0 });

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

	stageModel = Model::CreateModel("Block");
	enemyModel = Model::CreateModel("Enemy");

	//wall[0] = Object3d::Create(stageModel);
	//wall[0]->SetPosition({ -150,500,0 });
	//wall[0]->SetScale({ 50,5000,50 });
	//wall[1] = Object3d::Create(stageModel);
	//wall[1]->SetPosition({ 230,500,0 });
	//wall[1]->SetScale({ 50,5000,50 });

	wall[0] = Object3d::Create(stageModel);
	wall[0]->SetPosition({ -120,500,-50 });
	wall[0]->SetScale({ 40,5000,40 });
	wall[0]->SetRotation({ 0,-22,0 });
	wall[1] = Object3d::Create(stageModel);
	wall[1]->SetPosition({ 200,500,-50 });
	wall[1]->SetScale({ 40,5000,40 });
	wall[1]->SetRotation({ 0,288,0 });
	for (int i = 0; i < 3; i++)
	{
		stageTest[i] = Object3d::Create(stageModel);
		stageTest[i]->SetPosition({ -50.0f + 90.0f * i,1000.0f ,-50.0f });
		stageTest[i]->SetScale({ 90,50,50 });
	}
	stageManager = new StageManager;
	stageManager->Initialize(player, stageModel);

	//FBXの初期化
	FbxLoader::GetInstance()->Initialize(dxCommon->GetDev());
	FBXObject3d::SetDevice(dxCommon->GetDev());
	FBXObject3d::SetCamera(camera);
	FBXObject3d::CreateGraphicsPipeline();
	model1 = FbxLoader::GetInstance()->LoadModelFromFile("Enemy01");
	enemyManager = new EnemyManager;
	enemyManager->Initialize(player, enemyModel, model1);

	LoadEnemyData();

	//MapChipの初期化
	mapchip = new MapChip;
	mapchip->MapChipInitialize();
	map1_a = mapchip->MapLoad("test1", 7, 4);
	map1_b = mapchip->MapLoad("test2", 7, 4);
	objects = mapchip->MapSet(map1_a, 7, 4, 0);
	objects2 = mapchip->MapSet(map1_b, 7, 4, 1);

	//FBX
	/*model1 = FbxLoader::GetInstance()->LoadModelFromFile("Enemy01");
	object1 = new FBXObject3d;
	object1->Initialize();
	object1->SetModel(model1);
	object1->SetScale({ 0.1f, 0.1f, 0.1f });
	object1->PlayAnimation();*/

	isDead = false;
	isClear = false;
	isTitle = true;

	//sound
	float a = 0.01;
	/*sound->LoadWave("Title.wav");
	sound->SetVolume("Title.wav", a);
	sound->PlayWave("Title.wav", true);*/
	sound->LoadWave("Main.wav");
	sound->SetVolume("Main.wav", a);
	//sound->PlayWave("Main.wav", true);
	//Particle
	particleMan = ParticleManager::Create(dxCommon->GetDev());
	particleMan->Initialize(dxCommon->GetDev());

	//背景
	backGroundOBJ = new BackGround();
	backGroundOBJ->Initialize();
	/*ModelBackGround = Model::CreateModel("BackGround");
	BackGround1 = Object3d::Create(ModelBackGround);
	BackGround1->SetPosition({ 46,0,0 });
	BackGround1->SetScale({4,4,4});
	BackGround2 = Object3d::Create(ModelBackGround);
	BackGround2->SetPosition({ 46,-800,0 });
	BackGround2->SetScale({ 4,4,4 });
	BackGround3 = Object3d::Create(ModelBackGround);
	BackGround3->SetPosition({ 46,+800,0 });
	BackGround3->SetScale({ 4,4,4 });*/
}

void GameScene::Update() {


	// DirectX毎フレーム処理　ここから
	aimPosX = MouseInput::GetIns()->GetMousePoint().x;
	aimPosY = MouseInput::GetIns()->GetMousePoint().y;

	if (isTitle) {
		camera->SetEye({ 50, 1, -700 });
		if (input->GetIns()->TriggerKey(DIK_SPACE)) {
			isTitle = false;
		}
	}

	if (!isTitle && !isClear && !isDead) {
		//プロトタイプ
		//プレイヤーの落下
		//XMFLOAT3 eyepos = camera->GetEye();
		//eyepos.y = player->GetPlayerPos().y;
		//camera->SetEye(eyepos);
		//XMFLOAT3 targetpos = camera->GetTarget();
		//targetpos.y = eyepos.y;
		//camera->SetTarget(targetpos);
		//エネミーを上から踏んだらジャンプ
		//camera->SetEye({ 50, 1, -300 });


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
		char fallSpeed[256];
		sprintf_s(fallSpeed, "fallSpeed : %f", player->GetFallSpeed());
		debugText.Print(fallSpeed, 0, 100, 2.0f);

		char buck[256];
		sprintf_s(buck, "Back1y:%f Back2y:%f Back3y:%f", backGroundOBJ->GetPos1(), backGroundOBJ->GetPos2(), backGroundOBJ->GetPos3());
		debugText.Print(buck, 0, 200, 2.0f);

		const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player->GetBullet();

		XMFLOAT3 playerpos = player->GetPlayerPos();
		if (KeyInput::GetIns()->PushKey(DIK_Q)) { stageCenter -= 10000; }
		if (KeyInput::GetIns()->PushKey(DIK_E)) { stageCenter += 10000; }
		if (KeyInput::GetIns()->PushKey(DIK_Z)) { enemyCenter -= 1; }
		if (KeyInput::GetIns()->PushKey(DIK_C)) { enemyCenter += 1; }

		if (KeyInput::GetIns()->PushKey(DIK_I)) { stageRad.x -= 1; }
		if (KeyInput::GetIns()->PushKey(DIK_P)) { stageRad.x += 1; }
		if (KeyInput::GetIns()->PushKey(DIK_B)) { stageRad.y -= 1; }
		if (KeyInput::GetIns()->PushKey(DIK_M)) { stageRad.y += 1; }

		for (std::unique_ptr<Stage>& stage : stageManager->GetStages()) {
			XMFLOAT3 stagepos = stage->GetStagePos();
			stagepos.y += stageCenter;
			if (Collision::GetIns()->BoxCollision(player->GetPlayerPos(), playerRad, stagepos, stageRad)) {
				if (oldPlayerPos.x > stagepos.x - 60 && oldPlayerPos.x < stagepos.x + 60 && oldPlayerPos.y > stagepos.y + 10) {
					//isDead = true;	//プレイヤーの死亡
				}
				else
				{

				}

				/*const float moveSpeed = 2.0f;
				const float autoSpeed = 0.2;
				XMFLOAT3 playerpos = player->GetPlayerPos();*/
				//if (KeyInput::GetIns()->PushKey(DIK_W)) {
				//	playerpos.y += moveSpeed;
				//	player->SetPlayerPos(playerpos);
				//}
				//if (KeyInput::GetIns()->PushKey(DIK_S)) {
				//	playerpos.y -= moveSpeed;
				//	player->SetPlayerPos(playerpos);
				//}
				//if (KeyInput::GetIns()->PushKey(DIK_A)) {
				//	playerpos.x -= moveSpeed;
				//	player->SetPlayerPos(playerpos);
				//	if (Collision::GetIns()->BoxCollision(player->GetPlayerPos(), playerRad, stagepos, stageRad)) {
				//		playerpos.x += moveSpeed;
				//		player->SetPlayerPos(playerpos);
				//	}
				//}
				//if (KeyInput::GetIns()->PushKey(DIK_D)) {
				//	playerpos.x += moveSpeed;
				//	player->SetPlayerPos(playerpos);
				//	if (Collision::GetIns()->BoxCollision(player->GetPlayerPos(), playerRad, stagepos, stageRad)) {
				//		playerpos.x -= moveSpeed;
				//		player->SetPlayerPos(playerpos);
				//	}
				//}

				char atatta[256];
				sprintf_s(atatta, "atata");
				debugText.Print(atatta, 0, 300, 2.0f);
				stage->SetTouch();
			}
		}

		for (std::unique_ptr<Enemy>& enemy : enemyManager->GetEnemies()) {
			XMFLOAT3 enemypos = enemy->GetEnemyFbx()->GetPosition();
			enemypos.y += enemyCenter;
			if (Collision::GetIns()->BoxCollision(player->GetPlayerPos(), playerRad, enemypos, { 5,5,5 })) {
				if (oldPlayerPos.x > enemypos.x - 20 && oldPlayerPos.x < enemypos.x + 20 && oldPlayerPos.y > enemypos.y + 10) {
					player->StampJump();
					enemy->SetDead();
				}
				else {
					isDead = true;
				}
				char atatta[256];
				sprintf_s(atatta, "atata");
				debugText.Print(atatta, 0, 300, 2.0f);
			}
		}

		//生成範囲に入ったら生成
			//どのタイプを生成するか（）
			//敵とかぶらないようにする
		stageManager->Update();
		enemyManager->Update();

		EnemyDataUpdate();



		eyepos = camera->GetEye();
		eyepos.y = player->GetPlayerPos().y;
		eyepos.z = -300.0f;
		camera->SetEye(eyepos);
		targetpos = camera->GetTarget();
		targetpos.y = player->GetPlayerPos().y;
		camera->SetTarget(targetpos);
		backGroundOBJ->Update(player->GetPlayerPos().y);
		/*BackGround1->Update();
		BackGround2->Update();
		BackGround3->Update();*/
		celetialSphere->Update();
		ground->Update();
		oldPlayerPos = player->GetPlayerPos();
		player->Update();

		//boostGauge -= 0.01f;		
		if (KeyInput::GetIns()->PushKey(DIK_Q)) { boostGauge--; }
		if (KeyInput::GetIns()->PushKey(DIK_E)) { boostGauge++; }
		float boostNum = (boostRemainWegiht / maxBoostGauge) * player->GetBoostCapacity();
		boostRemain->SetSize({ boostNum,40 });


		//object1->Update();
		for (int i = 0; i < 2; i++) {
			wall[i]->Update();
		}
		for (int i = 0; i < 3; i++) {
			stageTest[i]->Update();
		}

		for (auto object : objects) {
			object->Update();
		}
		for (auto object : objects2) {
			object->Update();
		}
	}

	if (input->GetIns()->TriggerKey(DIK_R))
	{
		Reset();
	}

	if (input->GetIns()->TriggerKey(DIK_SPACE)) {

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
	score->Update();
	//ScoreUP();
}

void GameScene::Draw() {
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCmdList();

	//スプライト描画処理(背景)
	Sprite::PreDraw(dxCommon->GetCmdList());
	//background->Draw();
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(dxCommon->GetCmdList());
	//ground->Draw();
	backGroundOBJ->Draw();
	/*BackGround1->Draw();
	BackGround2->Draw();
	BackGround3->Draw();*/

	//celetialSphere->Draw();
	for (int i = 0; i < 2; i++) {
		wall[i]->Draw();
	}
	for (int i = 0; i < 3; i++) {
		stageTest[i]->Draw();
	}
	//stageManager->Draw();
	for (std::unique_ptr<Stage>& stage : stageManager->GetStages()) {
		stage->Draw();
	}
	for (std::unique_ptr<Enemy>& stage : enemyManager->GetEnemies()) {
		stage->Draw(dxCommon);
	}

	if (!isDead) {
		player->ObjectDraw();
	}
	for (std::unique_ptr<Enemy>& enemy : enemyManager->GetEnemies()) {
		enemy->Draw(dxCommon);
	}
	//object1->Draw(dxCommon->GetCmdList());
	Object3d::PostDraw();
	ParticleManager::PreDraw(cmdList);
	particleMan->Draw();
	ParticleManager::PostDraw();
	//スプライト描画処理(UI等)
	Sprite::PreDraw(dxCommon->GetCmdList());
	player->SpriteDraw();
	boostBack->Draw();
	boostRemain->Draw();
	boostFrame->Draw();
	if (isTitle) {
		title->Draw();
	}
	if (isDead) {
		gameover->Draw();
	}
	if (isClear) {
		clear->Draw();
	}
	//ScoreDraw();
	score->Draw();
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
	/*safe_delete(object1);
	safe_delete(model1);*/
	FbxLoader::GetInstance()->Finalize();
}

void GameScene::Reset() {
	//camera->SetEye(XMFLOAT3(50, 1, -100));
	//camera->SetTarget(XMFLOAT3(50, 0, 0));

	player->Reset();

	isDead = false;
	isClear = false;
	//isTitle = true;

	LoadEnemyData();
}

void GameScene::LoadEnemyData() {
	////ファイルストリーム
	//std::ifstream file;
	//enemyData.str("");
	//enemyData.clear(std::stringstream::goodbit);
	//enemies.clear();

	//const std::string filename = "EnemySet.aid";
	//const std::string directory = "Resources/";
	//file.open(directory + filename);
	//if (file.fail()) {
	//	assert(0);
	//}

	//enemyData << file.rdbuf();

	//file.close();
}

void GameScene::EnemyDataUpdate() {
	//std::string line;
	//Vector3 pos{};
	//Vector3 rot{};
	//Vector3 scale{};
	//bool isPos = false;
	//bool isRot = false;
	//bool isScale = false;

	//while (getline(enemyData, line)) {
	//	std::istringstream line_stream(line);
	//	std::string word;
	//	//半角区切りで文字列を取得
	//	getline(line_stream, word, ' ');
	//	if (word == "#") {
	//		continue;
	//	}
	//	if (word == "Pos") {
	//		//Vector3 pos{};
	//		line_stream >> pos.x;
	//		line_stream >> pos.y;
	//		line_stream >> pos.z;
	//		isPos = true;
	//	}
	//	if (word == "Rot") {
	//		//Vector3 rot{};
	//		line_stream >> rot.x;
	//		line_stream >> rot.y;
	//		line_stream >> rot.z;
	//		isRot = true;
	//	}
	//	if (word == "Scale") {
	//		//Vector3 scale{};
	//		line_stream >> scale.x;
	//		line_stream >> scale.y;
	//		line_stream >> scale.z;
	//		isScale = true;
	//	}

	//	if (isPos && isRot && isScale) {
	//		std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
	//		newEnemy->Initialize(enemyModel, pos, rot, scale); //FBXを呼び出す場合はEnemy01を呼び出してください
	//		enemies.push_back(std::move(newEnemy));
	//	}
	//}
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

