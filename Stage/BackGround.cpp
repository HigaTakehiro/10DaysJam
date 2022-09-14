#include "BackGround.h"

void BackGround::Initialize(bool flag)
{
	if (flag == 0)
	{
		ModelBackGround = Model::CreateModel("BackGround");
		BackGround1 = Object3d::Create(ModelBackGround);
		BackGround1->SetPosition(posBackGround1);
		BackGround1->SetScale(BackGroundSize);
		BackGround2 = Object3d::Create(ModelBackGround);
		BackGround2->SetPosition(posBackGround2);
		BackGround2->SetScale(BackGroundSize);
		
	}
	if (flag == 1)
	{
		posBackGround1 = { 46,950,0 };
		posBackGround2 = { 46,160,0 };
		
		BackGround1->SetPosition(posBackGround1);
		BackGround2->SetPosition(posBackGround2);
		
		BackGround1->Update();
		BackGround2->Update();
		
	}
	
}

void BackGround::Update(float posy)
{
	playerdistance1 = pow(posBackGround1.y - posy, 2);
	playerdistance2 = pow(posBackGround2.y - posy, 2);
	
	playerdistance1 = sqrtf(playerdistance1);
	playerdistance2 = sqrtf(playerdistance2);
	
	/*playerdistance1 = posBackGround1.y - posy;
	playerdistance2 = posBackGround1.y - posy;
	playerdistance3 = posBackGround1.y - posy;*/
	if (playerdistance1 > 800)
	{
		posBackGround1.y = posy - 800;
		BackGround1->SetPosition(posBackGround1);

	}
	if (playerdistance2 > 800)
	{
		posBackGround2.y = posy - 800;
		BackGround2->SetPosition(posBackGround2);

	}
	
	BackGround1->Update();
	BackGround2->Update();
	

}

void BackGround::Draw()
{
	BackGround1->Draw();
	BackGround2->Draw();
	//BackGround3->Draw();
}
