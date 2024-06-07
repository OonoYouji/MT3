﻿#pragma once

#include "Line.h"
#include "AABB.h"

class Sphere;
struct Plane;
struct Triangle;

bool IsCollision(const Sphere& s1, const Sphere& s2);

bool IsCollision(const Sphere& sphere, const Plane& plane);

bool IsCollision(const Line& line, const Plane& plane);
bool IsCollision(const Ray& ray, const Plane& plane);
bool IsCollision(const Segment& segment, const Plane& plane);

bool IsCollision(const Line& line, const Triangle& triangle);
bool IsCollision(const Ray& ray, const Triangle& triangle);
bool IsCollision(const Segment& segment, const Triangle& triangle);

bool IsCollision(const AABB& a, const AABB& b);

bool IsCollision(const AABB& aabb, const Sphere& sphere);
bool IsCollision(const AABB& aabb, const Line& segment);
bool IsCollision(const AABB& aabb, const Ray& segment);
bool IsCollision(const AABB& aabb, const Segment& segment);