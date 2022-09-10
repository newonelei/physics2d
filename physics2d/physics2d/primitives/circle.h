#pragma once
namespace primitives
{
	class Circle
	{
	public:
		Circle(float r)
			: radius_(r)
		{

		}

		float GetRadius() const
		{
			return radius_;
		}

	private:
		float radius_ = 1.0f;
	};
}