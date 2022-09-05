#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "MatCalc.h"

class PlayerBullet
{
public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector3 pos, Vector3 velocity);

	/// <summary>
	/// 更新処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画処理
	/// </summary>
	void Draw();

	/// <summary>
	/// 衝突時コールバック関数
	/// </summary>
	void OnCollision();

	/// <summary>
	/// 弾の状態を取得
	/// </summary>
	/// <returns>弾の状態</returns>
	bool IsDead() const { return isDead; }

	/// <summary>
	/// 弾オブジェクト取得
	/// </summary>
	/// <returns>弾オブジェクト</returns>
	Object3d* GetBulletObj() { return bullet; }

private: //静的メンバ変数
	static const int32_t lifeTime = 60 * 2;

private: //メンバ変数
	Model* bulletModel;
	Object3d* bullet;
	Vector3 pos;
	bool isDead;
	int32_t lifeTimer = lifeTime;
	Vector3 velocity;
};

