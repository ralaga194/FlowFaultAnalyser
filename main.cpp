#include <iostream>
#include "logfileParser.h"
#include "logfileUtils.h"
#include "logfileConfig.h"

#define WPE_CRASH_MARKER "event=\'PLUGIN_CRASHED\'"

int main(int argc, char *argv[])
{
  std::string configfile = "";
  // std::cout << "Welcome to POC program..." << std::endl;

  // read configuration
  // std::cout << "arguments : " << argc << " value : " << argv[argc - 1] << std::endl;
  if (argc > 1)
  {
    configfile = argv[argc - 1];
  }
  else
  {
    std::cout << "configuring with default configuration from setting.cfg" << std::endl;
    configfile = "./../settings.cfg";
  }
  std::cout << "config file : " << configfile << std::endl;
  LogfileConfig config(configfile);

  std::cout << config.getRootDir() << std::endl;
  std::vector<std::string> lookupfiles = config.getLookupFiles("Lookup_Files");
  // Printing all the elements
  for (auto filename : lookupfiles)
  {
    std::cout << filename << std::endl;
    std::vector<std::string> files = getListFiles(config.getRootDir(), filename);
    for (auto file : files)
    {
      std::cout << "list of lookup files : " << file << std::endl;
    }
  }

#if 0
  LogfileParser parser("./../sample.log", "./../analysis.log");
  std::string timestamp = parser.getMarkerTimestamp(WPE_CRASH_MARKER);
  if (false && timestamp != "")
  {
    std::string startTimestamp = adjustTimestampInMinutes(timestamp, "", -1);
    std::cout << " back track time : " << startTimestamp << std::endl;
    parser.writeLogMessageForAnalysis(startTimestamp, timestamp);
  }
  else
  {
    std::cout << "Marker is not found!!!" << std::endl;
  }
#endif
}