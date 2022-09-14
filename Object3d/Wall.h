#pragma once
#include "Object3d.h"
#include "Model.h"
class Wall
{

private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT3 = DirectX::XMFLOAT3;
public:
	void Initialize(Model* Stage, bool flag);
	void Update(float posy);
	void Draw();

private:
	Object3d* Wall1[2] = { nullptr };
	
	XMFLOAT3 setSize = { 50,5000,50 };
	XMFLOAT3 WallPos1[2] = { {-150,0,0},{230,950,0} };

	XMFLOAT3 ReWallPos1[2] = {};
	
	float playerdistance1;
	
};

