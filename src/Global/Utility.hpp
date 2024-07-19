#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <filesystem>
#include <iostream>

std::string getResourcesDirPath();
std::string const RESOURCE_PATH = getResourcesDirPath();

#endif