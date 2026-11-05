#include <iostream>
#include <stdexcept>

namespace skiruta
{
  struct Counter
  {
    Counter()
    {
      count = 0;
    }
    size_t operator()() const
    {
      return count;
    }
    void operator()(int)
    {
      count++;
    }
  private:
    size_t count;
  };
  struct PrevNum
  {
    PrevNum()
    {
      prev = 0;
    }
    void operator()(int p)
    {
      prev = p;
    }
    int operator()() const
    {
      return prev;
    }
  private:
    int prev;
  };
  struct DimRev
  {
    DimRev()
    {
      totalNums = Counter();
      prevNum = PrevNum();
      amountOfDivisibleNums = 0;
    }
    void operator()(int n)
    {
      if (prevNum() && n % prevNum() == 0)
      {
        amountOfDivisibleNums++;
      }
      prevNum(n);
      totalNums(n);
    }
    size_t operator()() const
    {
      if (totalNums() < 2)
      {
        throw std::runtime_error("Not enough numbers");
      }
      return amountOfDivisibleNums;
    }
  private:
    Counter totalNums;
    PrevNum prevNum;
    size_t amountOfDivisibleNums;
  };
}

int main()
{
  try
  {
    int n = 0;
    skiruta::DimRev res = skiruta::DimRev();
    while (true)
    {
      if (!(std::cin >> n))
      {
        throw std::invalid_argument("Wrong input, integer expected");
      }
      if (!n)
      {
        break;
      }
      res(n);
    }
    std::cout << res() << std::endl;
  }
  catch (const std::invalid_argument &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (const std::runtime_error &e)
  {
    std::cerr << e.what() << std::endl;
    return 2;
  }
  return 0;
}
