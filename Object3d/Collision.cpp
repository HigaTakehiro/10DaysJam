#include "Collision.h"

Collision* Collision::GetIns()
{
	static Collision instance;
	return &instance;
}

bool Collision::SphereCollision(Object3d* object1, Object3d* object2) {
	object1Pos = object1->GetMatWorld().r[3];
	object1Scale = object1->GetScale();

	object2Pos = object2->GetMatWorld().r[3];
	object2Scale = object2->GetScale();
	
	objectPosTotal = pow((object2Pos.x - object1Pos.x), 2) + pow((object2Pos.y - object1Pos.y), 2) + pow((object2Pos.z - object1Pos.z), 2);
	objectScaleTotal = (object1Scale.x + object2Scale.x) * (object1Scale.x + object2Scale.x);

	if (!(objectPosTotal <= objectScaleTotal)) return false;

	return true;
}