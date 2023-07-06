#ifndef LOGFILE_CONFIG_H
#define LOGFILE_CONFIG_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <iomanip>

class LogfileConfig
{
  std::string config_file;
  std::map<std::string, std::string> configProps;

public:
  LogfileConfig(std::string incfgfile);
  std::string getRootDir(void);
  std::vector<std::string> getLookupFiles(std::string marker);
};
#endif /*LOGFILE_CONFIG_H*/
