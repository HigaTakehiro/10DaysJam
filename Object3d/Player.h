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

public: //�����o�֐�
	/// <summary>
	/// ����������
	/// </summary>
	void Initialize(Camera* camera);

	/// <summary>
	/// �X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �I������
	/// </summary>
	void Finalize();

	/// <summary>
	/// �X�v���C�g�`�揈��
	/// </summary>
	void SpriteDraw();

	/// <summary>
	/// 3D�I�u�W�F�N�g�`�揈��
	/// </summary>
	void ObjectDraw();

	/// <summary>
	/// �ʒu�擾
	/// </summary>
	/// <returns>�ʒu</returns>
	const XMFLOAT3 GetPlayerPos() { return playerLPos; }

	/// <summary>
	/// �����擾
	/// </summary>
	/// <returns>����</returns>
	const XMFLOAT2 GetPlayerRot() { return aimPos; }

	/// <summary>
	/// �v���C���[�I�u�W�F�N�g�̎擾
	/// </summary>
	/// <returns>�v���C���[�I�u�W�F�N�g</returns>
	Object3d* GetPlayerObject() { return player; }

	/// <summary>
	/// �e�̃��X�g�擾
	/// </summary>
	/// <returns>�e�̃��X�g</returns>
	std::list<std::unique_ptr<PlayerBullet>>& GetBullet() { return bullets; }

	/// <summary>
	/// ���Z�b�g����
	/// </summary>
	void Reset();

	/// <summary>
	/// �G�𓥂�ŃW�����v
	/// </summary>
	void StampJump();

	/// <summary>
	/// �������x�擾
	/// </summary>
	float GetFallSpeed() { return fallSpeed; }

	/// <summary>
	/// �����u�[�X�g
	/// </summary>
	void DecelerationBoost();

	/// <summary>
	/// �u�[�X�g�e�ʎ擾
	/// </summary>
	float GetBoostCapacity() { return boostCapacity; }

	void SetPlayerPos(XMFLOAT3 pos) { playerLPos = pos; }

	void Recovery() { boostCapacity += 4; if (boostCapacity >= maxBoostCapacity) { boostCapacity = maxBoostCapacity; } };

private: //�����o�֐�
	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();

	/// <summary>
	/// �ʏ�U������
	/// </summary>
	void Shot();

	/// <summary>
	/// 3d���e�B�N���X�V����
	/// </summary>
	void AimUpdate();

	/// <summary>
	/// ���R�����X�V����
	/// </summary>
	void FreeFall();

	/// <summary>
	/// �W�����v�X�V����
	/// </summary>
	void JumpUpdate();

public:
	float num = 0;

private: //�����o�ϐ�
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
	//�Q�[���V�[���p�ϐ�
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

