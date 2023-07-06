#include "logfileConfig.h"

LogfileConfig::LogfileConfig(std::string incfgfile) : config_file(incfgfile)
{
  std::string line;
  std::string buf;
  std::ifstream cfg(config_file);
  while (std::getline(cfg, line))
  {
    // convert the line in to stream:
    std::istringstream iss(line);

    // declare vector of string (instead of fixed array)
    std::vector<std::string> tokens;

    // read the line, word by word
    while (std::getline(iss, buf, '='))
    {
      tokens.push_back(buf);
    }
    std::cout << "tokens: " << tokens[0] << tokens[1] << std::endl;
    configProps.insert(std::pair<std ::string, std ::string>(tokens[0], tokens[1]));
    tokens.clear();
  }
  std::map<std::string, std::string>::iterator it = configProps.begin();
  for (; it != configProps.end(); ++it)
    std::cout << it->first << " => " << it->second << '\n';
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