#include <iostream>
#include "logfileParser.h"
#include "logfileUtils.h"

#define WPE_CRASH_MARKER "event=\'PLUGIN_CRASHED\'"

int main()
{
  std::cout << "Welcome to POC program..." << std::endl;
  LogfileParser parser("./sample.log", "./analysis.log");
  std::string timestamp = parser.getMarkerTimestamp(WPE_CRASH_MARKER);
  if (timestamp != "")
  {
    std::string startTimestamp = adjustTimestampInMinutes(timestamp, "", -1);
    parser.writeLogMessageForAnalysis(startTimestamp, timestamp);
  }
  else
  {
    std::cout << "Marker is not found!!!" << std::endl;
  }
}