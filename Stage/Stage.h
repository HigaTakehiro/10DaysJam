#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "DirectXCommon.h"

class Stage
{

public: //メンバ関数

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, Vector3 pos, Vector3 rot, Vector3 scale);

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

	XMFLOAT3 GetStagePos() { return stage->GetPosition(); }

	void SetStagePos(XMFLOAT3 pos) { stage->SetPosition(pos); }

	void SetTouch() { isTouch = true; }

	/// <summary>
	/// ステージオブジェクト取得
	/// </summary>
	/// <returns>ステージオブジェクト</returns>
	Object3d* GetStageObj() { return stage; }

	bool IsDead() { return isDead; }

	bool IsTouch() { return isTouch; }

	void SetDead() { isDead = true; }

private: //メンバ変数

	Model* stageModel;
	Object3d* stage;
	Vector3 pos;
	bool isDead;
	int time = 0;
	bool isTouch = false;	//プレイヤーと触れたことがあるかどうか
};

