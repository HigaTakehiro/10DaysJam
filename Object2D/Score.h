#pragma once
#include"Sprite.h"
class Score
{
private:
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
public:

	void Initialize();
	void Update();
	void Draw();

private:
	Sprite* Score1[10];
	Sprite* Score2[10];
	Sprite* Score3[10];
	Sprite* Score4[10];
	Sprite* Score5[10];
	Sprite* Score6[10];
	Sprite* Score7[10];
	Sprite* Score8[10];
	Sprite* Score9[10];
	Sprite* Score10[10];
	int score = 0;
	int score1 = 0;
	int score2 = 0;
	int score3 = 0;
	int score4 = 0;
	int score5 = 0;
	int score6 = 0;
	int score7 = 0;
	int score8 = 0;
	int score9 = 0;
	int score10 = 0;
	float scoreTime = 0.0f;
	XMFLOAT2 scoreSize = { 32.0f,64.0f };
	XMFLOAT2 scoredis[10] = {};
};

