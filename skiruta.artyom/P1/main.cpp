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
      total_nums_ = Counter();
      prev_num_ = PrevNum();
      amount_of_divisible_nums_ = 0;
    }
    void operator()(int n)
    {
      if (prev_num_() && n % prev_num_() == 0)
      {
        amount_of_divisible_nums_++;
      }
      prev_num_(n);
      total_nums_(n);
    }
    size_t operator()() const
    {
      if (total_nums_() < 2)
      {
        throw std::runtime_error("Not enough numbers");
      }
      return amount_of_divisible_nums_;
    }
  private:
    Counter total_nums_;
    PrevNum prev_num_;
    size_t amount_of_divisible_nums_;
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
