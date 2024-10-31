#include "Utility.hpp"

#ifdef _WIN32
#include <windows.h>

std::string getResourcesDirPath() {
  char path[MAX_PATH];
  HMODULE hModule = GetModuleHandle(NULL);
  GetModuleFileName(hModule, path, MAX_PATH);
  return std::filesystem::path(path).remove_filename().string() + "resources/";
}

#elif __linux__
#include <unistd.h>
#include <limits.h>

std::string getResourcesDirPath() {
  char result[PATH_MAX];
  ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
  return std::filesystem::path(std::string(result, (count > 0) ? count : 0)).remove_filename().string() + "resources/";
}

#elif __APPLE__
#include <mach-o/dyld.h>
#include <limits.h>

std::string getResourcesDirPath() {
  char path[PATH_MAX];
  uint32_t size = sizeof(path);
  _NSGetExecutablePath(path, &size);
  return std::filesystem::path(path).remove_filename().string() + "resources/";
}

#else
#error "Unsupported platform"
#endif