#pragma once

#include <cstddef>
#include <string>


struct Cursor{
  size_t row = 0;
  size_t col = 0;
};

struct Document{
  std::string contents;
  Cursor cursor;
};


Document load_file(const std::string& path);

size_t get_line_length(const Document& document, size_t row);

size_t get_line_count(const Document & document);
