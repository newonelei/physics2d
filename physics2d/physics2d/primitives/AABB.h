#pragma once

#include "math/vector2d.h"
#include "rigidbody/rigidbody2d.h"

namespace primitives
{
	// Axis aligned bounding Box, this is not rotated box, just aligned to axis X and Y
	class AABB
	{
	public:
		AABB() 
		{
			this->half_size_ = this->size_ * 0.5f;
		}
		AABB(Vector2D min, Vector2D max)
		{
			this->size_ = max - min;
			this->half_size_ = this->size_ * 0.5f;
			this->center_ = min + this->half_size_;
		}

		Vector2D getMin() {
			return rigidbody_->GetPosition() - this->half_size_;
		}

		Vector2D getMax() {
			return rigidbody_->GetPosition() + this->half_size_;
		}
	private:
		Vector2D center_ = Vector2D::Zero;
		Vector2D size_   = Vector2D::Zero;
		Vector2D half_size_ = Vector2D::Zero;
		Rigidbody2D* rigidbody_ = nullptr;

	};
}