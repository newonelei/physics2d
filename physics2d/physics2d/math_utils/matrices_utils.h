#pragma once

#include <iostream>
#include <sstream>
#include <string>
#include "math/matrices.h"

using namespace std;
using namespace math;

namespace math_utils {

template <typename MatT, int ROW, int COL>
ostream& operator<<(ostream& os, const MatT& mat) {
  for (int r = 0; r < ROW; r++) {
    for (int c = 0; c < COL; c++) {
      os << mat[r][c] << " ";
    }
    os << endl;
  }
  os << endl;

  return os;
}

template <typename MatT, int ROW, int COL>
string ToString(const MatT& mat) {
  stringstream buffer;
  for (int r = 0; r < ROW; r++) {
    for (int c = 0; c < COL; c++) {
      buffer << mat[r][c] << " ";
    }
    buffer << endl;
  }
  buffer << endl;

  return buffer.str();
}


}  // namespace math_utils