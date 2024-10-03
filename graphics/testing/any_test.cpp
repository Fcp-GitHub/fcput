#include <iostream>
#include <vector>

std::any f;

template <typename T>
void foo(const std::vector<T>& o)
{
  f = o.data();
  
  std::cout << ;
}

int main(void)
{
  float fArray[] = {1.3, 1.4};
  std::any x(fArray);
  foo(x);
  std::cout << std::any_cast<float*>(f)[0] << '\n';

  return 0;
}