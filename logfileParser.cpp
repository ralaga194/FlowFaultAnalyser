#include "logfileParser.h"
#include <sstream>
#include <vector>

LogfileParser::LogfileParser(std::string file) : input_file(file)
{
}

int LogfileParser::open()
{
  std::cout << "file is opened successfully" << std::endl;
  return 0;
}

std ::string LogfileParser::findMarker(char *line)
{
  return "";
}

bool LogfileParser::parse()
{
  std::ifstream input(input_file);
  std::string line;
  std::string buf;
  bool found = false;

  while (std::getline(input, line))
  {
    found = false;
    // convert the line in to stream:
    std::istringstream iss(line);

    // declare vector of string (instead of fixed array)
    std::vector<std::string> vec;

    // read the line, word by word
    while (std::getline(iss, buf, CDELIMITER))
    {
      vec.push_back(buf);
      if (buf.compare("PLUGIN_CRASHED") == 0)
      {
        std::cout << "*****found crash marker*****" << std::endl;
        std::cout << line << std::endl;
        found = true;
      }
    }
    vec.clear();
    std::cout << "\n";
  }
  input.close();
  return true;
}

bool LogfileParser::close()
{
  std::cout << "filehandle is closed successfully" << std::endl;
  return true;
}