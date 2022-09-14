#pragma once
#include "KeyInput.h"
#include "Object3d.h"
#include "Model.h"
#include "MouseInput.h"
#include "PadInput.h"
#include "Sprite.h"
#include "Vector3.h"
#include "Camera.h"
#include "DebugText.h"
#include "WinApp.h"
#include "PlayerBullet.h"
#include <memory>
#include  "MatCalc.h"
class Stage;

using namespace DirectX;
using namespace Microsoft::WRL;

class Player
{
	enum JumpType
	{
		NONE_JUMP,
		STAMP_JUMP,
	};

public: //メンバ関数
	/// <summary>
	/// 初期化処理
	/// </summary>
	void Initialize(Camera* camera);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 終了処理
	/// </summary>
	void Finalize();

	/// <summary>
	/// スプライト描画処理
	/// </summary>
	void SpriteDraw();

	/// <summary>
	/// 3Dオブジェクト描画処理
	/// </summary>
	void ObjectDraw();

	/// <summary>
	/// 位置取得
	/// </summary>
	/// <returns>位置</returns>
	const XMFLOAT3 GetPlayerPos() { return playerLPos; }

	/// <summary>
	/// 向き取得
	/// </summary>
	/// <returns>向き</returns>
	const XMFLOAT2 GetPlayerRot() { return aimPos; }

	/// <summary>
	/// プレイヤーオブジェクトの取得
	/// </summary>
	/// <returns>プレイヤーオブジェクト</returns>
	Object3d* GetPlayerObject() { return player; }

	/// <summary>
	/// 弾のリスト取得
	/// </summary>
	/// <returns>弾のリスト</returns>
	std::list<std::unique_ptr<PlayerBullet>>& GetBullet() { return bullets; }

	/// <summary>
	/// リセット処理
	/// </summary>
	void Reset();

	/// <summary>
	/// 敵を踏んでジャンプ
	/// </summary>
	void StampJump();

	/// <summary>
	/// 落下速度取得
	/// </summary>
	float GetFallSpeed() { return fallSpeed; }

	/// <summary>
	/// 減速ブースト
	/// </summary>
	void DecelerationBoost();

	/// <summary>
	/// ブースト容量取得
	/// </summary>
	float GetBoostCapacity() { return boostCapacity; }

	void SetPlayerPos(XMFLOAT3 pos) { playerLPos = pos; }

	void Recovery() { boostCapacity += 4; if (boostCapacity >= maxBoostCapacity) { boostCapacity = maxBoostCapacity; } };

private: //メンバ関数
	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// 通常攻撃処理
	/// </summary>
	void Shot();

	/// <summary>
	/// 3dレティクル更新処理
	/// </summary>
	void AimUpdate();

	/// <summary>
	/// 自由落下更新処理
	/// </summary>
	void FreeFall();

	/// <summary>
	/// ジャンプ更新処理
	/// </summary>
	void JumpUpdate();

public:
	float num = 0;

private: //メンバ変数
	Vector3 playerLPos = { 0, 0, 0 };
	//Vector3 playerWPos = { 0, 0, 0 };
	Vector3 playerRot = { 0, 0, 0 };
	Vector3 playerScale = { 0, 0, 0 };

	Model* playerModel = nullptr;
	Model* aim3dModel = nullptr;
	Object3d* player = nullptr;
	Object3d* aim3d = nullptr;
	Sprite* aim = nullptr;
	std::list<std::unique_ptr<PlayerBullet>> bullets;

	bool isShot = false;
	//ゲームシーン用変数
	XMFLOAT2 aimPos;
	Vector3 oldShotPos;
	Vector3 targetAimPos;
	XMVECTOR positionRaticle;
	XMMATRIX matViewPort;
	XMMATRIX matViewProjection;
	XMFLOAT3 aimPosMath;

	Vector3 aimPos3d;
	Camera* camera;

	bool fallFlag = true;
	float fallSpeed = 0;
	float fallTime = 0;
	const float gravity = 0.098f;

	float jumpTime = 0;
	const float jumpTimePower = 0.8;
	JumpType jumpType = NONE_JUMP;

	bool decelerationFlag = false;
	const float maxBoostSpeed = 2.0f;
	const float boostPower = 2.0f;
	float boostSpeed = 0.0f;
	float boostTime = 0.0f;
	const float maxBoostCapacity = 20;
	float boostCapacity = maxBoostCapacity;

};

