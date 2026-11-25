#include <iostream>
#include <stdexcept>

namespace pechnikov
{
  struct ISeqPropety
  {
  public:
    int operator()() const;
    void operator()(int i);
    virtual ~ISeqPropety() = default;
  private:
    virtual int result() const = 0;
    virtual void next(int i) = 0;
  };

  struct Count: public ISeqPropety
  {
  private:
    int lenght_, current_, max_lenght_;
    void next(int i) override;
    int result() const override;
  public:
    Count();
  };
}

int main()
{
  pechnikov::Count counter;
  int value = 0;
  try
  {
    while (true)
    {
      if (!(std::cin >> value))
      {
        throw std::invalid_argument("Invalid argument");
      }
      counter(value);
      if (value == 0)
      {
        break;
      }
    }
  }
  catch (const std::invalid_argument& err)
  {
    std::cerr << err.what() << "\n";
    return 1;
  }
  catch (const std::exception& err)
  {
    std::cerr << err.what() << "\n";
    return 2;
  }
  std::cout << counter();
}

namespace pechnikov
{
  int ISeqPropety::operator()() const
  {
    return result();
  }

  void ISeqPropety::operator()(int i)
  {
    next(i);
  }

  Count::Count()
  {
    lenght_ = 0;
    current_ = 0;
    max_lenght_ = 0;
  }

  void Count::next(int next)
  {
    if (next == 0)
    {
      if (lenght_ > max_lenght_)
      {
        max_lenght_ = lenght_;
      }
    }
    else
    {
      if (next <= current_)
      {
        lenght_ += 1;
      }
      else
      {
        if (lenght_ > max_lenght_)
        {
          max_lenght_ = lenght_;
        }
        lenght_ = 1;
      }
      current_ = next;
    }
  }

  int Count::result() const
  {
    return max_lenght_;
  }
}
