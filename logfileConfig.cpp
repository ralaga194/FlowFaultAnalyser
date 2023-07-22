#include "logfileConfig.h"

LogfileConfig::LogfileConfig(std::string incfgfile) : config_file(incfgfile)
{
  std::string line;
  std::string buf;
  std::ifstream cfg(config_file);
  while (std::getline(cfg, line))
  {
    // ignore empty line
    if (line.size() == 0)
    {
      std::cout << "Ignored empty line " << std::endl;
      continue;
    }
    // ignore the comments
    if (line.at(0) == '#')
    {
      std::cout << "Ignored comments - " << line << std::endl;
      continue;
    }

    // convert the line in to stream:
    std::istringstream iss(line);

    // declare vector of string (instead of fixed array)
    std::vector<std::string> tokens;

    // read the line, word by word
    while (std::getline(iss, buf, ':'))
    {
      tokens.push_back(buf);
    }
    // std::cout << "tokens: " << tokens[0] << tokens[1] << std::endl;
    configProps.insert(std::pair<std ::string, std ::string>(tokens[0], tokens[1]));
    tokens.clear();
  }
  // std::map<std::string, std::string>::iterator it = configProps.begin();
  // for (; it != configProps.end(); ++it)
  //   std::cout << it->first << " => " << it->second << '\n';
  cfg.close();
}

std::string LogfileConfig::getRootDir()
{
  std::string result = "";

  if (configProps.find("Root_Dir") != configProps.end())
  {
    result = configProps["Root_Dir"];
  }
  std::cout << "Root_Dir: " << result << std::endl;
  return result;
}

std::vector<std::string> LogfileConfig::getLookupFiles(std::string marker)
{
  // declare vector of string (instead of fixed array)
  std::vector<std::string> logfiles;
  std::string buf;
  if (configProps.find(marker) != configProps.end())
  {
    std::string tokens = configProps[marker];
    // convert the line in to stream:
    std::istringstream iss(tokens);

    // read the line, word by word
    while (std::getline(iss, buf, ';'))
    {
      logfiles.push_back(buf);
    }
  }
  return logfiles;
}

std::string LogfileConfig::getInspectFile()
{
  std::string result = "";

  if (configProps.find("Inspect_Filename") != configProps.end())
  {
    result = configProps["Inspect_Filename"];
  }
  std::cout << "Inspect_Filename: " << result << std::endl;
  return result;
}

std::string LogfileConfig::getMarkerString()
{
  std::string result = "";

  if (configProps.find("Marker_String") != configProps.end())
  {
    result = configProps["Marker_String"];
  }
  // std::cout << "Marker_String: " << result << std::endl;
  return result;
}

int LogfileConfig::getInspectionDuration()
{
  int duration = 0;

  if (configProps.find("Inspection_Duration") != configProps.end())
  {
    duration = stoi(configProps["Inspection_Duration"]);
  }
  // std::cout << "Inspection_Duration: " << duration << std::endl;
  return duration;
}