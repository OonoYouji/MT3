#pragma once

#include <Vector3.h>


struct OBB {

	Vec3f center;			//- 中心
	Vec3f orientatinos[3];	//- 座標軸
	Vec3f size;				//- 大きさ

};