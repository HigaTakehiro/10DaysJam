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
	for (int i = 0; i < 20; i++) {
		//stageObj[i] = Object3d::Create(stageModel);
		//stageObj[i]->SetPosition({ 0,0,0 });
		//stageObj[i]->SetScale({ 50,50,50 });
	}

	wall[0] = Object3d::Create(stageModel);
	wall[0]->SetPosition({ -150,500,0 });
	wall[0]->SetScale({ 50,5000,50 });
	wall[1] = Object3d::Create(stageModel);
	wall[1]->SetPosition({ 230,500,0 });
	wall[1]->SetScale({ 50,5000,50 });

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
	/*model1 = FbxLoader::GetInstance()->LoadModelFromFile("Enemy01");
	object1 = new FBXObject3d;
	object1->Initialize();
	object1->SetModel(model1);
	object1->SetScale({ 0.1f, 0.1f, 0.1f });
	object1->PlayAnimation();*/

	isDead = false;
	isClear = false;
	isTitle = false;

	//sound
	sound->LoadWave("ice1.wav");
	float a = 0.1;
	sound->SetVolume("ice1.wav", a);
}

void GameScene::Update() {
	enemies.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->IsDead(); });

	stages.remove_if([](std::unique_ptr<Stage>& stage) {return stage->IsDead(); });

	// DirectX毎フレーム処理　ここから
	aimPosX = MouseInput::GetIns()->GetMousePoint().x;
	aimPosY = MouseInput::GetIns()->GetMousePoint().y;

	if (isTitle) {
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

		const std::list<std::unique_ptr<PlayerBullet>>& playerBullets = player->GetBullet();

		for (const std::unique_ptr<Enemy>& enemy : enemies) {
			if (Collision::GetIns()->OBJSphereCollision(player->GetPlayerObject(), enemy->GetEnemyObj(), 8, 8)) {
				if (player->GetPlayerPos().y > enemy->GetEnemyObj()->GetPosition().y)
				{
					player->StampJump();
				}
			}
		}

		//生成範囲に入ったら生成
		//どのタイプを生成するか（）
		//敵とかぶらないようにする
		intervalTime--;
		if (intervalTime < 0) {			
			int type = rand() % 6;
			float height = player->GetPlayerPos().y - 50;
			std::unique_ptr<Stage> newStage = std::make_unique<Stage>();			
			XMFLOAT3 staegepos = { 0,0,0 };
			switch (type) {
			case 0:
				staegepos = { -50,height ,-50 };
				break;
			case 1:
				staegepos = { 50,height ,-50 };
				break;
			case 2:
				staegepos = { 150,height ,-50 };
				break;
			case 3:
				staegepos = { -50,height - 20 ,-50 };
				break;
			case 4:
				staegepos = { 50,height - 20,-50 };
				break;
			case 5:
				staegepos = { 150,height - 20,-50 };
				break;
			case 6:
				//stageObj[stageClip]->SetPosition({ -50,height ,-50 });
				break;
			case 7:
				//何もでてこないタイプ
				//stageObj[stageClip]->SetPosition({ -50,height ,-50 });
				break;
			}
			newStage->Initialize("Block", staegepos, { 0,0,0 }, { 20,20,20 });
			stages.push_back(std::move(newStage));	
			intervalTime = rand() % 100;
		}

		EnemyDataUpdate();

		if (enemies.empty()) {
			isClear = true;
		}

		for (std::unique_ptr<Enemy>& enemy : enemies) {
			enemy->Update();
		}

		XMFLOAT3 eyepos = camera->GetEye();
		eyepos.y = player->GetPlayerPos().y;
		camera->SetEye(eyepos);
		XMFLOAT3 targetpos = camera->GetTarget();
		targetpos.y = player->GetPlayerPos().y;
		camera->SetTarget(targetpos);

		celetialSphere->Update();
		ground->Update();
		player->Update();
		//object1->Update();
		for (std::unique_ptr<Stage>& stage : stages) {
			stage->Update();
		}
		for (int i = 0; i < 2; i++) {
			wall[i]->Update();
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
}

void GameScene::Draw() {

	//スプライト描画処理(背景)
	Sprite::PreDraw(dxCommon->GetCmdList());
	//background->Draw();
	Sprite::PostDraw();

	//3Dオブジェクト描画処理
	Object3d::PreDraw(dxCommon->GetCmdList());
	//ground->Draw();
	celetialSphere->Draw();
	for (std::unique_ptr<Stage>& stage : stages) {
		stage->Draw();
	}
	for (int i = 0; i < 2; i++) {
		wall[i]->Draw();
	}

	if (!isDead) {
		player->ObjectDraw();
	}
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->Draw(dxCommon);
	}
	//object1->Draw(dxCommon->GetCmdList());
	Object3d::PostDraw();

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
			newEnemy->Initialize("Enemy", pos, rot, scale); //FBXを呼び出す場合はEnemy01を呼び出してください
			enemies.push_back(std::move(newEnemy));
		}
	}
}