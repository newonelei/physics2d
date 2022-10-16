#include "matrices.h"
#include "float_utils.h"
#include <cmath>

namespace math {
void Transpose(const float* srcMat, float* dstMat, int srcRows, int srcCols) {
  for (int i = 0; i < srcRows * srcCols; ++i) {
    int row = i / srcRows;
    int col = i % srcRows;
    dstMat[i] = srcMat[srcCols * col +
                       row];  // transposed element index on i([srcCols * row +
                              // col]) is j([srcCols * col + row])
  }
}

bool Multiply(float* out, const float* mat_a, int a_rows, int a_cols,
              const float* mat_b, int b_rows, int b_cols) {
  if (a_cols != b_rows) {
    return false;
  }

  for (int i = 0; i < a_rows; ++i) {
    for (int j = 0; j < a_cols; ++j) {
      int mat_out_idx = b_cols * i + j;
      out[mat_out_idx] = 0.0f;
      for (int k = 0; k < b_rows; ++k) {
        int mat_a_index = a_cols * i + k;
        int mat_b_index = b_cols * k + j;
        out[mat_out_idx] += mat_a[mat_a_index] * mat_b[mat_b_index];
      }
    }
  }

  return true;
}

// explicit Cut template instantiation
template Matrix2D Cut<Matrix2D, Matrix3D, 3, 3>(const Matrix3D&, int, int);

template Matrix3D Cut<Matrix3D, Matrix4D, 4, 4>(const Matrix4D&, int, int);

void Cofactor(float* out, const float* minor, int rows, int cols) {
	for (int i = 0; i < rows; ++i) {
    for (int j = 0; j < cols; ++j) {
      int target = j * cols + i;       // target index
      int source = target;             // source index
	  float sign = (i + j) % 2 == 0 ? 1.0f : -1.0f;// pow(-1.0f, i + j);  // -1 or 1
      out[target] = minor[source] * sign;
    }
  }
}

Matrix4D Translation(float x, float y, float z)
{
	return Matrix4D(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		x, y, z, 0.0f
	);
}

Matrix4D Translation(const Vector3D& pos)
{
	return Matrix4D(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		pos.x_, pos.y_, pos.z_, 0.0f
	);
}

Vector3D GetTranslation(const Matrix4D& mat)
{
	return Vector3D(mat._41, mat._42, mat._43);
}

Matrix4D Scale(float x, float y, float z)
{
	return Matrix4D(
		   x, 0.0f, 0.0f, 0.0f,
		0.0f,    y, 0.0f, 0.0f,
		0.0f, 0.0f,    z, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f);
}

Matrix4D Scale(const Vector3D& vec)
{
	return Matrix4D(
		vec.x_, 0.0f, 0.0f, 0.0f,
		0.0f, vec.y_, 0.0f, 0.0f,
		0.0f, 0.0f, vec.z_, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f);
}

Vector3D GetScale(const Matrix4D& mat)
{
    return Vector3D(mat._11, mat._22, mat._33);
}

Matrix4D ZRotation(float angle)
{
    angle = DEG2RAD(angle);
    return Matrix4D(
        cosf(angle),  sinf(angle), 0.0f, 0.0f,
        -sinf(angle), cosf(angle), 0.0f, 0.0f,
        0.0f,         0.0f,        1.0f, 0.0f,
        0.0f,         0.0f,        0.0f, 1.0f
    );
}

Matrix3D ZRotation3x3(float angle)
{
    angle = DEG2RAD(angle);
    return Matrix3D(
        cosf(angle),  sinf(angle), 0.0f,
        -sinf(angle), cosf(angle), 0.0f,
        0.0f,         0.0f,        1.0f
    );
}

Matrix4D XRotation(float angle)
{
    angle = DEG2RAD(angle);
    return Matrix4D(
        1.0f, 0.0f,         0.0f,        0.0f,
        0.0f,  cosf(angle), sinf(angle), 0.0f,
        0.0f, -sinf(angle), cosf(angle), 0.0f,
        0.0f, 0.0f,         0.0f,        1.0f
    );

}

Matrix3D XRotation3x3(float angle)
{
    angle = DEG2RAD(angle);
    return Matrix3D(
        1.0f,  0.0f,        0.0f,
        0.0f,  cosf(angle), sinf(angle),
        0.0f, -sinf(angle), cosf(angle)
    );
}

Matrix4D YRotation(float angle)
{
    angle = DEG2RAD(angle);
    return Matrix4D(
        cosf(angle), 0.0f, -sinf(angle), 0.0f,
        0.0f,        1.0f, 0.0f,         0.0f,
        sinf(angle), 0.0f, cosf(angle),  0.0f,
        0.0f,        0.0f, 0.0f,         1.0f
    );
}

Matrix3D YRotation3x3(float angle)
{
    angle = DEG2RAD(angle);
    return Matrix3D(
        cosf(angle), 0.0f, -sinf(angle),
        0.0f,        1.0f, 0.0f,
        sinf(angle), 0.0f, cosf(angle)
    );
}


Matrix4D Rotation(float pitch, float yaw, float roll)
{
    return ZRotation(roll) * XRotation(pitch) * YRotation(yaw);
}

Matrix3D Rotation3x3(float pitch, float yaw, float roll)
{
    return ZRotation3x3(roll) * XRotation3x3(pitch) * YRotation3x3(yaw);
}

Matrix4D AxisAngle(const Vector3D& axis, float angle)
{
    angle = DEG2RAD(angle);
    float c = cosf(angle);
    float s = sinf(angle);
    float t = 1.0f - cosf(angle);

    float x = axis.x_;
    float y = axis.y_;
    float z = axis.z_;
    if(!CMP(math::MagnitudeSq(axis), 1.0f))
    {
        float inv_len = 1.0f / math::Magnitude(axis);
        x *= inv_len;
        y *= inv_len;
        z *= inv_len;
    }// x, y, and z are a normalized vector

    return Matrix4D
    (
        t * (x * x) + c, t * x * y + s * z, t * x * z - s * y, 0.0f,
        t * x * y - s * z, t * (y * y) + c, t * y * z + s * x, 0.0f,
        t * x * z + s * y, t * y * z - s * x, t * (z * z) + c, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
}

Matrix3D AxisAngle3x3(const Vector3D& axis, float angle)
{
  angle = DEG2RAD(angle);
  float c = cosf(angle);
  float s = sinf(angle);
  float t = 1.0f - cosf(angle);

  float x = axis.x_;
  float y = axis.y_;
  float z = axis.z_;
  if (!CMP(math::MagnitudeSq(axis), 1.0f)) {
    float inv_len = 1.0f / math::Magnitude(axis);
    x *= inv_len;
    y *= inv_len;
    z *= inv_len;
  }  // x, y, and z are a normalized vector

  return Matrix3D(
      t * (x * x) + c, t * x * y + s * z, t * x * z - s * y,
      t * x * y - s * z, t * (y * y) + c, t * y * z + s * x,
      t * x * z + s * y, t * y * z - s * x, t * (z * z) + c
  );
}
}  // namespace math
