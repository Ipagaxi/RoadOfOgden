#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <string>
#include <filesystem>
#include <iostream>

std::string getResourcePath();
std::string const RESOURCES = getResourcePath();

#endif