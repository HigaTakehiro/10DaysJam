#pragma once
#include "Object3d.h"
#include "Vector3.h"
#include "FBXObject3d.h"
#include "DirectXMath.h"

class Collision final
{
private:
	Collision() = default;
	~Collision() = default;
	Collision(const Collision& obj) = delete;
	Collision& operator=(const Collision& obj) = delete;

public: //静的メンバ関数
	/// <summary>
	/// インスタンス取得用関数
	/// </summary>
	/// <returns>インスタンス</returns>
	static Collision* GetIns();

public: //メンバ関数

	bool Collision::BoxCollision(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2);

	/// <summary>
	/// 球と球の当たり判定(OBJ同士)
	/// </summary>
	/// <param name="object1">判定したいオブジェクト1</param>
	/// <param name="object2">判定したいオブジェクト2</param>
	/// <returns>当たった</returns>
	bool OBJSphereCollision(Object3d* object1, Object3d* object2, float r1 = -1, float r2 = -1);

	/// <summary>
	/// 球と球の当たり判定(FBXとOBJ)
	/// </summary>
	/// <param name="object1">判定したいオブジェクト(OBJ)</param>
	/// <param name="object2">判定したいオブジェクト(FBX)</param>
	/// <param name="r1">OBJオブジェクトの半径</param>
	/// <param name="r2">FBXオブジェクトの半径</param>
	/// <returns>当たった</returns>
	bool FBXtoOBJSphereCollision(Object3d* object1, FBXObject3d* object2, float r1 = -1, float r2 = -1);

	/// <summary>
	/// 球と球の当たり判定(FBX同士)
	/// </summary>
	/// <param name="object1">判定したいオブジェクト1</param>
	/// <param name="object2">判定したいオブジェクト2</param>
	/// <param name="r1">オブジェクト1の半径</param>
	/// <param name="r2">オブジェクト2の半径</param>
	/// <returns></returns>
	bool FBXSphereCollision(FBXObject3d* object1, FBXObject3d* object2, float r1 = -1, float r2 = -1);

private: //メンバ変数
	Vector3 object1Pos = { 0, 0, 0 };
	Vector3 object2Pos = { 0, 0, 0 };

	Vector3 object1Scale = { 0, 0, 0 };
	Vector3 object2Scale = { 0, 0, 0 };

	float objectPosTotal = 0;
	float objectScaleTotal = 0;
};

