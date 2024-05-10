#include "Collision.h"

#include "Sphere.h"
#include "Plane.h"

#include "Vector3.h"
#include "MyMath.h"

bool IsCollision(const Sphere& s1, const Sphere& s2) {
	Vec3f distance = s2.GetPosition() - s1.GetPosition();
	float length = Length(distance);

	///- 二点間の距離が二つの球の半径より小さければtrue
	if(length < s1.GetRadius() + s2.GetRadius()) {
		return true;
	}

	return false;
}

bool IsCollision(const Sphere& sphere, const Plane& plane) {

	float scaler = Dot(sphere.GetPosition(), plane.normal) - plane.distance;
	Vec3f planePoint = sphere.GetPosition() - (plane.normal * scaler);

	float length = Length(sphere.GetPosition() - planePoint);
	if(length < sphere.GetRadius()) {
		return true;
	}

	return false;
}
