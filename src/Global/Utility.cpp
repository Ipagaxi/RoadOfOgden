#include "Utility.hpp"

std::string getResourcePath() {
  std::filesystem::path relativeResourcePath = "resources/";
  std::filesystem::path absoluteResourcePath = std::filesystem::absolute(relativeResourcePath);
  return absoluteResourcePath.string();
}