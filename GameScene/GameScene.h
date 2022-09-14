#pragma once
#include "KeyInput.h"//
#include "DirectXCommon.h"//
#include "Object3d.h"
#include "Model.h"
#include "Sprite.h"
#include "DebugText.h"
#include "Sound.h"//
#include "Camera.h"
#include "MapChip.h"
#include "SafeDelete.h"
#include "FbxLoader.h"
#include "FBXObject3d.h"
#include "MouseInput.h"
#include "PadInput.h"
#include "Player.h"
#include "Enemy.h"
#include "Collision.h"
#include "PlayerBullet.h"
#include "ParticleManager.h"
#include "Score.h"
#include "BackGround.h"
#include "Wall.h"
#include "StageManager.h"
#include "Easing.h"
#include "EnemyManager.h"

#include <sstream>
#include "Stage.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class GameScene
{
private: //静的メンバ変数
	//デバックテキスト用テクスチャ番号
	static const int debugTextNumber = 0;

public: //メンバ関数
	/// <summary>
	/// コンストラクタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Sound* sound);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// エネミーデータの読み込み
	/// </summary>
	void LoadEnemyData();

	/// <summary>
	/// 読み込んだエネミーデータの更新
	/// </summary>
	void EnemyDataUpdate();

	/// <summary>
	/// パーティクル関連
	/// </summary>
	void ParticleCoal();

	void ParticleUpdate();

private: //メンバ関数

	/// <summary>
	/// リセット処理
	/// </summary>
	void Reset();

private: //メンバ変数
	DirectXCommon* dxCommon = nullptr;
	KeyInput* input = nullptr;
	WinApp* winApp = nullptr;
	DebugText debugText;
	Sound* sound = nullptr;
	Camera* camera = nullptr;
	MapChip* mapchip = nullptr;

	//ゲームオブジェクト & スプライト
	Player* player = nullptr;
	Sprite* sprite = nullptr;
	Sprite* background = nullptr;
	Sprite* title1 = nullptr;
	Sprite* title2 = nullptr;
	Sprite* title3 = nullptr;
	Sprite* title4 = nullptr;
	Sprite* title5 = nullptr;
	Sprite* gameover = nullptr;
	Sprite* clear = nullptr;
	Sprite* boostBack = nullptr;
	Sprite* boostFrame = nullptr;
	Sprite* boostRemain = nullptr;
	Sprite* leftArrow = nullptr;
	Sprite* rightArrow = nullptr;
	Sprite* space = nullptr;

	Model* celestialSphereModel = nullptr;
	Model* groundModel = nullptr;
	Object3d* celetialSphere = nullptr;
	Object3d* ground = nullptr;
	Vector3 groundPos = { 0, 0, 0 };
	Vector3 groundScale = { 1, 1, 1 };
	Vector3 spherePos = { 0, 0, 0 };
	Vector3 sphereScale = { 10, 10, 10 };

	Model* stageModel = nullptr;
	Model* enemyModel = nullptr;
	//Object3d* stageObj[20] = { nullptr };	
	//Model* stageModel = nullptr;
	Object3d* wall[2] = { nullptr };
	Model* holeModel = nullptr;
	Object3d* hole = nullptr;
	Object3d* stageTest[3] = { nullptr };
	StageManager* stageManager = nullptr;
	EnemyManager* enemyManager = nullptr;

	
	//Wall* wall = nullptr;

	//マップチップ用変数
	int** map1_a = nullptr;
	int** map1_b = nullptr;
	std::vector<Object3d*> objects;
	std::vector<Object3d*> objects2;

	//FBX用変数
	FBXModel* playerJumpModel = nullptr;
	FBXObject3d* playerJump = nullptr;
	FBXModel* playerWaitModel = nullptr;
	FBXObject3d* playerWait = nullptr;

	//ゲームシーン用変数
	float aimPosX;
	float aimPosY;
	bool isDead;
	bool isTitle;
	bool isClear;
	bool isStart;
	std::stringstream enemyData;
	XMFLOAT2 titlePos1;
	XMFLOAT2 titlePos2;
	XMFLOAT2 titlePos3;
	Vector3 titlePlayerPos;
	float titleAlpha1;
	float titleAlpha2;
	float time;
	float waitTime;

	//パーティクル
	ParticleManager* particleMan = nullptr;
	const float PI = 3.1415926f;
	XMFLOAT3 pos = { 0,0,0 };
	int PCount = 180;
	int angle = 30;
	int radian[360];
	int fffff = 0;
	int flag = 1;

	int intervalTime = 0;
	int stageClip = 0;

	//スコア
	Score* score = nullptr;

	//背景
	Model* ModelBackGround = nullptr;
	Object3d* BackGround1 = nullptr;
	Object3d* BackGround2 = nullptr;
	Object3d* BackGround3 = nullptr;

	//背景
	BackGround* backGroundOBJ = nullptr;

	float maxBoostGauge = 20;
	float boostGauge = maxBoostGauge;
	float boostRemainWegiht = 200;
	XMFLOAT3 playerRad = { 7,10,10 };
	XMFLOAT3 enemyRad = { 10,10,10 };
	XMFLOAT3 stageRad = { 50,20,10 };
	float enemyCenter = 5;
	float stageCenter = 28;
	XMFLOAT3 oldPlayerPos = { 0,0,0 };

	XMFLOAT3 eyepos;
	XMFLOAT3 targetpos;
};

