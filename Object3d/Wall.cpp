#include "Wall.h"

void Wall::Initialize(Model* Stage, bool flag)
{
	if (flag == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			Wall1[i] = Object3d::Create(Stage);
			Wall1[i]->SetScale(setSize);
			Wall1[i]->SetPosition(WallPos1[i]);
			ReWallPos1[i] = WallPos1[i];
		
			Wall1[i]->Update();
		
		}
	}
	if (flag == 1)
	{
		for (int i = 0; i < 2; i++)
		{
			Wall1[i]->SetPosition(ReWallPos1[i]);
			
			Wall1[i]->Update();
		

		}
	}
}

void Wall::Update(float posy)
{
	playerdistance1 = pow(WallPos1[0].y - posy, 2);
	
	playerdistance1 = sqrtf(playerdistance1);
	


	if (playerdistance1 > 800)
	{
		for (int i = 0; i < 2; i++)
		{
			WallPos1[i].y = posy - 800;
			Wall1[i]->SetPosition(WallPos1[i]);
			Wall1[i]->Update();
		}

	}
	
}

void Wall::Draw()
{
	for (int i = 0; i < 2; i++)
	{
		Wall1[i]->Draw();
	}
}
