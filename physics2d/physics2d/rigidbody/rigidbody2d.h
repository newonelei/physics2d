#pragma once
#include "math/vector2d.h"
using namespace math;

namespace physics
{
	class Rigidbody2D // : public Component, to do, implement your own Component
	{
	public:
		math::Vector2D GetPosition() const { return position_; }
		void SetPosition(math::Vector2D val) { position_ = val; }

		float GetRotation() const { return rotation_; }
		void SetRotation(float val) { rotation_ = val; }
	private:
		Vector2D position_;

		// degree
		float rotation_ = 0.0f;
	};
}