#pragma once

#include <cstdint>

/// Class for storring initial info about operation or class
struct LocationInfo {
  uint_fast32_t line;
  const char *func_name;
  const char *file_name;
};
