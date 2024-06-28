#include "Collision.h"
#define NOMINMAX

#include <algorithm>
#include <vector>

#include <ImGuiManager.h>

#include "Vector3.h"
#include "MyMath.h"
#include "Sphere.h"
#include "Plane.h"
#include "Triangle.h"
#include "OBB.h"



bool IsCollided(const Sphere& s1, const Sphere& s2) {
	Vec3f distance = s2.center - s1.center;
	float length = Length(distance);

	///- 二点間の距離が二つの球の半径より小さければtrue
	if(length < s1.radius + s2.radius) {
		return true;
	}

	return false;
}

bool IsCollided(const Sphere& sphere, const Plane& plane) {

	float scaler = Dot(sphere.center, plane.normal) - plane.distance;
	Vec3f planePoint = sphere.center - (plane.normal * scaler);

	float length = Length(sphere.center - planePoint);
	if(length < sphere.radius) {
		return true;
	}

	return false;
}

bool IsCollided(const Line& line, const Plane& plane) {
	float dot = Dot(plane.normal, line.diff);
	///- 垂直=平面なので、衝突していない
	if(dot == 0.0f) { return false; }
	return true;
}

bool IsCollided(const Ray& ray, const Plane& plane) {
	float dot = Dot(plane.normal, ray.diff);
	///- 垂直=平面なので、衝突していない
	if(dot == 0.0f) { return false; }
	float t = (plane.distance - Dot(plane.normal, ray.origin)) / dot;

	if(t >= 0.0f) { return true; }
	return false;
}

bool IsCollided(const Segment& segment, const Plane& plane) {

	float dot = Dot(plane.normal, segment.diff);
	///- 垂直=平面なので、衝突していない
	if(dot == 0.0f) { return false; }
	float t = (plane.distance - Dot(plane.normal, segment.origin)) / dot;

	if(t >= 0.0f && t <= 1.0f) { return true; }
	return false;
}



bool IsCollided(const Line& line, const Triangle& triangle) {

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

bool IsCollided(const Ray& ray, const Triangle& triangle) {

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

bool IsCollided(const Segment& segment, const Triangle& triangle) {

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

bool IsCollided(const AABB& a, const AABB& b) {
	if(!(a.min.x <= b.max.x && a.max.x >= b.min.x)) { return false; }
	if(!(a.min.y <= b.max.y && a.max.y >= b.min.y)) { return false; }
	if(!(a.min.z <= b.max.z && a.max.z >= b.min.z)) { return false; }
	return true;
}

bool IsCollided(const AABB& aabb, const Sphere& sphere) {

	Vec3f closestPoint{
		{std::clamp(sphere.center.x, aabb.min.x, aabb.max.x)},
		{std::clamp(sphere.center.y, aabb.min.y, aabb.max.y)},
		{std::clamp(sphere.center.z, aabb.min.z, aabb.max.z)}
	};

	float distance = Length(closestPoint - sphere.center);
	if(distance <= sphere.radius) {
		return true;
	}

	return false;
}

bool IsCollided(const AABB& aabb, const Line& line) {
	Vec3f min = (aabb.min - line.origin) / line.diff;
	Vec3f max = (aabb.max - line.origin) / line.diff;

	Vec3f nearPoint = {
		std::min(min.x, max.x),
		std::min(min.y, max.y),
		std::min(min.z, max.z)
	};

	Vec3f farPoint = {
		std::max(min.x, max.x),
		std::max(min.y, max.y),
		std::max(min.z, max.z)
	};

	float tmin = std::max({ nearPoint.x, nearPoint.y, nearPoint.z });
	float tmax = std::min({ farPoint.x, farPoint.y, farPoint.z });

	///- Lineには制限がない

	if(tmin <= tmax) {
		return true;
	}

	return false;
}

bool IsCollided(const AABB& aabb, const Ray& ray) {
	Vec3f min = (aabb.min - ray.origin) / ray.diff;
	Vec3f max = (aabb.max - ray.origin) / ray.diff;

	Vec3f nearPoint = {
		std::min(min.x, max.x),
		std::min(min.y, max.y),
		std::min(min.z, max.z)
	};

	Vec3f farPoint = {
		std::max(min.x, max.x),
		std::max(min.y, max.y),
		std::max(min.z, max.z)
	};

	float tmin = std::max({ nearPoint.x, nearPoint.y, nearPoint.z });
	float tmax = std::min({ farPoint.x, farPoint.y, farPoint.z });

	///- Ray用の制限
	if(tmax < 0.0f) {
		return false;
	}

	if(tmin <= tmax) {
		return true;
	}

	return false;
}

bool IsCollided(const AABB& aabb, const Segment& segment) {

	Vec3f min = (aabb.min - segment.origin) / segment.diff;
	Vec3f max = (aabb.max - segment.origin) / segment.diff;

	Vec3f nearPoint = {
		std::min(min.x, max.x),
		std::min(min.y, max.y),
		std::min(min.z, max.z)
	};

	Vec3f farPoint = {
		std::max(min.x, max.x),
		std::max(min.y, max.y),
		std::max(min.z, max.z)
	};

	float tmin = std::max({ nearPoint.x, nearPoint.y, nearPoint.z });
	float tmax = std::min({ farPoint.x, farPoint.y, farPoint.z });

	///- Segment用の制限
	if(1.0f < tmin || tmax < 0.0f) {
		return false;
	}

	if(tmin <= tmax) {
		return true;
	}

	return false;
}

bool IsCollided(const OBB& obb, const Sphere& sphere) {

	///- OBBの逆行列
	Matrix4x4 inverseObbWorldMatrix = Mat4::MakeInverse(obb.MakeWorldMatrix());

	///- Sphereの座標をOBBのLocal空間へ変換
	Vec3f obbLocalPosition = Mat4::Transform(sphere.center, inverseObbWorldMatrix);

	///- OBBのLocal空間内のAABB
	AABB aabbObbLocal = {
		.min = -obb.size,
		.max = obb.size
	};

	///- OBBのLocal空間内のSphere
	Sphere sphereObbLocal = {
		.rotate = sphere.rotate,
		.center = obbLocalPosition,
		.radius = sphere.radius,
	};

	///- Local空間に変換したAABBとSphere
	return IsCollided(aabbObbLocal, sphereObbLocal);
}


bool IsCollided(const OBB& obb, const Line& line) {

	///- OBBの逆行列
	Matrix4x4 inverseObbWorldMatrix = Mat4::MakeInverse(obb.MakeWorldMatrix());

	///- OBBのLocal空間に変換したAABB
	AABB aabbObbLocal = {
		.min = -obb.size,
		.max = obb.size
	};

	///- OBBのLocal空間に変換したLine
	Line lineObbLocal = {
		.origin = Mat4::Transform(line.origin, inverseObbWorldMatrix),
		.diff = Mat4::Transform(line.diff, inverseObbWorldMatrix)
	};

	///- OBBのLocal空間のAABBとLineで衝突判定を取る
	return IsCollided(aabbObbLocal, lineObbLocal);
}

bool IsCollided(const OBB& obb, const Ray& ray) {

	///- OBBの逆行列
	Matrix4x4 inverseObbWorldMatrix = Mat4::MakeInverse(obb.MakeWorldMatrix());

	///- OBBのLocal空間に変換したAABB
	AABB aabbObbLocal = {
		.min = -obb.size,
		.max = obb.size
	};

	///- OBBのLocal空間に変換したRay
	Ray rayObbLocal = {
		.origin = Mat4::Transform(ray.origin, inverseObbWorldMatrix),
		.diff = Mat4::Transform(ray.diff, inverseObbWorldMatrix)
	};

	///- OBBのLocal空間のAABBとRayで衝突判定を取る
	return IsCollided(aabbObbLocal, rayObbLocal);
}

bool IsCollided(const OBB& obb, const Segment& segment) {

	///- OBBの逆行列
	Matrix4x4 inverseObbWorldMatrix = Mat4::MakeInverse(obb.MakeWorldMatrix());

	///- OBBのLocal空間に変換したAABB
	AABB aabbObbLocal = {
		.min = -obb.size,
		.max = obb.size
	};

	///- OBBのLocal空間に変換したSegment
	Segment segmentObbLocal = {
		.origin = Mat4::Transform(segment.origin, inverseObbWorldMatrix),
		.diff = Mat4::Transform(segment.diff, inverseObbWorldMatrix)
	};

	///- OBBのLocal空間のAABBとSegmentで衝突判定を取る
	return IsCollided(aabbObbLocal, segmentObbLocal);
}

bool IsCollided(const OBB& obb1, const OBB& obb2) {

	///- 分離軸を計算
	std::vector<Vec3f> axes{};

	///- 面法線を分離軸に
	for(uint32_t index = 0; index < 3; ++index) {
		axes.push_back(obb1.orientatinos[index]);
		axes.push_back(obb2.orientatinos[index]);
	}

	///- 面法線同士の外積を分離軸に
	for(uint32_t row = 0; row < 3; ++row) {
		for(uint32_t col = 0; col < 3; ++col) {
			axes.push_back(Cross(obb1.orientatinos[row], obb2.orientatinos[col]));
		}
	}

	///- 分離軸から二つのオブジェクトが離れているか計算
	for(const auto& axis : axes) {
		///- obb1の最小値と最大値
		std::vector<Vec3f> v1 = obb1.GetVertices();
		float min1 = MinDot(v1, axis);
		float max1 = MaxDot(v1, axis);
		float diff1 = max1 - min1;

		///- obb2の最小値と最大値
		std::vector<Vec3f> v2 = obb2.GetVertices();
		float min2 = MinDot(v2, axis);
		float max2 = MaxDot(v2, axis);
		float diff2 = max2 - min2;

		///- 差分の合計
		float sumSpan = diff1 + diff2;
		///- 二つのオブジェクトの最大値と最小値の差分
		float longSpan = std::max(max1, max2) - std::min(min1, min2);

		///- 離れている
		if(sumSpan < longSpan) {
			return false;
		}

	}


	return true;
}
