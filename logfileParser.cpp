#include "logfileParser.h"
#include "logfileUtils.h"
#include <sstream>
#include <vector>

LogfileParser::LogfileParser(std::string infile, std::string afile) : input_file(infile), analysis_file(afile)
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

std::string LogfileParser::getMarkerTimestamp(std::string marker)
{
  std::ifstream input(input_file);
  std::string line;
  std::string buf;
  bool found = false;
  std::string markerTimestamp = "";

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
      if (buf.compare(marker) == 0)
      {
        std::cout << "*****found the marker*****" << std::endl;
        std::cout << line << std::endl;
        found = true;

        // get the timestamp
        // TODO: need to check whether timestamp is available in log before adding up
        markerTimestamp = vec[0] + ' ' + vec[1] + ' ' + vec[2] + ' ' + vec[3];
      }
    }
    vec.clear();
  }
  input.close();
  return markerTimestamp;
}

bool LogfileParser::seek(std::string timestamp)
{
  return true;
}

std::vector<std::string> LogfileParser::getTokens(std::string start, std::string end)
{
  std::vector<std::string> tokens = {};
  return tokens;
}

std::string LogfileParser::getTimestamp(std::string line)
{
  std::string buf;
  std::vector<std::string> vec;
  std::string time = "";

  // convert the line in to stream:
  std::istringstream iss(line);
  // read the line, word by word
  while (std::getline(iss, buf, CDELIMITER))
  {
    vec.push_back(buf);
    if (vec.size() >= 4)
    {
      time = vec[0] + ' ' + vec[1] + ' ' + vec[2] + ' ' + vec[3];
      break;
    }
  }
  vec.clear();
  return time;
}

std::string LogfileParser::getStartTimestamp()
{
  std::ifstream input(input_file);
  std::string firstLine;
  std::string time = "";

  if (std::getline(input, firstLine))
  {
    time = getTimestamp(firstLine);
  }
  return time;
}

bool LogfileParser::writeLogMessageForAnalysis(std::string start, std::string end)
{
  std::ifstream input(input_file);
  std::ofstream analysisFile(analysis_file);
  std::string line;
  std::string time = "";

  bool reached = false;

  while (std::getline(input, line))
  {
    time = LogfileParser::getTimestamp(line);
    if (time != "")
    {
      if (compareTimestamp(start, time) <= 0)
      {
        if (compareTimestamp(end, time) > 0)
        {
          analysisFile << line << std::endl;
        }
        else
        {
          std::cout << "Reached end of the log messages....." << std::endl;
          break;
        }
      }
    }
  }
  input.close();
  analysisFile.close();
  return true;
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
      if (buf.compare("event=\'PLUGIN_CRASHED\'") == 0)
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