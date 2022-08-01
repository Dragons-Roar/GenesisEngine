#pragma once
#include <cstdint>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <functional>
#include <algorithm>
#include <iomanip>
#include <iterator>
#include <string_view>
#include <format>
#include <utility>
#include <array>
#include <vector>
#include <stdlib.h>
#include <random>
#include <type_traits>

/* ---> Streams <--- */
#include <istream>
#include <ostream>
#include <fstream>
#include <sstream>
#include <iostream>

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

// Combines certain values to hashes together
inline void hash_combine(std::size_t& seed) { }
template <typename T, typename... Rest>
inline void hash_combine(std::size_t& seed, const T& v, Rest... rest) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    hash_combine(seed, rest...);
}

// Makes a class hashable (fields have to start with t.)
#define GE_MakeHashable(type, ...) \
    namespace std {\
        template<> struct hash<type> {\
            std::size_t operator()(const type &t) const {\
                std::size_t ret = 0;\
                hash_combine(ret, __VA_ARGS__);\
                return ret;\
            }\
        };\
    }

#define GE_BIT(x) 1 << x;
