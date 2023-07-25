#ifndef LOGFILE_UTILS_H
#define LOGFILE_UTILS_H
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>
#include <filesystem>

std::string adjustTimestampInMinutes(std::string current, std::string format, int offset);
int compareTimestamp(std::string refernceTime, std::string currentTime);
std::vector<std::string> getListFiles(std::string path, std::string identifier);
std::string getFilename(std::string filenameWithPath);
std::string getFileExtension(std::string filename);
std::string convertTimestampFormat(std::string timestamp, std::string curfmt, std::string newfmt);
#endif /*LOGFILE_UTILS_H*/