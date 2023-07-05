#ifndef LOGFILE_UTILS_H
#define LOGFILE_UTILS_H
#include <iomanip>
#include <iostream>
#include <sstream>
#include <vector>

std::string adjustTimestampInMinutes(std::string current, std::string format, int offset);
int compareTimestamp(std::string refernceTime, std::string currentTime);
#endif /*LOGFILE_UTILS_H*/