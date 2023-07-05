#ifndef LOGFILE_PARSER_H
#define LOGFILE_PARSER_H

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

const int MAX_LINE = 500;
const char CDELIMITER = ' ';

class LogfileParser
{
  std::string input_file;
  std::string analysis_file;

public:
  LogfileParser(std::string infile, std::string afile);
  int open();
  bool parse();
  bool close();
  std::string findMarker(char *line);
  std::string getMarkerTimestamp(std::string marker);
  bool seek(std::string timestamp);
  std::vector<std::string> getTokens(std::string start, std::string end);
  bool writeLogMessageForAnalysis(std::string start, std::string end);
  std::string getTimestamp(std::string line);
};

#endif /*LOGFILE_PARSER_H*/