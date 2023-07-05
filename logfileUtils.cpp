#include "logfileUtils.h"

const char CDELIMITER = ' ';

std::string adjustTimestampInMinutes(std::string current, std::string format, int offset)
{
  std::tm timestamp{};
  std::istringstream iss(current);
  std::string buf;

  std::vector<std::string> dateVec;

  std::cout << "current timestamp: " << current << std::endl;

  iss >> std::get_time(&timestamp, "%Y %b %d %H:%M:%S");
  if (iss.fail())
  {
    throw std::runtime_error{"failed to parse time string"};
  }
  std::cout << "Number of hours   = " << timestamp.tm_hour << '\n';
  std::cout << "Number of minutes = " << timestamp.tm_min << '\n';
  std::cout << "Number of seconds = " << timestamp.tm_sec << '\n';

  timestamp.tm_min = timestamp.tm_min + (offset);
  timestamp.tm_sec = 0;

  std::stringstream dateStream;
  dateStream << std::put_time(&timestamp, "%Y %b %d %H:%M:%S");
  return dateStream.str();
}

int compareTimestamp(std::string refernceTime, std::string currentTime)
{
  std::tm time1{}, time2{};
  std::istringstream iss1(refernceTime);
  std::istringstream iss2(currentTime);

  std::vector<std::string> dateVec;

  iss1 >> std::get_time(&time1, "%Y %b %d %H:%M:%S");
  if (iss1.fail())
  {
    throw std::runtime_error{"failed to parse time string"};
  }

  iss2 >> std::get_time(&time2, "%Y %b %d %H:%M:%S");
  if (iss2.fail())
  {
    throw std::runtime_error{"failed to parse time string"};
  }

  // std::cout << "time1 : " << std::put_time(&time1, "%Y %b %d %H:%M:%S") << "time2: " << std::put_time(&time2, "%Y %b %d %H:%M:%S") << std::endl;
  double seconds = difftime(mktime(&time1), mktime(&time2));
  // std::cout << "time difference is : " << seconds << std::endl;
  return seconds;
}