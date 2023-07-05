#include <iostream>
#include "logfileParser.h"
int main()
{
  std::cout << "Welcome to POC program..." << std::endl;
  LogfileParser parser("./06-15-23-07-45AM-wpeframework.log");
  parser.parse();
}