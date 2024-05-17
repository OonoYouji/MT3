#pragma once

#include "Line.h"

class Sphere;
struct Plane;
struct Triangle;

bool IsCollision(const Sphere& s1, const Sphere& s2);

bool IsCollision(const Sphere& sphere, const Plane& plane);

bool IsCollision(const Line& line, const Plane& plane);
bool IsCollision(const Ray& ray, const Plane& plane);
bool IsCollision(const Segment& segment, const Plane& plane);

bool IsCollision(const Segment& segment, const Triangle& triangle);