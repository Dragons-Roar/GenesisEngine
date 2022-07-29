#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <functional>
#include <istream>
#include <ostream>
#include <sstream>
#include <fstream>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <iterator>
#include <string_view>
#include <format>
#include <utility>
#include <array>

#define TOML_HEADER_ONLY 0
#include <toml++/toml.h>

/// A 8 Bit sized unsigned integer
typedef uint8_t uint8;
/// A 16 Bit sized unsigned integer
typedef uint16_t uint16;
/// A 32 Bit sized unsigned integer
typedef uint32_t uint32;
/// A 64 Bit sized unsigned integer
typedef uint64_t uint64;
/// A 8 Bit sized integer
typedef int8_t int8;
/// A 16 Bit sized integer
typedef int16_t int16;
/// A 32 Bit sized integer
typedef int32_t int32;
/// A 64 Bit sized integer
typedef int64_t int64;
/// A 32 Bit sized floating point number
typedef float float32;
/// A 64 Bit sized floating point number
typedef double float64;
/// A standard std::string
typedef std::string String;
