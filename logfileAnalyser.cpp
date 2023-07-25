#include "logfileAnalyser.h"
#include "logfileParser.h"
#include "logfileUtils.h"
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <cstring>
#include <filesystem>

void printFileContents(const std::filesystem::path &filePath)
{
  std::ifstream inputFile(filePath);
  if (inputFile.is_open())
  {
    std::cout << "\n****************" << std::endl;
    std::cout << "\nFIRMWARE VERSION\n"
              << std::endl;
    std::cout << "****************\n"
              << std::endl;
    std::string line;
    while (std::getline(inputFile, line))
    {
      std::cout << line << '\n';
    }
    std::cout << "********************************" << '\n';
    inputFile.close();
  }
  else
  {
    std::cout << "Unable to open the file: " << filePath << std::endl;
  }
}

void getFileStartTimestamp(std::string coreFile)
{
}

// void corelogAnlayse(const std::filesystem::path &filePath, std::string startTimestamp, std::string endTimestamp)
// {
//   std::ifstream coreLogFile(filePath);
//   std::string line;
//   std::string time = "";
//   std::string buf;
//   int found = 0;
//   LogfileParser parser;

//   while (std::getline(coreLogFile, line))
//   {
//     // convert the line in to stream:
//     std::istringstream iss(line);
//     time = parser.getTimestamp(line, logFormat::coreLog);
//     std::cout << "coreLogAnalyse()-> " << time << std::endl;
//     if (time != "")
//     {
//       std::cout << "coreLogAnalyse()-> " << startTimestamp << std::endl;
//       if (compareTimestamp(startTimestamp, time) <= 0)
//       {
//         std::cout << "Priya_main" << std::endl;
//         if (compareTimestamp(endTimestamp, time) > 0)
//         {
//           std::cout << "Priya_main" << std::endl;
//           if (found == 1)
//           {
//             std::cout << line << std::endl;
//           }
//           else
//           {
//             // while (std::getline(iss, buf, CDELIMITER))
//             // {
//             //   if (buf.compare("Clock Frequency Info") == 0)
//             //   {
//             //     found++;
//             //     // std::cout << "*****found crash marker*****" << std::endl;
//             //     std::cout << line << std::endl;
//             //   }
//             // }
//           }
//         }
//       }
//       else
//       {
//         std::cout << "Reached end of the log messages....." << std::endl;
//         break;
//       }
//     }
//   }
// }

void corelogAnlayse(std::string coreFile, std::string startTimestamp, std::string endTimestamp)
{
  std::ifstream coreLogFile(coreFile);
  std::string line;
  std::string time = "";
  std::string buf;
  int found = 0;
  LogfileParser parser;
  bool isDisplayContinue = false;

  while (std::getline(coreLogFile, line))
  {
    // ignore empty line
    if (line.size() == 0)
    {
      std::cout << "Ignored empty line " << std::endl;
      continue;
    }
    // convert the line in to stream:
    std::istringstream iss(line);
    time = parser.getTimestamp(line, logFormat::coreLog);
    // std::cout << "coreLogAnalyse()-> " << time << std::endl;
    if (time != "")
    {
      // std::cout << "coreLogAnalyse()-> " << startTimestamp << std::endl;
      if (compareTimestamp(startTimestamp, time) <= 0)
      {
        if (compareTimestamp(endTimestamp, time) > 0)
        {
          std::cout << line << std::endl;
          isDisplayContinue = true;
        }
      }
      else
      {
        std::cout << "Reached end of the log messages....." << std::endl;
        isDisplayContinue = false;
        break;
      }
    }
    else
    {
      if (isDisplayContinue)
      {
        std::size_t found = line.find("time of dump");
        if (found != std::string::npos)
        {
          std::cout << "Reached end of the log messages....." << std::endl;
          isDisplayContinue = false;
          break;
        }
        std::cout << line << std::endl;
      }
    }
  }
}



int toplogAnlayse(const std::filesystem::path &filePath, std::string startTimestamp, std::string endTimestamp)
{
    LogfileParser parser;
    std::time_t targetTime = convertToTimeT(startTimestamp);

    std::ifstream file(filePath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << std::endl;
        return 0;
    }

    std::string line;
    std::string nearestTimestamp="";
    std::time_t minTimeDifference = std::numeric_limits<std::time_t>::max();
    int occurance = 0;
    while (std::getline(file, line)) {
        std::time_t timestampTime = convertToTimeT(line);
        std::time_t timeDifference = std::abs(timestampTime - targetTime);
        if (timeDifference < minTimeDifference) {
            minTimeDifference = timeDifference;
            nearestTimestamp = parser.getTimestamp(line, logFormat::wpeLog);
        }
        if (nearestTimestamp != "" ) {
            if (line.find("Clock Frequency Info:") != std::string::npos) {
              if (occurance == 0)
              std::cout << line << std::endl;
              occurance++;
            }
            if (occurance == 1)
              std::cout << line << std::endl;
          }
        } 

    file.close();
    return 1;
}

void logfileAnalyse(std::string analyseFile)
{
  std::ifstream analysisFile(analyseFile);
  std::cout << "\n****************" << std::endl;
  std::cout << "\nLOG ANALYSER\n"
            << std::endl;
  std::cout << "****************\n"
            << std::endl;
  std::string line;
  std::string buf;

  while (std::getline(analysisFile, line))
  {
    // convert the line in to stream:
    std::istringstream iss(line);

    // read the line, word by word
    while (std::getline(iss, buf, WPE_CDELIMITER))
    {
      if (buf.compare("HTML5") == 0)
      {
        std::cout << "*****Playback*****" << std::endl;
        std::cout << line << std::endl;
      }
      if (buf.compare("virtualKeyCode") == 0)
      {
        std::cout << "*****Key Presses*****" << std::endl;
        std::cout << line << std::endl;
      }
      if (buf.compare("virtualKeyCode") == 0)
      {
        std::cout << "*****Key Presses*****" << std::endl;
        std::cout << line << std::endl;
      }
      if (buf.compare("ERROR") == 0)
      {
        std::cout << "*****Error Message*****" << std::endl;
        std::cout << line << std::endl;
      }
      if (buf.compare("WARN") == 0)
      {
        std::cout << "*****Warnings*****" << std::endl;
        std::cout << line << std::endl;
      }
      if (buf.compare("Failure") == 0)
      {
        std::cout << "*****Failures*****" << std::endl;
        std::cout << line << std::endl;
      }
      if (buf.compare("Got memory pressure notification") == 0)
      {
        std::cout << "*****Error Message*****" << std::endl;
        std::cout << line << std::endl;
      }
      if (buf.compare("WebProcess is unresponsive") == 0)
      {
        std::cout << "*****Warnings*****" << std::endl;
        std::cout << line << std::endl;
      }
      if (buf.compare("Failure") == 0)
      {
        std::cout << "*****Failures*****" << std::endl;
        std::cout << line << std::endl;
      }
      if (buf.compare("reason: 'MemoryExceeded'") == 0)
      {
        std::cout << "*****Mmeory Usage Warning*****" << std::endl;
        std::cout << line << std::endl;
      }
    }
  }
}
