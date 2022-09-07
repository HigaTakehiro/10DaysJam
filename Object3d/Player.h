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

	float fallSpeed = 0;
	float fallTime =0;
	const float gravity = 0.098f;

	float jumpTime = 0;
	const float jumpTimePower = 0.3;

	JumpType jumpType = NONE_JUMP;


};

