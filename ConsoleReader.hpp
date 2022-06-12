#ifndef CONSOLEREADER_HPP
#define CONSOLEREADER_HPP

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <string>

class ConsoleReader
{
public:
  ConsoleReader();
  ConsoleReader(const ConsoleReader& other);
  ConsoleReader(ConsoleReader&& other) = delete;
  ~ConsoleReader();

  ConsoleReader& operator=(const ConsoleReader& other);
  ConsoleReader& operator=(ConsoleReader&& other) = delete;

  bool run(std::string& fileNameWithCmds, bool (*arr[])(std::vector< std::string >), const std::size_t& n);

private:
  std::unordered_map< std::string, std::pair< std::vector< std::string >, std::string > > cmds_;

  bool readCmds(std::string& fileName);
  std::vector< std::string > splitString(const std::string& str) const;
  void printCmds() const noexcept;

  template< bool(*)(std::vector< std::string >)>
  std::string functionName();
};

ConsoleReader::ConsoleReader()
{}

ConsoleReader::ConsoleReader(const ConsoleReader& other)
{
  if (this != &other)
  {
    cmds_ = other.cmds_;
  }
}

ConsoleReader::~ConsoleReader()
{}

ConsoleReader& ConsoleReader::operator=(const ConsoleReader& other)
{
  if (this != &other)
  {
    ConsoleReader temp(other);
    return temp;
  }
}

bool ConsoleReader::run(std::string& fileNameWithCmds, bool (*arr[])(std::vector< std::string >), const std::size_t& n)
{
  if (readCmds(fileNameWithCmds) == false)
  {
    return false;
  }
  
  std::string strOfArgs = "";
  std::vector< std::string > argsFromConsole;
  std::vector< std::string > argsForCmd;
  std::string cmd = "";
  while (std::getline(std::cin, strOfArgs))
  {
    argsFromConsole = splitString(strOfArgs);
    cmd = argsFromConsole[0];

    if (cmd == "exit")
    {
      return true;
    }

    if (cmd == "help")
    {
      printCmds();
      continue;
    }
    else if (cmds_.find(cmd) == cmds_.end())
    {
      continue;
    }

    for (std::size_t i = 1; i < argsFromConsole.size(); i++)
    {
      argsForCmd[i] = argsFromConsole[i];
    }

    for (std::size_t i = 0; i < n; i++)
    {
      std::string funcName = functionName<arr[i]>();
      if (funcName == cmd)
      {
        if (arr[i](argsForCmd) == false)
        {
          std::cerr << "<ERROR>\n";
        }
        break;
      }
    }
  }
}

bool ConsoleReader::readCmds(std::string& fileName)
{
  std::ifstream text(fileName);
  if (text.is_open() == false)
  {
    std::cerr << "File \"" << fileName << "\" is not open!\n";

    return false;
  }
  for (std::string str; std::getline(text, str); )
  {
    std::vector< std::string > words;
    std::string cmd = "";
    std::vector< std::string > args;
    std::string desc = "";

    words = splitString(str);
    if (words.empty() == false)
    {
      cmd = words[0];

      unsigned int i = 1;
      while (words[i][0] == '[' && i != words.size())
      {
        args.push_back(words[i]);
        i++;
      }

      if (i != words.size())
      {
        desc = words[i];
        i++;
        while (i != words.size())
        {
          desc = desc + " " + words[i];
          i++;
        }
      }

      cmds_.insert_or_assign(cmd, std::make_pair(args, desc));
    }
  }
  text.close();

  return true;
}

std::vector< std::string > ConsoleReader::splitString(const std::string& str) const
{
  std::vector< std::string > words;
  if (str == "")
  {
    return words;
  }

  std::size_t begin = 0;
  std::size_t end = str.find(' ', begin);
  while (end != -1)
  {
    words.push_back(str.substr(begin, end - begin));

    begin = end + 1;
    end = str.find(' ', begin);
  }
  words.push_back(str.substr(begin));

  return words;
}

void ConsoleReader::printCmds() const noexcept
{
  for (std::unordered_map< std::string, std::pair< std::vector< std::string >, std::string > >::const_iterator
    it = cmds_.cbegin(); it != cmds_.cend(); it++)
  {
    std::cout << it->first << " ";
    for (std::size_t i = 0; i < it->second.first.size(); i++)
    {
      std::cout << it->second.first[i] << " ";
    }
    std::cout << "- " << it->second.second << "\n";
  }
}

template< bool(*)(std::vector< std::string >)>
std::string ConsoleReader::functionName()
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
      std::string name(func.begin() + space, func.begin() + i);

      return name;
    }
  }
}

#endif
