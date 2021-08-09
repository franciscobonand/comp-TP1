#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include "logs.h"

bool is_number(const std::string &s)
{
  std::string::const_iterator it = s.begin();
  if (*it == '-')
    ++it;
  while (it != s.end() && std::isdigit(*it))
    ++it;
  return !s.empty() && it == s.end();
}

int main(int argc, char **argv)
{
  logger::Logger logger = logger::Logger();
  std::map<std::string, int> registers = {};
  int cur = 0;
  std::vector<std::string> compiled = std::vector<std::string>();
  int entry;
  std::vector<std::vector<std::string>> operations = {
      {},
      {"R", "M"},
      {"R", "M"},
      {"R"},
      {"R"},
      {"R", "R"},
      {"R"},
      {"R"},
      {"R", "R"},
      {"R", "R"},
      {"R", "R"},
      {"R", "R"},
      {"R", "R"},
      {"R", "R"},
      {"R", "R"},
      {"M"},
      {"M"},
      {"M"},
      {"M"},
      {"M"},
      {},
      {"R"},
  };

  for (int i = 1; i < argc; ++i)
  {
    std::string inputFile = std::string(argv[i]);
    std::ifstream t = std::ifstream(inputFile);
    if (!t.good())
    {
      logger.ERROR(std::string("invalid file name: ") + inputFile);
    }
    std::stringstream buffer;
    buffer << t.rdbuf();

    std::string line;
    getline(buffer, line);
    std::stringstream buf;
    buf.str(line);
    std::string label;
    do
    {
      buf >> label;
      if (buf.eof())
        break;
      int value;
      buf >> value;
      registers[label] = value + cur;
      logger.INFO("reading value:", label, value);
    } while (!buf.eof());

    getline(buffer, line);

    buf = std::stringstream();
    buf.str(line);
    do
    {
      buf >> label;
      // if (buf.eof())
      //   break;
      cur++;
      compiled.push_back(label);
      logger.INFO("reading value:", label);
    } while (!buf.eof());
  }

  std::cout << "MV-EXE" << std::endl;
  if (registers.find("main") == registers.end())
    logger.ERROR("unable to find entry point");
  std::cout << cur << " 0 999"
            << " " << registers["main"] << std::endl;

  int instr;
  int currVal;
  for (int i = 0; i < compiled.size(); ++i)
  {
    auto k = compiled[i];
    instr = atoi(k.c_str());
    if (instr != 21)
    {
      std::cout << instr << " ";
    }
    for (auto j : operations[instr])
    {
      k = compiled[++i];
      if (is_number(k))
        currVal = atoi(k.c_str());
      else if (registers.find(k) == registers.end())
        logger.ERROR("unable to find label", k);
      else
      {
        currVal = registers[k];
        logger.INFO("currval:", currVal);
        if (j == "M")
        {
          currVal -= i;
        }
        logger.INFO("i:", i);
        logger.INFO("k:", k);
        logger.INFO("j:", j);
        logger.INFO("instr:", instr);
      }

      std::cout << currVal << (i == compiled.size() - 1 ? "" : " ");
    }
  }
  std::cout << std::endl;
}
