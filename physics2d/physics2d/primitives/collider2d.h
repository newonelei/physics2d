#pragma once
#include "math/vector2d.h"

namespace primitives
{
	class Vector2D;
	class Collider2D // todo : public Component, implement your own component system
	{
	public:
		// TODO IMPLEMENT THIS, later we will implement force then do it
		//float GetInertiaTensor(float mass);
	protected:
		Vector2D offset_ = Vector2D
	};
}