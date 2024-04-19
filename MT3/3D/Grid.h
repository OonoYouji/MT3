#pragma once

#include <cmath>

class Camera;

class Grid final {
public:

	static Grid* GetInstance();

	void Init();
	void Draw(const Camera& camera);
	

	///- setter

	void SetGridHalfWidth(float gridHalfWidth) {
		gridHalfWidth_ = gridHalfWidth;
	}

	void SetSubdivision(uint32_t subdivision) {
		subdivision_ = subdivision;
	}

private:


	float gridHalfWidth_ = 2.0f;
	uint32_t subdivision_ = 10;

private:

	Grid() = default;
	~Grid() = default;

	Grid& operator=(const Grid&) = delete;
	Grid(const Grid&) = delete;
	Grid(Grid&&) = delete;

};