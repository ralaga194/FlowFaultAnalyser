#include <iostream>
#include "logfileParser.h"
#include "logfileUtils.h"
#include "logfileConfig.h"
#include "logfileAnalyser.h"

#define WPE_CRASH_MARKER "event=\'PLUGIN_CRASHED\'"

int main(int argc, char *argv[])
{
  std::string configfile = "";
  bool isRelatedFilesReq = false;

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

  std::vector<std::string> lookupfiles = config.getLookupFiles("Lookup_Files");
  std::string outputDir = config.getOutputDir();
  std::string markerTimestamp = "";
  std::vector<std::string> mTimestamps;

  // Printing all the elements
  for (auto filename : lookupfiles)
  {
    std::cout << filename << std::endl;
    std::vector<std::string> files = getListFiles(config.getRootDir(), filename);
    std::string inspectFilename = config.getInspectFile();

    std::cout << "------------------------------------------------------------" << std::endl;
    for (auto file : files)
    {
      // std::cout << "list of lookup files : " << file << std::endl;

      std::string filename = getFilename(file);
      std::string fext = getFileExtension(filename);
      // std::cout << "filename : " << filename << "extension: " << fext;

      // TODO: input file for the parser needs to be updated based on above findings
      LogfileParser parser(file, outputDir + inspectFilename + fext);
      markerTimestamp = parser.getMarkerTimestamp(config.getMarkerString());
      if (markerTimestamp != "")
      {
        isRelatedFilesReq = true;
        std::string startTimestamp = adjustTimestampInMinutes(markerTimestamp, "", config.getInspectionDuration());
        std::string fileStartTimestamp = parser.getStartTimestamp();

        // std::cout << "startTimestamp : " << startTimestamp << std::endl;
        // std::cout << "fileStartTimestamp : " << fileStartTimestamp << std::endl;
        if (compareTimestamp(fileStartTimestamp, startTimestamp) > 0)
        {
          std::cout << " inspect logmessage start timestamp : " << fileStartTimestamp << std::endl;
          parser.writeLogMessageForAnalysis(fileStartTimestamp, markerTimestamp);
        }
        else
        {
          std::cout << " inspect logmessage start timestamp : " << startTimestamp << std::endl;
          parser.writeLogMessageForAnalysis(startTimestamp, markerTimestamp);
        }
        logfileAnalyse(outputDir + inspectFilename + fext);
        mTimestamps.push_back(markerTimestamp);
      }
      else
      {
        std::cout << "Marker is not found!!!" << std::endl;
      }
    }
  }
  if (isRelatedFilesReq)
  {
    std::vector<std::string> relatedfilesMarker = config.getRelatedFiles("Related_Files");
    std::filesystem::path targetParent = outputDir;
    LogfileParser coreLogParser;
    /*std::string coreLogFile = "../investigate/06-15-23-07-45AM-core_log.txt";*/

    for (auto marker : relatedfilesMarker)
    {
      std::cout << marker << std::endl;
      std::vector<std::string> files = getListFiles(config.getRootDir(), marker);

      for (auto file : files)
      {
        std::string filename = getFilename(file);
        auto target = targetParent / filename;
        // std::cout << "file - " << file << "filename: " << filename << std::endl;
        try
        {
          if (!std::filesystem::exists(target))
          {
            std::filesystem::copy_file(file, target, std::filesystem::copy_options::overwrite_existing);
          }
          else
          {
            std::cout << target << "is already exist in output folder\n"
                      << std::endl;
          }
          if (marker.compare("version") == 0)
            printFileContents(file);
          if (marker.compare("top_log") == 0) {
            std::string startTimestamp = adjustTimestampInMinutes(mTimestamps[0], "", -3);
            std::string fileStartTimestamp = coreLogParser.getStartTimestamp(file, logFormat::wpeLog);
            std::cout << "\n Top_log startTimestamp : " << startTimestamp << "Top_log endTimestamp : " << mTimestamps[0] << std::endl;
            if (compareTimestamp(fileStartTimestamp, startTimestamp) > 0)
            {
              std::cout << " \n inspect logmessage start timestamp : " << fileStartTimestamp << std::endl;
              toplogAnlayse(file, fileStartTimestamp, mTimestamps[0]);
            }
            else
            {
              std::cout << " \n inspect logmessage start timestamp : " << startTimestamp << std::endl;
              toplogAnlayse(file, startTimestamp, mTimestamps[0]);
            }
          }
          if (marker.compare("core_log") == 0)
          {
            std::string startTimestamp = adjustTimestampInMinutes(mTimestamps[0], "", -3);
            std::cout << "startTimestamp : " << startTimestamp << "endTimestamp : " << mTimestamps[0] << std::endl;
            std::string fileStartTimestamp = coreLogParser.getStartTimestamp(file, logFormat::coreLog);

            // std::cout << "startTimestamp : " << startTimestamp << std::endl;
            // std::cout << "fileStartTimestamp : " << fileStartTimestamp << std::endl;
            if (compareTimestamp(fileStartTimestamp, startTimestamp) > 0)
            {
              std::cout << " inspect logmessage start timestamp : " << fileStartTimestamp << std::endl;
              corelogAnlayse(file, fileStartTimestamp, mTimestamps[0]);
            }
            else
            {
              std::cout << " inspect logmessage start timestamp : " << startTimestamp << std::endl;
              corelogAnlayse(file, startTimestamp, mTimestamps[0]);
            }
          }
        }
        catch (std::exception &e)
        {
          std::cout << e.what();
        }
      }
    }
  }
}