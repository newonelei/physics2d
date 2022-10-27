#pragma once
#include "math/vector2d.h"

using namespace math;

namespace primitives
{
	class Box2D
	{
	private:
		Vector2D size_ = Vector2D::Zero;
		Vector2D half_size_ = Vector2D::Zero;
	};
}
