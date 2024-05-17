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

bool IsCollision(const Line& line, const Plane& plane) {
	float dot = Dot(plane.normal, line.diff);
	///- 垂直=平面なので、衝突していない
	if(dot == 0.0f) { return false; }
	return true;
}

bool IsCollision(const Ray& ray, const Plane& plane) {
	float dot = Dot(plane.normal, ray.diff);
	///- 垂直=平面なので、衝突していない
	if(dot == 0.0f) { return false; }
	float t = (plane.distance - Dot(plane.normal, ray.origin)) / dot;

	if(t >= 0.0f) { return true; }
	return false;
}

bool IsCollision(const Segment& segment, const Plane& plane) {

	float dot = Dot(plane.normal, segment.diff);
	///- 垂直=平面なので、衝突していない
	if(dot == 0.0f) { return false; }
	float t = (plane.distance - Dot(plane.normal, segment.origin)) / dot;

	if(t >= 0.0f && t <= 1.0f) { return true; }
	return false;
}
