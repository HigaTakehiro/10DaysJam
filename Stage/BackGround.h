#pragma once
#include "Object3d.h"
#include "Model.h"
#include"Player.h"
class BackGround
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT3 = DirectX::XMFLOAT3;
public:
	void Initialize();
	void Update(float posy);
	void Draw();
private:
	Model* ModelBackGround = nullptr;
	Object3d* BackGround1 = nullptr;
	Object3d* BackGround2 = nullptr;
	Object3d* BackGround3 = nullptr;
	XMFLOAT3 BackGroundSize = { 4,4,4 };

	XMFLOAT3 posBackGround1 = { 46,0,0 };
	XMFLOAT3 posBackGround2 = { 46,+800,0 };
	XMFLOAT3 posBackGround3 = { 46,-800,0 };
	float playerdistance1;
	float playerdistance2;
	float playerdistance3;
};

