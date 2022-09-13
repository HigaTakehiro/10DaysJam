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
#include"Score.h"

#include <sstream>
#include "Stage.h"

using namespace DirectX;
using namespace Microsoft::WRL;

class GameScene
{
private: //�ÓI�����o�ϐ�
	//�f�o�b�N�e�L�X�g�p�e�N�X�`���ԍ�
	static const int debugTextNumber = 0;

public: //�����o�֐�
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	GameScene();

	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~GameScene();

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Sound* sound);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	/// <summary>
	/// �G�l�~�[�f�[�^�̓ǂݍ���
	/// </summary>
	void LoadEnemyData();

	/// <summary>
	/// �ǂݍ��񂾃G�l�~�[�f�[�^�̍X�V
	/// </summary>
	void EnemyDataUpdate();

/// <summary>
/// �p�[�e�B�N���֘A
/// </summary>
	void ParticleCoal();

	void ParticleUpdate();

///// <summary>
///// �X�R�A�֘A
///// </summary>
//	void ScoreUP();
//	void ScoreDraw();

private: //�����o�֐�

	/// <summary>
	/// ���Z�b�g����
	/// </summary>
	void Reset();

private: //�����o�ϐ�
	DirectXCommon* dxCommon = nullptr;
	KeyInput* input = nullptr;
	WinApp* winApp = nullptr;
	DebugText debugText;
	Sound* sound = nullptr;
	Camera* camera = nullptr;
	MapChip* mapchip = nullptr;

	//�Q�[���I�u�W�F�N�g & �X�v���C�g
	Player* player = nullptr;
	std::list<std::unique_ptr<Enemy>> enemies;
	Sprite* sprite = nullptr;
	Sprite* background = nullptr;
	Sprite* title = nullptr;
	Sprite* gameover = nullptr;
	Sprite* clear = nullptr;
	Sprite* boostBack = nullptr;
	Sprite* boostFrame = nullptr;
	Sprite* boostRemain = nullptr;

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
	std::list<std::unique_ptr<Stage>>stages;
	//Model* stageModel = nullptr;
	Object3d* wall[2] = { nullptr };


	//�}�b�v�`�b�v�p�ϐ�
	int** map1_a = nullptr;
	int** map1_b = nullptr;
	std::vector<Object3d*> objects;
	std::vector<Object3d*> objects2;

	//FBX�p�ϐ�
	FBXModel* model1 = nullptr;
	FBXObject3d* object1 = nullptr;

	//�Q�[���V�[���p�ϐ�
	float aimPosX;
	float aimPosY;
	bool isDead;
	bool isTitle;
	bool isClear;
	std::stringstream enemyData;

	//�p�[�e�B�N��
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

	//�X�R�A
	Score* score = nullptr;
	/*Sprite* score1[10];
	Sprite* score2[10];
	Sprite* score3[10];
	Sprite* score4[10];
	Sprite* score5[10];
	Sprite* score6[10];
	Sprite* score7[10];
	Sprite* score8[10];
	Sprite* score9[10];
	int Score = 0;
	int Score1 = 0;
	int Score2 = 0;
	int Score3 = 0;
	int Score4 = 0;
	int Score5 = 0;
	int Score6 = 0;
	int Score7 = 0;
	int Score8 = 0;
	int Score9 = 0;
	float scoredis = 16;
	float scoreTime = 0.0f;*/
	


	float maxBoostGauge = 20;
	float boostGauge = maxBoostGauge;
	float boostRemainWegiht = 200;
};

