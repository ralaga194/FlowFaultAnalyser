#include "logfileUtils.h"
using std::filesystem::directory_iterator;
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

int getMilliseconds(std::string time)
{
  int millisec = 0;
  std::string delimiter = ".";

  size_t pos_start;

  pos_start = time.find(delimiter);
  if (pos_start != std::string::npos)
  {
    millisec = stoi(time.substr(pos_start + 1));
  }
  // std::cout << "millisec: " << millisec << std::endl;
  return millisec;
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
  if (seconds == 0)
  {
    int time1Millisec = getMilliseconds(refernceTime);
    int time2Millisec = getMilliseconds(currentTime);
    return (time1Millisec - time2Millisec);
  }
  return seconds;
}

std::vector<std::string> getListFiles(std::string path, std::string identifier)
{
  std::vector<std::string> fileslist = {};
  for (const auto &file : directory_iterator(path))
  {
    std::string infile(file.path().filename().string());

    if (infile.find(identifier) != std::string::npos)
    {
      // std::cout << "found!" << '\n';
      fileslist.push_back(file.path().string());
    }
  }
  return fileslist;
}

std::string getFilename(std::string filenameWithPath)
{
  std::string filename = "";
  std::string delimiter = "/";

  size_t pos_end;

  pos_end = filenameWithPath.find_last_of(delimiter);
  if (pos_end != std::string::npos)
  {
    filename = filenameWithPath.substr(pos_end + 1);
  }
  std::cout << "filename: " << filename << std::endl;
  return filename;
}

std::string getFileExtension(std::string filename)
{
  std::string fileExtension = "";
  std::string delimiter = ".";

  size_t pos_start;

  pos_start = filename.find(delimiter);
  if (pos_start != std::string::npos)
  {
    fileExtension = filename.substr(pos_start);
  }
  std::cout << "fileExtension: " << fileExtension << std::endl;
  return fileExtension;
}