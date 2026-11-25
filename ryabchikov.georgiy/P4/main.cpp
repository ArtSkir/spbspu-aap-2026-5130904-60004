#include <cctype>
#include <cstddef>
#include <iostream>
#include <new>

namespace ryabchikov {
  char *removeLatin(const char *source, char *result)
  {
    size_t j = 0;
    for (size_t i = 0; source[i] != '\0'; ++i) {
      const unsigned char symbol = source[i];
      if (!std::isalpha(symbol)) {
        result[j] = source[i];
        ++j;
      }
    }
    result[j] = '\0';
    return result;
  }

  char *readLine(std::istream &in, size_t &length)
  {
    const size_t initial_capacity = 16;
    size_t capacity = initial_capacity;
    char *line = new (std::nothrow) char[capacity];
    if (line == nullptr) {
      return nullptr;
    }
    length = 0;
    char c = 0;
    while (in.get(c) && c != '\n') {
      if (length + 1 == capacity) {
        char *const bigger = new (std::nothrow) char[capacity * 2];
        if (bigger == nullptr) {
          delete[] line;
          return nullptr;
        }
        for (size_t i = 0; i < length; ++i) {
          bigger[i] = line[i];
        }
        delete[] line;
        line = bigger;
        capacity *= 2;
      }
      line[length] = c;
      ++length;
    }
    line[length] = '\0';
    return line;
  }
}

int main()
{
  char *line = nullptr;
  char *result = nullptr;
  try {
    size_t length = 0;
    line = ryabchikov::readLine(std::cin, length);
    if (line == nullptr) {
      throw "can't allocate memory for the line";
    }
    if (length == 0) {
      throw "empty input";
    }

    result = new (std::nothrow) char[length + 1];
    if (result == nullptr) {
      throw "can't allocate memory for the result";
    }
  } catch (const char *error) {
    delete[] line;
    std::cerr << "Error: " << error << "\n";
    return 1;
  }
  ryabchikov::removeLatin(line, result);
  std::cout << result << "\n";
  delete[] line;
  delete[] result;
  return 0;
}
