#include <iostream>
#include <fstream>
#include <cstddef>

namespace sierra {
  const size_t MAX_SIZE = 10000;

  bool isNumberOneOrTwo(const char* str, int& num)
  {
    if (str[0] == '1' && str[1] == '\0') {
      num = 1;
      return true;
    }
    if (str[0] == '2' && str[1] == '\0') {
      num = 2;
      return true;
    }
    return false;
  }

  bool readMatrix(std::istream& in, int* matrix, size_t rows, size_t cols)
  {
    for (size_t i = 0; i < rows * cols; ++i) {
      in >> matrix[i];
      if (in.fail()) {
        return false;
      }
    }
    return true;
  }

  size_t numRowLongestSeries(const int* matrix, size_t rows, size_t cols)
  {
    size_t best_row = 0;
    size_t best_len = 0;
    for (size_t i = 0; i < rows; ++i) {
      size_t len = 0;
      size_t max_len = 0;
      for (size_t j = 0; j < cols; ++j) {
        if (j > 0 && matrix[i * cols + j] == matrix[i * cols + j - 1]) {
          ++len;
        } else {
          len = 1;
        }
        if (len > max_len) {
          max_len = len;
        }
      }
      if (max_len > best_len) {
        best_len = max_len;
        best_row = i + 1;
      }
    }
    return best_row;
  }
}

int main(int argc, char** argv)
{
  if (argc != 4) {
    std::cerr << "Wrong number of arguments\n";
    return 1;
  }
  int num = 0;
  if (!sierra::isNumberOneOrTwo(argv[1], num)) {
    std::cerr << "First parameter must be 1 or 2\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  size_t rows = 0;
  size_t cols = 0;
  input >> rows >> cols;
  if (input.fail()) {
    std::cerr << "Can not read matrix\n";
    return 2;
  }

  size_t result = 0;
  if (num == 1) {
    int matrix[sierra::MAX_SIZE] = {};
    if (rows * cols > sierra::MAX_SIZE) {
      std::cerr << "Matrix is too big\n";
      return 2;
    }
    if (!sierra::readMatrix(input, matrix, rows, cols)) {
      std::cerr << "Can not read matrix\n";
      return 2;
    }
    result = sierra::numRowLongestSeries(matrix, rows, cols);
  } else {
    int* matrix = nullptr;
    try {
      matrix = new int[rows * cols];
    } catch (const std::bad_alloc&) {
      std::cerr << "Not enough memory\n";
      return 2;
    }
    if (!sierra::readMatrix(input, matrix, rows, cols)) {
      delete[] matrix;
      std::cerr << "Can not read matrix\n";
      return 2;
    }
    result = sierra::numRowLongestSeries(matrix, rows, cols);
    delete[] matrix;
  }

  std::ofstream output(argv[3]);
  output << result << "\n";
  return 0;
}
