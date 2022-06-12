#include <iostream>
#include <functional>

#include "utils.hpp"

template < bool(*)(std::vector< std::string >) >
std::string functionName()
{
  std::string func = __FUNCSIG__;
  std::size_t i = 0;
  std::size_t space = 0;
  while (func[i])
  {
    if (func[i] == ' ')
    {
      space = i;
    }
    if (func[i] == '(')
    {
      std::string name(func.begin() + space + 1, func.begin() + i);

      return name;
    }
    i++;
  }

  return "<FUNCTION_NAME_ERROR>";
}

int main()
{
  bool (*arr[2])(std::vector< std::string >) = { boo, blah };
  bool (*ptr)(std::vector< std::string >) = blah;
  //std::cout << ptr << " " << blah;
  std::string func = functionName<ptr>();

  std::cout << func << " ";
  //bool (*p)() = blah;
  //std::string str = "blah";

  //const char* func = "sdflkjds";

  //std::cout << func[3];
  //if (*p == str)
  //{

  //}

  return 0;
}