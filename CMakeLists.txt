cmake_minimum_required(VERSION 3.5)

project(FlowFaultAnalyser LANGUAGES CXX)

add_executable(parser main.cpp logfileParser.cpp logfileUtils.cpp logfileConfig.cpp)