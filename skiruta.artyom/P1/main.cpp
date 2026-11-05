#include <iostream>
#include <stdexcept>

namespace skiruta
{
  struct Counter
  {
    Counter()
    {
      count_ = 0;
    }
    size_t operator()() const
    {
      return count_;
    }
    void operator()(int)
    {
      count_++;
    }
  private:
    size_t count_;
  };
  struct PrevNum
  {
    PrevNum()
    {
      prev_ = 0;
    }
    void operator()(int p)
    {
      prev_ = p;
    }
    int operator()() const
    {
      return prev_;
    }
  private:
    int prev_;
  };
  struct DimRev
  {
    DimRev()
    {
      totalNums_ = Counter();
      prevNum_ = PrevNum();
      amountOfDivisibleNums_ = 0;
    }
    void operator()(int n)
    {
      if (prevNum_() && n % prevNum_() == 0)
      {
        amountOfDivisibleNums_++;
      }
      prevNum_(n);
      totalNums_(n);
    }
    size_t operator()() const
    {
      if (totalNums_() < 2)
      {
        throw std::runtime_error("Not enough numbers");
      }
      return amountOfDivisibleNums_;
    }
  private:
    Counter totalNums_;
    PrevNum prevNum_;
    size_t amountOfDivisibleNums_;
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
