#include <iostream>
#include <fstream>
#include <new>

namespace alekseev
{
  bool readSize(std::istream &in, int &rows, int &cols)
  {
    if (!(in >> rows >> cols))
    {
      return false;
    }
    return rows >= 0 && cols >= 0;
  }

  bool readElements(std::istream &in, int *data, long long count)
  {
    for (long long i = 0; i < count; ++i)
    {
      if (!(in >> data[i]))
      {
        return false;
      }
    }
    return true;
  }

  bool hasNoExtraData(std::istream &in)
  {
    in >> std::ws;
    return in.peek() == std::char_traits< char >::eof();
  }

  int countLocalMinima(const int *matrix, int rows, int cols)
  {
    int result = 0;

    for (int i = 1; i < rows - 1; ++i)
    {
      for (int j = 1; j < cols - 1; ++j)
      {
        const int current = matrix[i * cols + j];
        bool is_min = true;

        for (int di = -1; di <= 1 && is_min; ++di)
        {
          for (int dj = -1; dj <= 1; ++dj)
          {
            if (di == 0 && dj == 0)
            {
              continue;
            }
            if (matrix[(i + di) * cols + (j + dj)] <= current)
            {
              is_min = false;
              break;
            }
          }
        }

        if (is_min)
        {
          ++result;
        }
      }
    }
    return result;
  }
}

int main(int argc, char **argv)
{
  if (argc != 4)
  {
    std::cerr << "Usage: " << argv[0] << " num input output\n";
    return 1;
  }

  int mode = 0;
  if (argv[1][0] == '1' && argv[1][1] == '\0')
  {
    mode = 1;
  }
  else if (argv[1][0] == '2' && argv[1][1] == '\0')
  {
    mode = 2;
  }
  else
  {
    std::cerr << "First parameter must be 1 or 2\n";
    return 1;
  }

  std::ifstream input(argv[2]);
  if (!input)
  {
    std::cerr << "Cannot open input file\n";
    return 2;
  }

  int rows = 0;
  int cols = 0;
  if (!alekseev::readSize(input, rows, cols))
  {
    std::cerr << "Invalid matrix size\n";
    return 2;
  }

  const long long count = static_cast< long long >(rows) * cols;
  const long long max_fixed = 10000;

  int fixed[max_fixed] = {};
  int *dynamic = nullptr;
  int *matrix = nullptr;

  if (mode == 1)
  {
    if (count > max_fixed)
    {
      std::cerr << "Matrix is too large for fixed array\n";
      return 2;
    }
    matrix = fixed;
  }
  else
  {
    try
    {
      dynamic = new int[count];
      matrix = dynamic;
    }
    catch (const std::bad_alloc &)
    {
      std::cerr << "Cannot allocate memory\n";
      return 2;
    }
  }

  const bool is_read = alekseev::readElements(input, matrix, count);
  const bool is_clean = is_read && alekseev::hasNoExtraData(input);
  if (!is_clean)
  {
    delete[] dynamic;
    std::cerr << "Invalid matrix data\n";
    return 2;
  }

  const int result = alekseev::countLocalMinima(matrix, rows, cols);
  delete[] dynamic;

  std::ofstream output(argv[3]);
  if (!output)
  {
    std::cerr << "Cannot open output file\n";
    return 2;
  }

  if (count == 0)
  {
    output << "0 0\n";
  }
  else
  {
    output << result << '\n';
  }
  return 0;
}
