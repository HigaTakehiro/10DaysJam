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

public: //�ÓI�����o�֐�
	/// <summary>
	/// �C���X�^���X�擾�p�֐�
	/// </summary>
	/// <returns>�C���X�^���X</returns>
	static Collision* GetIns();

public: //�����o�֐�

	bool Collision::BoxCollision(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2);

	/// <summary>
	/// ���Ƌ��̓����蔻��(OBJ���m)
	/// </summary>
	/// <param name="object1">���肵�����I�u�W�F�N�g1</param>
	/// <param name="object2">���肵�����I�u�W�F�N�g2</param>
	/// <returns>��������</returns>
	bool OBJSphereCollision(Object3d* object1, Object3d* object2, float r1 = -1, float r2 = -1);

	/// <summary>
	/// ���Ƌ��̓����蔻��(FBX��OBJ)
	/// </summary>
	/// <param name="object1">���肵�����I�u�W�F�N�g(OBJ)</param>
	/// <param name="object2">���肵�����I�u�W�F�N�g(FBX)</param>
	/// <param name="r1">OBJ�I�u�W�F�N�g�̔��a</param>
	/// <param name="r2">FBX�I�u�W�F�N�g�̔��a</param>
	/// <returns>��������</returns>
	bool FBXtoOBJSphereCollision(Object3d* object1, FBXObject3d* object2, float r1 = -1, float r2 = -1);

	/// <summary>
	/// ���Ƌ��̓����蔻��(FBX���m)
	/// </summary>
	/// <param name="object1">���肵�����I�u�W�F�N�g1</param>
	/// <param name="object2">���肵�����I�u�W�F�N�g2</param>
	/// <param name="r1">�I�u�W�F�N�g1�̔��a</param>
	/// <param name="r2">�I�u�W�F�N�g2�̔��a</param>
	/// <returns></returns>
	bool FBXSphereCollision(FBXObject3d* object1, FBXObject3d* object2, float r1 = -1, float r2 = -1);

private: //�����o�ϐ�
	Vector3 object1Pos = { 0, 0, 0 };
	Vector3 object2Pos = { 0, 0, 0 };

	Vector3 object1Scale = { 0, 0, 0 };
	Vector3 object2Scale = { 0, 0, 0 };

	float objectPosTotal = 0;
	float objectScaleTotal = 0;
};

