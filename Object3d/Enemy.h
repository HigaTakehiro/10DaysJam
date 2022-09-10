#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "Player.h"
#include "FbxLoader.h"
#include "FBXObject3d.h"
#include "DirectXCommon.h"

class Enemy
{
	enum EnemyStyle {
		ONEJUMP_ENEMY,
		TWOJUMP_ENEMY
	};

public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(const std::string& modelName, Vector3 pos, Vector3 rot, Vector3 scale);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw(DirectXCommon* dxCommon);

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 敵の状態を取得
	/// </summary>
	/// <returns>敵の状態</returns>
	bool IsDead() const { return isDead; }

	/// <summary>
	/// 敵オブジェクト取得
	/// </summary>
	/// <returns>敵オブジェクト</returns>
	Object3d* GetEnemyObj() { return enemy; }

private: //メンバ変数

	Model* enemyModel;
	Object3d* enemy;
	FBXObject3d* testEnemy;
	FBXModel* testEnemyModel;
	Vector3 pos;
	bool isDead;
};

