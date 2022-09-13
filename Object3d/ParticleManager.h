#pragma once

#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>
#include<forward_list>
/// <summary>
/// 3D�I�u�W�F�N�g
/// </summary>

const DirectX::XMFLOAT3 operator+(
	const DirectX::XMFLOAT3& lhs, const DirectX::XMFLOAT3& rhs);

class ParticleManager
{
public:




private: // �G�C���A�X
	// Microsoft::WRL::���ȗ�
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;


	// DirectX::���ȗ�
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

public: // �T�u�N���X
	// ���_�f�[�^�\����
	//struct VertexPosNormalUv
	//{
	//	XMFLOAT3 pos; // xyz���W
	//	XMFLOAT3 normal; // �@���x�N�g��
	//	XMFLOAT2 uv;  // uv���W
	//};
	struct VertexPos
	{
		XMFLOAT3 pos;
		float scale;
	};

	// �萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		//XMFLOAT4 color;	// �F (RGBA)
		XMMATRIX mat;	// �R�c�ϊ��s��
		XMMATRIX matBillboard;//�r���{�[�h�s��
	};

	struct Particle
	{
		using XMFLOAT3 = DirectX::XMFLOAT3;

		XMFLOAT3 position = {};

		XMFLOAT3 velocity = {};

		XMFLOAT3 accel = {};

		int frame = 0;

		int num_frame = 0;

		float scale = 1.0f;

		float s_scale = 1.0f;

		float e_scale = 1.0f;


	};

	std::forward_list<Particle> particles;
private: // �萔

	static const int division = 50;					// ������
	static const float radius;				// ��ʂ̔��a
	static const float prizmHeight;			// ���̍���
	static const int planeCount = division * 2 + division * 2;		// �ʂ̐�

	static const int vertexCount = 1048576 * 20;		// ���_��
	static const int indexCount = 3 * 2;



public: // �ÓI�����o�֐�
	/// <summary>
	/// �ÓI������
	/// </summary>
	/// <param name="device">�f�o�C�X</param>
	/// <param name="window_width">��ʕ�</param>
	/// <param name="window_height">��ʍ���</param>
	/// <returns>����</returns>
	static bool StaticInitialize(ID3D12Device* device, int window_width, int window_height);

	/// <summary>
	/// �`��O����
	/// </summary>
	/// <param name="cmdList">�`��R�}���h���X�g</param>
	static void PreDraw(ID3D12GraphicsCommandList* cmdList);

	/// <summary>
	/// �`��㏈��
	/// </summary>
	static void PostDraw();

	/// <summary>
	/// 3D�I�u�W�F�N�g����
	/// </summary>
	/// <returns></returns>
	static ParticleManager* Create(ID3D12Device* device);

	/// <summary>
	/// ���_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	static const XMFLOAT3& GetEye() { return eye; }

	/// <summary>
	/// ���_���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	static void SetEye(XMFLOAT3 eye);

	/// <summary>
	/// �����_���W�̎擾
	/// </summary>
	/// <returns>���W</returns>
	static const XMFLOAT3& GetTarget() { return target; }

	/// <summary>
	/// �����_���W�̐ݒ�
	/// </summary>
	/// <param name="position">���W</param>
	static void SetTarget(XMFLOAT3 target);

	/// <summary>
	/// �x�N�g���ɂ��ړ�
	/// </summary>
	/// <param name="move">�ړ���</param>
	//static void CameraMoveVector(XMFLOAT3 move);
	static void CameraMoveEyeVector(XMFLOAT3 move);

	void SetDev(ID3D12Device* device) { this->device = device; }

private: // �ÓI�����o�ϐ�
	// �f�o�C�X
	static ID3D12Device* device;
	// �f�X�N���v�^�T�C�Y
	static UINT descriptorHandleIncrementSize;
	// �R�}���h���X�g
	static ID3D12GraphicsCommandList* cmdList;
	// ���[�g�V�O�l�`��
	static ComPtr<ID3D12RootSignature> rootsignature;
	// �p�C�v���C���X�e�[�g�I�u�W�F�N�g
	static ComPtr<ID3D12PipelineState> pipelinestate;
	// �f�X�N���v�^�q�[�v
	static ComPtr<ID3D12DescriptorHeap> descHeap;
	// ���_�o�b�t�@
	static ComPtr<ID3D12Resource> vertBuff;
	// �C���f�b�N�X�o�b�t�@
	static ComPtr<ID3D12Resource> indexBuff;
	// �e�N�X�`���o�b�t�@
	static ComPtr<ID3D12Resource> texbuff;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	static CD3DX12_CPU_DESCRIPTOR_HANDLE cpuDescHandleSRV;
	// �V�F�[�_���\�[�X�r���[�̃n���h��(CPU)
	static CD3DX12_GPU_DESCRIPTOR_HANDLE gpuDescHandleSRV;
	// �r���[�s��
	static XMMATRIX matView;
	// �ˉe�s��
	static XMMATRIX matProjection;
	// ���_���W
	static XMFLOAT3 eye;
	// �����_���W
	static XMFLOAT3 target;
	// ������x�N�g��
	static XMFLOAT3 up;
	// ���_�o�b�t�@�r���[
	static D3D12_VERTEX_BUFFER_VIEW vbView;
	// �C���f�b�N�X�o�b�t�@�r���[
	static D3D12_INDEX_BUFFER_VIEW ibView;
	// ���_�f�[�^�z��
	//static VertexPosNormalUv vertices[vertexCount];
	static VertexPos vertices[vertexCount];
	// ���_�C���f�b�N�X�z��
	static unsigned short indices[indexCount];

	//�r���{�[�h�s��
	static XMMATRIX matBillboard;

	//Y������r���{�[�h�s��
	static XMMATRIX matBillboardY;





private:// �ÓI�����o�֐�
	/// <summary>
	/// �f�X�N���v�^�q�[�v�̏�����
	/// </summary>
	/// <returns></returns>
	static bool InitializeDescriptorHeap();

	/// <summary>
	/// �J����������
	/// </summary>
	/// <param name="window_width">��ʉ���</param>
	/// <param name="window_height">��ʏc��</param>
	static void InitializeCamera(int window_width, int window_height);

	/// <summary>
	/// �O���t�B�b�N�p�C�v���C������
	/// </summary>
	/// <returns>����</returns>
	static bool InitializeGraphicsPipeline();

	/// <summary>
	/// �e�N�X�`���ǂݍ���
	/// </summary>
	/// <returns>����</returns>
	static bool LoadTexture();

	/// <summary>
	/// ���f���쐬
	/// </summary>
	static void CreateModel();

	/// <summary>
	/// �r���[�s����X�V
	/// </summary>
	static void UpdateViewMatrix();



public: // �����o�֐�
	bool Initialize(ID3D12Device* device);
	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw();

	void PBustr(int angle, XMFLOAT3 pos);

	void PArts(int angle, XMFLOAT3 pos);

	void PQuik(int angle, XMFLOAT3 pos);

	void All(int angle, XMFLOAT3 pos);

	void Add(int life, XMFLOAT3 position, XMFLOAT3 velocity, XMFLOAT3 accel,
		float start_scale, float end_scale);

private: // �����o�ϐ�
	ComPtr<ID3D12Resource> constBuff; // �萔�o�b�t�@

	// ���[�J���X�P�[��
	XMFLOAT3 scale = { 1,1,1 };


	int ccc = 0;

	static const float PI;
	XMFLOAT3 pos = { 0,0,0 };
	int PCount = 180;
	int angle = 0;
	static int radian[360];
	static int count;
};
