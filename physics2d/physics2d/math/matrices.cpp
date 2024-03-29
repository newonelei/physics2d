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

// for the point version, hardcoded the last W component with 1.0f
Vector3D MultiplyPoint(const Vector3D& vec, const Matrix4D& mat)
{
    Vector3D result;
    result.x_ = vec.x_ * mat._11 + vec.y_ * mat._21 + vec.z_ * mat._31 + 1.0f * mat._41;
    result.y_ = vec.x_ * mat._12 + vec.y_ * mat._22 + vec.z_ * mat._32 + 1.0f * mat._42;
    result.x_ = vec.x_ * mat._13 + vec.y_ * mat._23 + vec.z_ * mat._33 + 1.0f * mat._43;
    return result;
}

// for the vector, hardcoded the last W component as 0.0f
Vector3D MultiplyVector(const Vector3D& vec, const Matrix4D& mat)
{
    Vector3D result;
    result.x_ = vec.x_ * mat._11 + vec.y_ * mat._21 + vec.z_ * mat._31;
    result.y_ = vec.x_ * mat._12 + vec.y_ * mat._22 + vec.z_ * mat._32;
    result.x_ = vec.x_ * mat._13 + vec.y_ * mat._23 + vec.z_ * mat._33;
    return result;
}

Vector3D MultiplyPoint(const Vector3D& vec, const Matrix3D& mat)
{
    Vector3D result;
    result.x_ = Dot(vec, Vector3D(mat._11, mat._21, mat._31));
    result.y_ = Dot(vec, Vector3D(mat._12, mat._22, mat._32));
    result.z_ = Dot(vec, Vector3D(mat._13, mat._23, mat._33));
    return result;
}

Matrix4D Transform(const Vector3D& scale, const Vector3D& eulerRotation, const Vector3D& translate)
{
    return Scale(scale) 
        * Rotation(eulerRotation.x_, eulerRotation.y_, eulerRotation.z_) 
        * Translation(translate);
}

Matrix4D Transform(const Vector3D& scale, const Vector3D& rotationAxis, float rotationAngle, const Vector3D& translate)
{
    return Scale(scale)
        * AxisAngle(rotationAxis, rotationAngle)
        * Translation(translate);
}

// generate a view transform matrix that transform world space object to camera view space
Matrix4D LookAt(const Vector3D& position, const Vector3D& target, const Vector3D& up)
{
    // we need to get rotation of the matrix and position of camera
    Vector3D forward = Normalized(target - position);

    // COMMENT: up is the normally(often) world space up axis, this up vector is the random
    // vector that is on the same plane
    // of forward vector and camera's real up vector.
    // We use this up vector to calculate right vector, then use right and
    // forward vector to get real camera up vector
    Vector3D right = Normalized(Cross(up, forward)); // we are using lefthanded coordinate

    // this the real camera up vector
    Vector3D newUp = Cross(forward, right);

    /*
    view matrix = rotMat * transMat = Matrix4D(
        right.x_, right.y_, right.z_, 0.0f,
        newUp.x_, newUp.y_, newUp.z_, 0.0f,
        forwards.x_, forward.y_, forward.z_, 0.0f,
        0.0f,     0.0f,     0.0f,     1.0f
    ) * Matrix4D(
        1.0f,     0.0f,     0.0f,     0.0f,
        0.0f,     1.0f,     0.0f,     0.0f,
        0.0f,     0.0f,     1.0f,     0.0f,
        position.x_, position.y_, position.z_, 1.0f
    ) = Matrix4D(
        right.x_, right.y_, right.z_, 0.0f,
        newUp.x_, newUp.y_, newUp.z_, 0.0f,
        forwards.x_, forward.y_, forward.z_, 0.0f,
        position.x_, position.y_, position.z_, 1.0f
    });

    1. The inverse of a translation matrix is the translation matrix with the opposite signs on
       each of the translation components.
    2. The inverse of a rotation matrix is the rotation matrix's transpose.
    3. The inverse of a matrix product is the product of the inverse matrices ordered in reverse.

    inverted view matrix = invertTransMat * invertRotMat = Matrix4D(
        1.0f,         0.0f,         0.0f,         0.0f,
        0.0f,         1.0f,         0.0f,         0.0f,
        0.0f,         0.0f,         1.0f,         0.0f,
        -position.x_, -position.y_, -position.z_, 1.0f
    ) * Matrix4D(
        right.x_, newUp.x_, right.x_, 0.0f,
        right.y_, newUp.y_, right.y_, 0.0f,
        right.z_, newUp.z_, right.z_, 0.0f,
        0.0f,     0.0f,     0.0f,     1.0f
    ) = Matrix4d(
        right.x_, newUp.x_, right.x_, 0.0f,
        right.y_, newUp.y_, right.y_, 0.0f,
        right.z_, newUp.z_, right.z_, 0.0f,
        -position.x_ * right.x_ + -position.y_ * right.y_ + -position.z_ * right.z_,
        -position.x_ * newUp.x_ + -position.y_ * newUp.y_ + -position.z_ * newUp.z_,
        -position.x_ * right.x_ + -position.y_ * right.y_ + -position.z_ * right.z_,
        , 1.0f
    )
    */
    return Matrix4D( // transpose rotation
        right.x_, newUp.x_, forward.x_, 0.0f,
        right.y_, newUp.y_, forward.y_, 0.0f,
        right.z_, newUp.z_, forward.z_, 0.0f,
        -Dot(right, position),
        -Dot(newUp, position),
        -Dot(forward, position), 1.0f
    );
}

Matrix4D Projection(float fov, float aspect, float zNear, float zFar)
{
    float tanHalfFov = tanf(DEG2RAD(fov * 0.5f));
    float fovY = 1.0f / tanHalfFov; // ctan(fov/2)
    float fovX = fovY / aspect; // ctan(fov/2) / aspect

    Matrix4D result;
    result._11 = fovX;
    result._22 = fovY;
    /// _33 = far / range
    result._33 = zFar / (zFar - zNear);
    result._34 = 1.0f;
    // _43 = - near * (far / range)
    result._43 = -zNear * result._33;
    result._44 = 0.0f;
    
    return result;
}

Matrix4D Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
    Matrix4D result;

    result._11 = 2.0f / (right - left);
    result._22 = 2.0f / (top - bottom);
    result._33 = 1.0f / (zFar - zNear);
    result._41 = (left + right) / (left - right);
    result._42 = (top + bottom) / (bottom - top);
    result._43 = zNear / (zNear - zFar);

    return result;
}
}  // namespace math
