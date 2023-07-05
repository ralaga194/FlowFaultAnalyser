#ifndef LOGFILE_PARSER_H
#define LOGFILE_PARSER_H

#include <iostream>
#include <string>
#include <fstream>

const int MAX_LINE = 500;
const char CDELIMITER = ' ';

class LogfileParser
{
  std::string input_file;

public:
  LogfileParser(std::string file);
  int open();
  bool parse();
  bool close();
  std::string findMarker(char *line);
};

#endif /*LOGFILE_PARSER_H*/