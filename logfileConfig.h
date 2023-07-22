#ifndef LOGFILE_CONFIG_H
#define LOGFILE_CONFIG_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <iomanip>
#include <filesystem>

class LogfileConfig
{
  std::string config_file;
  std::map<std::string, std::string> configProps;

public:
  LogfileConfig(std::string incfgfile);
  std::string getRootDir(void);
  std::string getOutputDir(void);
  std::vector<std::string> getLookupFiles(std::string marker);
  std::vector<std::string> getRelatedFiles(std::string marker);
  std::string getInspectFile(void);
  std::string getMarkerString(void);
  int getInspectionDuration(void);
  bool init(void);
};
#endif /*LOGFILE_CONFIG_H*/
