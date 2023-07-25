#include "logfileParser.h"
#include "logfileUtils.h"
#include "logfileAnalyser.h"
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
    while (std::getline(iss, buf, WPE_CDELIMITER))
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

std::string LogfileParser::getTimestamp(std::string line, logFormat fmt = wpeLog)
{
  std::string buf;
  std::vector<std::string> vec;
  std::string time = "";

  // convert the line in to stream:
  std::istringstream iss(line);

  switch (fmt)
  {
  case wpeLog:
  {
    // read the line, word by word
    while (std::getline(iss, buf, WPE_CDELIMITER))
    {
      vec.push_back(buf);
      if (vec.size() >= 4)
      {
        time = vec[0] + ' ' + vec[1] + ' ' + vec[2] + ' ' + vec[3];
        break;
      }
    }
    vec.clear();
  }
  break;
  case coreLog:
  {
    // ignore the comments
    if (line.at(0) != '[')
    {
      // std::cout << "Ignored line - " << line << std::endl;
      return time;
    }
    // read the line, word by word
    std::getline(iss, buf, CORE_CDELIMITER);
    size_t pos = buf.find(" ");
    if (pos != std::string::npos)
    {
      std::string extractedTime = buf.substr(pos, buf.size() - pos);
      time = convertTimestampFormat(extractedTime, "%Y/%m/%d %H:%M:%S", "%Y %b %d %H:%M:%S");
    }
    else
    {
      std::cout << "Not able to find timestamp" << std::endl;
    }
  }
  break;
  }
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

std::string LogfileParser::getStartTimestamp(std::string file, logFormat fmt)
{
  std::ifstream input(file);
  std::string firstLine;
  std::string time = "";

  while (std::getline(input, firstLine))
  {
    time = getTimestamp(firstLine, fmt);
    if (time != "")
    {
      return time;
    }
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
    while (std::getline(iss, buf, WPE_CDELIMITER))
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