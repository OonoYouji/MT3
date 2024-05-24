#include "Collision.h"

#include <algorithm>

#include "Vector3.h"
#include "MyMath.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"

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



bool IsCollision(const Line& line, const Triangle& triangle) {

	Vec3f v01 = triangle.vertices[1] - triangle.vertices[0];
	Vec3f v12 = triangle.vertices[2] - triangle.vertices[1];
	Vec3f v20 = triangle.vertices[0] - triangle.vertices[2];

	Vec3f normal = Cross(v01, v12);
	float distance = Dot(triangle.origin, normal);

	float dot = Dot(normal, line.diff);
	if(dot == 0.0f) { return false; }
	float t = (distance - Dot(normal, line.origin)) / dot;
	Vec3f planePoint = line.origin + (line.diff * t);

	Vec3f cross01 = Cross(v01, planePoint - triangle.vertices[1]);
	Vec3f cross12 = Cross(v12, planePoint - triangle.vertices[2]);
	Vec3f cross20 = Cross(v20, planePoint - triangle.vertices[0]);

	if(Dot(cross01, normal) >= 0.0f
	   && Dot(cross12, normal) >= 0.0f
	   && Dot(cross20, normal) >= 0.0f) {
		return true;
	}

	return false;
}

bool IsCollision(const Ray& ray, const Triangle& triangle) {

	Vec3f v01 = triangle.vertices[1] - triangle.vertices[0];
	Vec3f v12 = triangle.vertices[2] - triangle.vertices[1];
	Vec3f v20 = triangle.vertices[0] - triangle.vertices[2];

	Vec3f normal = Cross(v01, v12);
	float distance = Dot(triangle.origin, normal);

	float dot = Dot(normal, ray.diff);
	if(dot == 0.0f) { return false; }
	float t = (distance - Dot(normal, ray.origin)) / dot;
	if(t < 0.0f) { return false; }

	Vec3f planePoint = ray.origin + (ray.diff * t);

	Vec3f cross01 = Cross(v01, planePoint - triangle.vertices[1]);
	Vec3f cross12 = Cross(v12, planePoint - triangle.vertices[2]);
	Vec3f cross20 = Cross(v20, planePoint - triangle.vertices[0]);

	if(Dot(cross01, normal) >= 0.0f
	   && Dot(cross12, normal) >= 0.0f
	   && Dot(cross20, normal) >= 0.0f) {
		return true;
	}

	return false;
}

bool IsCollision(const Segment& segment, const Triangle& triangle) {

	Vec3f v01 = triangle.vertices[1] - triangle.vertices[0];
	Vec3f v12 = triangle.vertices[2] - triangle.vertices[1];
	Vec3f v20 = triangle.vertices[0] - triangle.vertices[2];

	Vec3f normal = Cross(v01, v12);
	float distance = Dot(triangle.origin, normal);

	float dot = Dot(normal, segment.diff);
	if(dot == 0.0f) { return false; }
	float t = (distance - Dot(normal, segment.origin)) / dot;
	if(t < 0.0f || t > 1.0f) { return false; }

	Vec3f planePoint = segment.origin + (segment.diff * t);

	Vec3f cross01 = Cross(v01, planePoint - triangle.vertices[1]);
	Vec3f cross12 = Cross(v12, planePoint - triangle.vertices[2]);
	Vec3f cross20 = Cross(v20, planePoint - triangle.vertices[0]);

	if(Dot(cross01, normal) >= 0.0f
	   && Dot(cross12, normal) >= 0.0f
	   && Dot(cross20, normal) >= 0.0f) {
		return true;
	}

	return false;
}

bool IsCollision(const AABB& a, const AABB& b) {
	if(!(a.min.x <= b.max.x && a.max.x >= b.min.x)) { return false; }
	if(!(a.min.y <= b.max.y && a.max.y >= b.min.y)) { return false; }
	if(!(a.min.z <= b.max.z && a.max.z >= b.min.z)) { return false; }
	return true;
}

bool IsCollision(const AABB& aabb, const Sphere& sphere) {

	Vec3f closestPoint{
		{std::clamp(sphere.GetPosition().x, aabb.min.x, aabb.max.x)},
		{std::clamp(sphere.GetPosition().y, aabb.min.y, aabb.max.y)},
		{std::clamp(sphere.GetPosition().z, aabb.min.z, aabb.max.z)}
	};

	float distance = Length(closestPoint - sphere.GetPosition());
	if(distance <= sphere.GetRadius()) {
		return true;
	}

	return false;
}
