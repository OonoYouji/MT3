#pragma once

#include "Line.h"
#include "AABB.h"

struct Sphere;
struct Plane;
struct Triangle;
struct OBB;

bool IsCollided(const Sphere& s1, const Sphere& s2);

bool IsCollided(const Sphere& sphere, const Plane& plane);

bool IsCollided(const Line& line, const Plane& plane);
bool IsCollided(const Ray& ray, const Plane& plane);
bool IsCollided(const Segment& segment, const Plane& plane);

bool IsCollided(const Line& line, const Triangle& triangle);
bool IsCollided(const Ray& ray, const Triangle& triangle);
bool IsCollided(const Segment& segment, const Triangle& triangle);

bool IsCollided(const AABB& a, const AABB& b);

bool IsCollided(const AABB& aabb, const Sphere& sphere);

bool IsCollided(const AABB& aabb, const Line& segment);
bool IsCollided(const AABB& aabb, const Ray& segment);
bool IsCollided(const AABB& aabb, const Segment& segment);

bool IsCollided(const OBB& obb, const Sphere& sphere);