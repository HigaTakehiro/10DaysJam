#include "EnemyManager.h"

void EnemyManager::Initialize(Player* player, Model* enemyModel)
{
	this->player = player;
	this->enemyModel = enemyModel;
	playerOldPos = player->GetPlayerPos();
}

void EnemyManager::Update()
{
	enemies.remove_if([](std::unique_ptr<Enemy>& stage) {return stage->IsDead(); });

	//�O��n�ʂ𐶐��������̃v���C���[�̈ʒu���猻�݂̃v���C���[�̈ʒu�������Čv�Z����Y���̒l�i��Βl�ł̌v�Z�j����苗�����ɂȂ����琶��
	float num1 = fabs(playerOldPos.y);
	float num2 = fabs(player->GetPlayerPos().y);
	float num3 = num1 - num2;
	num3 = fabs(num3);
	if (num3 > 300/*&& stageNum <10*/)
	{
		stageNum++;
		int type = rand() % 3 + 3;
		float height = player->GetPlayerPos().y - 200 + 70;
		height -= 100;
		XMFLOAT3 enemypos = { 0,0,0 };
		XMFLOAT3 enemypos2 = { 0,0,0 };
		switch (type) {
		case 0:
			enemypos = { -50.0f,height ,-50 };
			break;
		case 1:
			enemypos = { 40,height ,-50 };
			break;
		case 2:
			enemypos = { 120,height ,-50 };
			break;
		case 3:
			enemypos = { -50,height - 20 ,-50 };
			enemypos2 = { 40,height - 20 ,-50 };
			break;
		case 4:
			enemypos = { 40,height - 20,-50 };
			enemypos2 = { 120,height - 20,-50 };
			break;
		case 5:
			enemypos = { -50,height - 20,-50 };
			enemypos2 = { 120,height - 20,-50 };
			break;
		case 6:
			//stageObj[stageClip]->SetPosition({ -50,height ,-50 });
			break;
		case 7:
			//�����łĂ��Ȃ��^�C�v
			//stageObj[stageClip]->SetPosition({ -50,height ,-50 });
			break;
		}
		//�n�ʂ��Q�[���V�[���ɒǉ�
		std::unique_ptr<Enemy> newEnemy = std::make_unique<Enemy>();
		newEnemy->Initialize(enemyModel, enemypos, { 0,0,0 }, { 10,10,50 });
		enemies.push_back(std::move(newEnemy));
		//if (type == 3 || type == 4 || type == 5) {
		//	std::unique_ptr<Enemy> newEnemy2 = std::make_unique<Enemy>();
		//	newEnemy2->Initialize(enemyModel, enemypos2, { 0,0,0 }, { 10,10,50 });
		//	enemies.push_back(std::move(newEnemy2));
		//}

		playerOldPos = player->GetPlayerPos();
	}


	//�X�e�[�W���v���C���[����w�肵���l����ɂ�����f�b�h�t���O�𗧂Ă�
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		num1 = fabs(enemy->GetEnemyObj()->GetPosition().y);
		num2 = fabs(player->GetPlayerPos().y);
		num3 = num1 - num2;
		num3 = fabs(num3);
		if (num3 > 400) {
			enemy->SetDead();
		}
	}
	//�X�e�[�W�̍X�V
	for (std::unique_ptr<Enemy>& stage : enemies) {
		stage->Update();
	}
}

void EnemyManager::Draw(DirectXCommon* dxCommon)
{
	for (std::unique_ptr<Enemy>& enemy : enemies) {
		enemy->Draw(dxCommon);
	}
}
