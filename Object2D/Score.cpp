#include "Score.h"

void Score::Initialize()
{
	Sprite::LoadTexture(60, L"Resources/Numbers/No0.png");
	Sprite::LoadTexture(61, L"Resources/Numbers/No1.png");
	Sprite::LoadTexture(62, L"Resources/Numbers/No2.png");
	Sprite::LoadTexture(63, L"Resources/Numbers/No3.png");
	Sprite::LoadTexture(64, L"Resources/Numbers/No4.png");
	Sprite::LoadTexture(65, L"Resources/Numbers/No5.png");
	Sprite::LoadTexture(66, L"Resources/Numbers/No6.png");
	Sprite::LoadTexture(67, L"Resources/Numbers/No7.png");
	Sprite::LoadTexture(68, L"Resources/Numbers/No8.png");
	Sprite::LoadTexture(69, L"Resources/Numbers/No9.png");
	for (int i = 0; i < 10; i++)
	{
		scoredis[i] = { pos.x - (32.0f * i),pos.y };
	}
	for (int i = 0; i < 10; i++)
	{
		Score1[i] = Sprite::Create(60 + i, { 0, 0 });
		Score1[i]->SetPosition(scoredis[0]);
		Score1[i]->SetSize(scoreSize);
		Score2[i] = Sprite::Create(60 + i, { 0, 0 });
		Score2[i]->SetPosition(scoredis[1]);
		Score2[i]->SetSize(scoreSize);
		Score3[i] = Sprite::Create(60 + i, { 0, 0 });
		Score3[i]->SetPosition(scoredis[2]);
		Score3[i]->SetSize(scoreSize);
		Score4[i] = Sprite::Create(60 + i, { 0, 0 });
		Score4[i]->SetPosition(scoredis[3]);
		Score4[i]->SetSize(scoreSize);
		Score5[i] = Sprite::Create(60 + i, { 0, 0 });
		Score5[i]->SetPosition(scoredis[4]);
		Score5[i]->SetSize(scoreSize);
		Score6[i] = Sprite::Create(60 + i, { 0, 0 });
		Score6[i]->SetPosition(scoredis[5]);
		Score6[i]->SetSize(scoreSize);
		Score7[i] = Sprite::Create(60 + i, { 0, 0 });
		Score7[i]->SetPosition(scoredis[6]);
		Score7[i]->SetSize(scoreSize);
		Score8[i] = Sprite::Create(60 + i, { 0, 0 });
		Score8[i]->SetPosition(scoredis[7]);
		Score8[i]->SetSize(scoreSize);
		Score9[i] = Sprite::Create(60 + i, { 0, 0 });
		Score9[i]->SetPosition(scoredis[8]);
		Score9[i]->SetSize(scoreSize);
		Score10[i] = Sprite::Create(60 + i, { 0, 0 });
		Score10[i]->SetPosition(scoredis[9]);
		Score10[i]->SetSize(scoreSize);

	}

	SetPosition({ 200.0f, 100.0f });
}

void Score::Update()
{
	scoreTime += 0.005f;
	if (scoreTime > 1.0f)
	{
		scoreTime = 0.0f;
		score++;

	}

	if (score >= 100000 && score < 1000000)
	{
		score6 = score / 100000;
		score5 = (score - (score6 * 100000)) / 10000;
		score4 = (score - (score6 * 100000) - (score5 * 10000)) / 1000;
		score3 = (score - (score6 * 100000) - (score5 * 10000) - (score4 * 1000)) / 100;
		score2 = (score - (score6 * 100000) - (score5 * 10000) - (score4 * 1000) - (score3 * 100)) / 10;
		score1 = (score - (score6 * 100000) - (score5 * 10000) - (score4 * 1000) - (score3 * 100) - (score2 * 10));
	}
	if (score >= 10000 && score < 100000)
	{
		score5 = score / 10000;
		score4 = (score - (score5 * 10000)) / 1000;
		score3 = (score - (score5 * 10000) - (score4 * 1000)) / 100;
		score2 = (score - (score5 * 10000) - (score4 * 1000) - (score3 * 100)) / 10;
		score1 = (score - (score5 * 10000) - (score4 * 1000) - (score3 * 100) - (score2 * 10));
	}
	if (score >= 1000 && score < 10000)
	{
		score4 = score / 1000;
		score3 = (score - (score4 * 1000)) / 100;
		score2 = (score - (score4 * 1000) - (score3 * 100)) / 10;
		score1 = (score - (score4 * 1000) - (score3 * 100) - (score2 * 10));
	}
	if (score >= 100 && score < 1000)
	{
		score3 = score / 100;
		score2 = (score - (score3 * 100)) / 10;
		score1 = (score - (score3 * 100) - (score2 * 10));
	}
	if (score >= 10 && score < 100)
	{
		score2 = score / 10;
		score1 = (score - (score2 * 10));
	}
	if (score < 10)
	{

		score1 = score;
	}
}

void Score::Draw()
{
	for (int i = 0; i < 10; i++)
	{
		if (score1 == i)Score1[i]->Draw();
		if (score2 == i)Score2[i]->Draw();
		if (score3 == i)Score3[i]->Draw();
		if (score4 == i)Score4[i]->Draw();
		if (score5 == i)Score5[i]->Draw();
		if (score6 == i)Score6[i]->Draw();
		/*if (score7 == i)Score7[i]->Draw();
		if (score8 == i)Score8[i]->Draw();
		if (score9 == i)Score9[i]->Draw();*/

	}
}

void Score::ReSet()
{
	scoreTime = 0.0f;
	score = 0;
	SetPosition({ 200, 100 });
}

void Score::SetPosition(XMFLOAT2 pos)
{
	this->pos = pos;

	for (int i = 0; i < 10; i++)
	{
		scoredis[i] = { pos.x - (32.0f * i),pos.y };
	}
	for (int i = 0; i < 10; i++)
	{
		Score1[i]->SetPosition(scoredis[0]);
		Score2[i]->SetPosition(scoredis[1]);
		Score3[i]->SetPosition(scoredis[2]);
		Score4[i]->SetPosition(scoredis[3]);
		Score5[i]->SetPosition(scoredis[4]);
		Score6[i]->SetPosition(scoredis[5]);
		Score7[i]->SetPosition(scoredis[6]);
		Score8[i]->SetPosition(scoredis[7]);
		Score9[i]->SetPosition(scoredis[8]);
		Score10[i]->SetPosition(scoredis[9]);
	}
}
