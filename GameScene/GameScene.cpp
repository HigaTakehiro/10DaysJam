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

	//�J����������
	camera = new Camera;
	camera->SetEye(XMFLOAT3(50, 1, -700));
	camera->SetTarget(XMFLOAT3(50, 0, 0));

	//Sprite & DebugText�̏�����
	Sprite::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);

	Sprite::LoadTexture(debugTextNumber, L"Resources/debugfont.png");
	debugText.Initialize(debugTextNumber);

	//Sprite::LoadTexture(1, L"Resources/Aim.png");
	//sprite = Sprite::Create(1, { 0, 0 });
	Sprite::LoadTexture(2, L"Resources/TitleBackTex.png");
	background = Sprite::Create(2, { 0, 0 });

	//Sprite::LoadTexture(4, L"Resources/Title.png");
	//title = Sprite::Create(4, { 0, 0 });

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

	Sprite::LoadTexture(10, L"Resources/Title1.png");
	titlePos1 = { 90.0f, -500.0f };
	title1 = Sprite::Create(10, titlePos1);

	Sprite::LoadTexture(11, L"Resources/Title2.png");
	titlePos2 = { 340.0f, -500.0f };
	title2 = Sprite::Create(11, titlePos2);

	Sprite::LoadTexture(12, L"Resources/Title3.png");
	titlePos3 = { 590.0f, -500.0f };
	title3 = Sprite::Create(12, { 590, 100 });

	Sprite::LoadTexture(13, L"Resources/Title4.png");
	titleAlpha1 = 0.0f;
	title4 = Sprite::Create(13, { 360, 400 });

	Sprite::LoadTexture(14, L"Resources/Title5.png");
	titleAlpha2 = 0.0f;
	title5 = Sprite::Create(14, { 360, 500 });

	time = 0.0f;
	waitTime = 0.0f;

	//Object3d�̏�����
	Object3d::StaticInitialize(dxCommon->GetDev(), WinApp::window_width, WinApp::window_height);

	groundModel = Model::CreateModel("Block");
	ground = Object3d::Create(groundModel);
	groundPos = { 0, -70, 0 };
	ground->SetPosition(groundPos);
	groundScale = { 1500, 10, 1500 };
	ground->SetScale(groundScale);

	holeModel = Model::CreateModel("Hole");
	hole = Object3d::Create(holeModel);
	hole->SetPosition(Vector3(0.0f, -105.0f, 0.0f));
	hole->SetScale(Vector3(25.0f, 10.0f, 25.0f));

	celestialSphereModel = Model::CreateModel("CelestialSphere");
	celetialSphere = Object3d::Create(celestialSphereModel);
	celetialSphere->SetPosition(spherePos);
	celetialSphere->SetScale(sphereScale);

	player = new Player();
	player->Initialize(camera);

	stageModel = Model::CreateModel("Block");
	enemyModel = Model::CreateModel("Enemy");

	wall[0] = Object3d::Create(stageModel);
	wall[0]->SetPosition({ -150,500,0 });
	wall[0]->SetScale({ 50,5000,50 });
	wall[1] = Object3d::Create(stageModel);
	wall[1]->SetPosition({ 230,500,0 });
	wall[1]->SetScale({ 50,5000,50 });

	LoadEnemyData();

	//MapChip�̏�����
	mapchip = new MapChip;
	mapchip->MapChipInitialize();
	map1_a = mapchip->MapLoad("test1", 7, 4);
	map1_b = mapchip->MapLoad("test2", 7, 4);
	objects = mapchip->MapSet(map1_a, 7, 4, 0);
	objects2 = mapchip->MapSet(map1_b, 7, 4, 1);

	//FBX�̏�����
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
	playerJumpModel = FbxLoader::GetInstance()->LoadModelFromFile("Player_Jump");
	playerJump = new FBXObject3d;
	playerJump->Initialize();
	playerJump->SetModel(playerJumpModel);
	playerJump->SetScale({ 0.1f, 0.1f, 0.1f });
	playerJump->SetRotation({ 0.0f, 225.0f, 0.0f });
	titlePlayerPos = { 200.0f, 0.0f, 0.0f };
	playerJump->SetPosition(titlePlayerPos);

	playerWaitModel = FbxLoader::GetInstance()->LoadModelFromFile("Player_Wait");
	playerWait = new FBXObject3d;
	playerWait->Initialize();
	playerWait->SetModel(playerWaitModel);
	playerWait->SetRotation({ 0.0f, 225.0f, 0.0f });
	playerWait->SetScale({ 0.1f, 0.1f, 0.1f });
	playerWait->SetPosition({ 200.0f, 0.0f, 0.0f });
	playerWait->PlayAnimation();

	isDead = false;
	isClear = false;
	isTitle = true;
	isStart = false;

	//sound
	float a = 0.01;
	/*sound->LoadWave("Title.wav");
	sound->SetVolume("Title.wav", a);
	sound->PlayWave("Title.wav", true);*/
	sound->LoadWave("Main.wav");
	sound->SetVolume("Main.wav", a);
	sound->PlayWave("Main.wav", true);
	//Particle
	particleMan = ParticleManager::Create(dxCommon->GetDev());
	particleMan->Initialize(dxCommon->GetDev());

	//�w�i
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
	enemies.remove_if([](std::unique_ptr<Enemy>& enemy) {return enemy->IsDead(); });

	stages.remove_if([](std::unique_ptr<Stage>& stage) {return stage->IsDead(); });

	// DirectX���t���[�������@��������
	aimPosX = MouseInput::GetIns()->GetMousePoint().x;
	aimPosY = MouseInput::GetIns()->GetMousePoint().y;

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

	if (isTitle) {
		const float maxTime1 = 20.0f;
		const float maxTime2 = 40.0f;
		const float maxTime3 = 60.0f;
		const float maxTime4 = 100.0f;
		const float maxPosY = 100.0f;
		const float maxAlpha = 1.0f;

		camera->SetEye(XMFLOAT3(50, 1, -700));

		if (input->GetIns()->TriggerKey(DIK_R)) {
			isStart = false;
			titlePos1.y = -500.0f;
			titlePos2.y = -500.0f;
			titlePos3.y = -500.0f;
			titleAlpha1 = 0.0f;
			titleAlpha2 = 0.0f;
			titlePlayerPos = {200.0f, 0.0f, 0.0f};
			time = 0.0f;
			waitTime = 0.0f;
		}

		if (!isStart) {
			time++;
		}
		titlePos1.y = Easing::GetIns()->easeIn(time, maxTime1, maxPosY, titlePos1.y);
		titlePos2.y = Easing::GetIns()->easeIn(time, maxTime2, maxPosY, titlePos2.y);
		titlePos3.y = Easing::GetIns()->easeIn(time, maxTime3, maxPosY, titlePos3.y);
		titleAlpha1 = Easing::GetIns()->easeIn(time, maxTime3, maxAlpha, titleAlpha1);
		titleAlpha2 = Easing::GetIns()->easeIn(time, maxTime3, maxAlpha, titleAlpha2);

		title1->SetPosition(titlePos1);
		title2->SetPosition(titlePos2);
		title3->SetPosition(titlePos3);
		title4->SetAlpha(titleAlpha1);
		title5->SetAlpha(titleAlpha2);

		if (!isStart && !playerWait->GetIsAnimation()) {
			playerWait->PlayAnimation();
		}
		if (input->GetIns()->TriggerKey(DIK_SPACE) && !isStart) {
			isStart = true;
			playerWait->StopAnimation();
			playerJump->PlayAnimation(false);
		}
		if (isStart) {
			const float timeOver = 50.0f;
			const float maxPosY = 150.0f;
			float jumpSpeed = 10.0f;
			waitTime++;
			if (waitTime >= timeOver && titlePlayerPos.y <= maxPosY) {
				titlePlayerPos.x -= jumpSpeed;
				titlePlayerPos.y += jumpSpeed;
			}
			if (titlePlayerPos.x <= 50.0f) {
				titlePlayerPos.y -= 40.0f;
			}
			playerJump->SetPosition(titlePlayerPos);
			if (titlePlayerPos.y <= -500.0f) {
				isStart = false;
				isTitle = false;
				titlePos1.y = -500.0f;
				titlePos2.y = -500.0f;
				titlePos3.y = -500.0f;
				titleAlpha1 = 0.0f;
				titleAlpha2 = 0.0f;
				titlePlayerPos = { 200.0f, 0.0f, 0.0f };
				time = 0.0f;
				waitTime = 0.0f;
			}
		}

		playerJump->Update();
		playerWait->Update();
		ground->Update();
		hole->Update();
	}

	if (!isTitle && !isClear && !isDead) {
		//�v���g�^�C�v
		//�v���C���[�̗���
		//XMFLOAT3 eyepos = camera->GetEye();
		//eyepos.y = player->GetPlayerPos().y;
		//camera->SetEye(eyepos);
		//XMFLOAT3 targetpos = camera->GetTarget();
		//targetpos.y = eyepos.y;
		//camera->SetTarget(targetpos);
		//�G�l�~�[���ォ�瓥�񂾂�W�����v
		camera->SetEye(XMFLOAT3(50, 1, -300));


		score->Update();

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

		for (const std::unique_ptr<Enemy>& enemy : enemies) {
			if (Collision::GetIns()->OBJSphereCollision(player->GetPlayerObject(), enemy->GetEnemyObj(), 8, 8)) {
				if (player->GetPlayerPos().y > enemy->GetEnemyObj()->GetPosition().y)
				{
					player->StampJump();
				}
			}
		}

		//�����͈͂ɓ������琶��
		//�ǂ̃^�C�v�𐶐����邩�i�j
		//�G�Ƃ��Ԃ�Ȃ��悤�ɂ���
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
				//�����łĂ��Ȃ��^�C�v
				//stageObj[stageClip]->SetPosition({ -50,height ,-50 });
				break;
			}
			newStage->Initialize(stageModel, staegepos, { 0,0,0 }, { 20,20,20 });
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
		backGroundOBJ->Update(player->GetPlayerPos().y);
		/*BackGround1->Update();
		BackGround2->Update();
		BackGround3->Update();*/
		celetialSphere->Update();
		player->Update();

		//boostGauge -= 0.01f;		
		if (KeyInput::GetIns()->PushKey(DIK_Q)) { boostGauge--; }
		if (KeyInput::GetIns()->PushKey(DIK_E)) { boostGauge++; }
		float boostNum = (boostRemainWegiht / maxBoostGauge) * player->GetBoostCapacity();
		boostRemain->SetSize({ boostNum,40 });
		

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

	//if (input->GetIns()->TriggerKey(DIK_SPACE)) {
	//	
	//}

	//if (isClear) {
	//	if (input->GetIns()->TriggerKey(DIK_SPACE)) {
	//		Reset();

	//	}
	//}

	//if (isDead) {
	//	if (input->GetIns()->TriggerKey(DIK_SPACE)) {
	//		Reset();
	//	}
	//}
	if (input->PushKey(DIK_1))flag = 1;
	if (input->PushKey(DIK_2))flag = 2;
	if (input->PushKey(DIK_3))flag = 3;
	if (input->PushKey(DIK_4))flag = 4;
	if (input->PushKey(DIK_5))flag = 5;
	ParticleUpdate();
	//ScoreUP();
}

void GameScene::Draw() {
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCmdList();

	//�X�v���C�g�`�揈��(�w�i)
	Sprite::PreDraw(dxCommon->GetCmdList());
	background->Draw();
	Sprite::PostDraw();

	//3D�I�u�W�F�N�g�`�揈��
	Object3d::PreDraw(dxCommon->GetCmdList());
	if (isTitle) {
		ground->Draw();
		hole->Draw();
		if (isStart) {
			playerJump->Draw(dxCommon->GetCmdList());
		}
		else {
			playerWait->Draw(dxCommon->GetCmdList());
		}

	}
	if (!isTitle) {
		backGroundOBJ->Draw();
		/*BackGround1->Draw();
		BackGround2->Draw();
		BackGround3->Draw();*/

		//celetialSphere->Draw();
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
	}
	Object3d::PostDraw();
	ParticleManager::PreDraw(cmdList);
	particleMan->Draw();
	ParticleManager::PostDraw();
	//�X�v���C�g�`�揈��(UI��)
	Sprite::PreDraw(dxCommon->GetCmdList());
	if (!isTitle) {
		player->SpriteDraw();
		boostBack->Draw();
		boostRemain->Draw();
		boostFrame->Draw();
		score->Draw();
	}
	if (isTitle) {
		if (!isStart) {
			title1->Draw();
			title2->Draw();
			title3->Draw();
			title4->Draw();
			title5->Draw();
		}
	}
	if (isDead) {
		//gameover->Draw();
	}
	if (isClear) {
		//clear->Draw();
	}
	//ScoreDraw();
	debugText.DrawAll(dxCommon->GetCmdList());
	Sprite::PostDraw();

	// �S�D�`��R�}���h�����܂�
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
	//�t�@�C���X�g���[��
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
		//���p��؂�ŕ�������擾
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
			newEnemy->Initialize(enemyModel, pos, rot, scale); //FBX���Ăяo���ꍇ��Enemy01���Ăяo���Ă�������
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
	//if (input->TriggerKey(DIK_R))
	//{
	//	if (flag == 1)particleMan->PBustr(angle, pos);
	//	if (flag == 2)particleMan->PArts(angle, pos);
	//	if (flag == 3)particleMan->PQuik(angle, pos);
	//	if (flag == 4)particleMan->All(angle, pos);
	//	if (flag == 5)
	//	{
	//		angle++;
	//		ParticleCoal();
	//		pos.y = (rand() % 10) + 1;
	//	}
	//}
	if (input->TriggerKey(DIK_Q))
	{
		angle = 0;
		pos = {};
	}
	particleMan->Update();

}

