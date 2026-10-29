#include <iostream>
#include <cstring>
#include <cctype>
#include <new>

namespace skiruta
{
  char *readLine(size_t &size)
  {
    char *res = nullptr;
    char *buf = static_cast< char * >(malloc(1));
    if (!buf)
    {
      throw std::bad_alloc();
    }
    char c = 0;
    while (std::cin.get(c) && c != '\n' && buf)
    {
      buf[size] = c;
      buf = static_cast< char * >(realloc(buf, ++size));
    }
    if (buf)
    {
      res = static_cast< char * >(malloc(size + 1));
      strcpy(res, buf);
      res[size] = '\0';
      free(buf);
    }
    return res;
  }

  int countDifLat(char *t, const size_t s)
  {
    int count = 0;
    char *seen = new char[s];
    for (size_t i = 0; i < s; i++)
    {
      seen[i] = ' ';
      if (!(strchr(seen, *(t + i))) && std::isalpha(*(t + i)))
      {
        seen[i] = *(t + i);
        count++;
      }
    }
    return count;
  }
}

int main()
{
  try
  {
    char *t = nullptr;
    size_t s = 0;
    t = skiruta::readLine(s);
    if (t)
    {
      std::cout << skiruta::countDifLat(t, s) << std::endl;
    }
    else
    {
      throw std::bad_alloc();
    }
    free(t);
  }
  catch (const std::bad_alloc &)
  {
    std::cerr << "Memory error" << std::endl;
    return 1;
  }
  return 0;
}
