#pragma once 

#include "Vector3.h"
#include <string>

class Camera;

/// <summary>
/// 無限等遠平面
/// </summary>
struct Plane {

	Vec3f normal;
	float distance;

	void DebugDraw(const std::string& windowName);
	void Draw(const Camera* camera);

};