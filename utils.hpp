#include <iostream>
#include <vector>
#include <string>

bool boo(std::vector< std::string > args)
{
  std::string text = args[0];
  int n = std::stoi(args[1]);
  try
  {
    for (int i = 0; i < n; ++i)
    {
      std::cout << text << "\n";
    }
  }
  catch (const std::exception* exc)
  {
    std::cerr << exc->what() << "\n";

    return false;
  }

  return true;
}

bool blah(std::vector< std::string > args)
{
  try
  {
    std::cout << "ooga booga\n";
  }
  catch (const std::exception* exc)
  {
    std::cerr << exc->what() << "\n";

    return false;
  }

  return true;
}