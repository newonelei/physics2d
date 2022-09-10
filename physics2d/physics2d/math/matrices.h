#pragma once

namespace math
{
	typedef class Mat2 {
		union {
			struct
			{
				float _11, _12,
					_21, _22;
			};

			float as_array_[4];
		};

		// return row
		inline float* operator[](int i)
		{
			return &as_array_[i * 2];
		}
	} Mat2;

	typedef class Mat3 {
		union {
			struct
			{
				float _11, _12, _13,
					_21, _22, _23,
					_31, _32, _33;
			};

			float as_array_[9];
		};

		// return row
		inline float* operator[](int i)
		{
			return &as_array_[i * 3];
		}
	} Mat3;

	typedef class Mat4 {
		union {
			struct
			{
				float _11, _12, _13, _14,
					_21, _22, _23, _24,
					_31, _32, _33, _34,
					_41, _42, _43, _44;
			};

			float as_array_[16];
		};

		// return row
		inline float* operator[](int i)
		{
			return &as_array_[i * 4];
		}
	} Mat4;

	void Transpose(const float *)
}