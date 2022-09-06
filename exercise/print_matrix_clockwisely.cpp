#include <iostream>
#include <vector>

using Matrix = std::vector<std::vector<int>>;

void PrintMatrixClockwisely(const int rows, const int columns);
void PrintMatrixInCircle(const int rows, const int columns, const int start,
                         Matrix& matrix);

int main(int argc, char** argv) {
  PrintMatrixClockwisely(atoi(argv[1]), atoi(argv[2]));
  // PrintMatrixClockwisely(5, 7);

  return 0;
}

void PrintMatrixClockwisely(const int rows, const int columns) {
  if (rows <= 0 || columns <= 0) {
    return;
  }

  int start{0};
  Matrix matrix{static_cast<Matrix::size_type>(rows),
                std::vector<int>(columns)};

  while (start * 2 < rows && start * 2 < columns) {
    PrintMatrixInCircle(rows, columns, start, matrix);
    ++start;
  }

  for (const auto& row : matrix) {
    for (const auto& elem : row) {
      std::cout << elem << " ";
    }
    std::cout << "\n";
  }

  return;
}

void PrintMatrixInCircle(const int rows, const int columns, const int start,
                         Matrix& matrix) {
  static int cnt{1};
  int end_column{columns - start - 1};
  int end_row{rows - start - 1};

  // Left to right.
  for (int column = start; column <= end_column; ++column) {
    matrix[start][column] = cnt++;
  }

  // Top to bottom.
  if (start < end_row) {
    for (int row = start + 1; row <= end_row; ++row) {
      matrix[row][end_column] = cnt++;
    }
  }

  // Right to left.
  if (start < end_column && start < end_row) {
    for (int column = end_column - 1; column >= start; --column) {
      matrix[end_row][column] = cnt++;
    }
  }

  // Bottom to top.
  if (start < end_column && start < end_row - 1) {
    for (int row = end_row - 1; row >= start + 1; --row) {
      matrix[row][start] = cnt++;
    }
  }

  return;
}
