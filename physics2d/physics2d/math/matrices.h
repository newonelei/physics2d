#pragma once

#include "matrix2d.h"
#include "matrix3d.h"
#include "matrix4d.h"

#include "vector3d.h"

namespace math {
void Transpose(const float* srcMat, float* dstMat, int srcRows, int srcCols);

bool Multiply(float* out, const float* mat_a, int a_rows, int a_cols,
              const float* mat_b, int b_rows, int b_cols);

template <typename MatCutT, typename MatSrcT, int ROW, int COL>
MatCutT Cut(const MatSrcT& mat, int row, int col) {
  MatCutT result;

  int index = 0;
  for (int i = 0; i < ROW; ++i) {
    for (int j = 0; j < COL; ++j) {
      if (i == row || j == col) continue;

	  int target = index++;
	  int source = i * COL + j;
      result.as_array_[target] = mat.as_array_[source];
    }
  }

  return result;
}

void Cofactor(float* out, const float* minor, int rows, int cols);

// translation
Matrix4D Translation(float x, float y, float z);
Matrix4D Translation(const Vector3D& pos);
Vector3D GetTranslation(const Matrix4D& mat);

// scale matrix operations
Matrix4D Scale(float x, float y, float z);
Matrix4D Scale(const Vector3D& vec);
Vector3D GetScale(const Matrix4D& mat);

// Eular rotation operators : could have Gimbal lock
Matrix4D ZRotation(float angle);
Matrix3D ZRotation3x3(float angle);
Matrix4D XRotation(float angle);
Matrix3D XRotation3x3(float angle);
Matrix4D YRotation(float angle);
Matrix3D YRotation3x3(float angle);
Matrix4D Rotation(float pitch, float yaw, float roll);
Matrix3D Rotation3x3(float pitch, float yaw, float roll);

// Axis angle rotation
Matrix4D AxisAngle(const Vector3D& axis, float angle);
Matrix3D AxisAngle3x3(const Vector3D& axis, float angle);
}  // namespace math