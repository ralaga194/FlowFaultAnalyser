#ifndef LOGFILE_ANALYSER_H
#define LOGFILE_ANALYSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <filesystem>

void logfileAnalyse(std::string analyseFile);
void printFileContents(const std::filesystem::path &filePath);
void corelogAnlayse(std::string coreFile, std::string startTimestamp, std::string endTimestamp);

#endif /*LOGFILE_UTILS_H*/