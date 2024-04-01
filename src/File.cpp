#include "CRobes/File.hpp"

std::string crb::File::getContents(const std::string& path)
{
  std::ifstream file(path);
  if (!file.is_open())
  {
    std::cerr << "Failed to open file (" << path << ")!\n";
    return "";
  }

  std::ostringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}
