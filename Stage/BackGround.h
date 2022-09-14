#pragma once
#include "Object3d.h"
#include "Model.h"

class BackGround
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT3 = DirectX::XMFLOAT3;
public:
	void Initialize(bool flag);
	void Update(float posy);
	void Draw();

	float GetPos1() { return posBackGround1.y; };
	float GetPos2() { return posBackGround2.y; };
	
private:
	Model* ModelBackGround = nullptr;
	Object3d* BackGround1 = nullptr;
	Object3d* BackGround2 = nullptr;
	XMFLOAT3 BackGroundSize = { 4,4.12f,4 };

	XMFLOAT3 posBackGround1 = { 46,940,0 };
	XMFLOAT3 posBackGround2 = { 46,160,0 };
	
	float playerdistance1;
	float playerdistance2;

};

