#include "Collision.h"

Collision* Collision::GetIns()
{
	static Collision instance;
	return &instance;
}

bool Collision::OBJSphereCollision(Object3d* object1, Object3d* object2, float r1, float r2) {
	object1Pos = object1->GetMatWorld().r[3];
	object2Pos = object2->GetMatWorld().r[3];

	if (r1 == -1 && r2 == -1) {
		object1Scale = object1->GetScale();
		object2Scale = object2->GetScale();
	}
	else {
		object1Scale = { r1,r1,r1 };
		object2Scale = { r2 ,r2,r2 };
	}	
	
	objectPosTotal = pow((object2Pos.x - object1Pos.x), 2) + pow((object2Pos.y - object1Pos.y), 2) + pow((object2Pos.z - object1Pos.z), 2);
	objectScaleTotal = (object1Scale.x + object2Scale.x) * (object1Scale.x + object2Scale.x);

	if (!(objectPosTotal <= objectScaleTotal)) return false;

	return true;
}

bool Collision::FBXtoOBJSphereCollision(Object3d* object1, FBXObject3d* object2, float r1, float r2) {
	object1Pos = object1->GetMatWorld().r[3];
	object2Pos = object2->GetMatWorld().r[3];

	if (r1 == -1 && r2 == -1) {
		object1Scale = object1->GetScale();
		object2Scale = object2->GetScale();
	}
	else {
		object1Scale = { r1,r1,r1 };
		object2Scale = { r2 ,r2,r2 };
	}

	objectPosTotal = pow((object2Pos.x - object1Pos.x), 2) + pow((object2Pos.y - object1Pos.y), 2) + pow((object2Pos.z - object1Pos.z), 2);
	objectScaleTotal = (object1Scale.x + object2Scale.x) * (object1Scale.x + object2Scale.x);

	if (!(objectPosTotal <= objectScaleTotal)) return false;

	return true;
}

bool Collision::FBXSphereCollision(FBXObject3d* object1, FBXObject3d* object2, float r1, float r2) {
	object1Pos = object1->GetMatWorld().r[3];
	object2Pos = object2->GetMatWorld().r[3];

	if (r1 == -1 && r2 == -1) {
		object1Scale = object1->GetScale();
		object2Scale = object2->GetScale();
	}
	else {
		object1Scale = { r1,r1,r1 };
		object2Scale = { r2 ,r2,r2 };
	}

	objectPosTotal = pow((object2Pos.x - object1Pos.x), 2) + pow((object2Pos.y - object1Pos.y), 2) + pow((object2Pos.z - object1Pos.z), 2);
	objectScaleTotal = (object1Scale.x + object2Scale.x) * (object1Scale.x + object2Scale.x);

	if (!(objectPosTotal <= objectScaleTotal)) return false;

	return true;
}

bool Collision::BoxCollision(XMFLOAT3 object1, XMFLOAT3 radius1, XMFLOAT3 object2, XMFLOAT3 radius2) {
	float disX1 = object1.x + radius1.x;
	float disX2 = object2.x - radius2.x;
	float disX3 = object1.x - radius1.x;
	float disX4 = object2.x + radius2.x;
	float disY1 = object1.y + radius1.y;
	float disY2 = object2.y - radius2.y;
	float disY3 = object1.y - radius1.y;
	float disY4 = object2.y + radius2.y;
	float disZ1 = object1.z + radius1.z;
	float disZ2 = object2.z - radius2.z;
	float disZ3 = object1.z - radius1.z;
	float disZ4 = object2.z + radius2.z;

	//x‚Æy‚Í‚»‚ê‚¼‚ê’†SÀ•W‚Æ‚µ‚ÄŒvŽZ‚·‚é
	return disX1 > disX2 && disX4 > disX3 && disY1 > disY2 && disY4 > disY3 && disZ1 > disZ2 && disZ4 > disZ3;
}