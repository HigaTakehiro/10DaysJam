#pragma once
#include "Object3d.h"
#include "Model.h"
#include "Vector3.h"
#include "SafeDelete.h"
#include "DirectXCommon.h"

class Stage
{

public: //�����o�֐�

	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const std::string& modelName, Vector3 pos, Vector3 rot, Vector3 scale);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �`�揈��
	/// </summary>
	void Draw();

	/// <summary>
	/// �Փˎ��R�[���o�b�N�֐�
	/// </summary>
	void OnCollision();


	/// <summary>
	/// �X�e�[�W�I�u�W�F�N�g�擾
	/// </summary>
	/// <returns>�X�e�[�W�I�u�W�F�N�g</returns>
	Object3d* GetStageObj() { return stage; }

	bool IsDead() { return isDead; }

private: //�����o�ϐ�

	Model* stageModel;
	Object3d* stage;
	Vector3 pos;
	bool isDead;
	int time = 0;
};

