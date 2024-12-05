#include "Utility.hpp"

#ifdef _WIN32
#include <windows.h>

std::string get_bundle_dir_path() {
  char path[MAX_PATH];
  HMODULE hModule = GetModuleHandle(NULL);
  GetModuleFileName(hModule, path, MAX_PATH);
  return std::filesystem::path(path).remove_filename().string();
}

#elif __linux__
#include <unistd.h>
#include <limits.h>

std::string get_bundle_dir_path() {
  char result[PATH_MAX];
  ssize_t count = readlink("/proc/self/exe", result, PATH_MAX);
  return std::filesystem::path(std::string(result, (count > 0) ? count : 0)).remove_filename().string();
}

#elif __APPLE__
#include <mach-o/dyld.h>
#include <limits.h>

std::string get_bundle_dir_path() {
  char path[PATH_MAX];
  uint32_t size = sizeof(path);
  _NSGetExecutablePath(path, &size);
  return std::filesystem::path(path).remove_filename().string();
}

#else
#error "Unsupported platform"
#endif

std::string getResourcesDirPath() {
  return get_bundle_dir_path() + "resources/";
}

std::string get_save_dir_path() {
  return get_bundle_dir_path() + "save/";
}