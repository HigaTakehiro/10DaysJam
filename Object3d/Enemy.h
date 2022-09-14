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

public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, FBXModel* fbxModel, Vector3 pos, Vector3 rot, Vector3 scale, int enemyType,Model* energyModel);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw(DirectXCommon* dxCommon);

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	void OnCollision();

	/// <summary>
	/// �G�̏�Ԃ��擾
	/// </summary>
	/// <returns>�G�̏��</returns>
	bool IsDead() const { return isDead; }

	void SetDead() { isDead = true; }

	/// <summary>
	/// �G�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>�G�I�u�W�F�N�g</returns>
	Object3d* GetEnemyObj() { return enemy; }

	FBXObject3d* GetEnemyFbx() { return fbxEnemy; }

	int GetEnemyType() { return enemyType; }

private: //�����o�ϐ�

	Model* enemyModel = nullptr;
	Object3d* enemy = nullptr;
	FBXModel* fbxEnemyModel = nullptr;
	FBXObject3d* fbxEnemy = nullptr;
	Vector3 pos;
	bool isDead;
	float speed = 1;;

	int direction = 0;
	int enemyType = 0;
	Model* energyModel = nullptr;
	Object3d* energyObj = nullptr;
};

