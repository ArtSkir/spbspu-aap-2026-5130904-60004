#include <iostream>

namespace odaci
{
  void printName(std::ostream & out)
  {
    out << "odaci.batineren" << '\n';
  }
}

int main()
{
  odaci::printName(std::cout);
}
