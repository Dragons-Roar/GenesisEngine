#pragma once
#include "GenesisCore/GenesisConfig.hpp"
#include "GenesisCore/debug/Instrumentation.hpp"

// This file includes the core defines
// This file is not meant to be used in applications!
// For applications, include <GenesisCore/Genesis.hpp>

// C++ Standard
#include <algorithm>
#include <array>
#include <chrono>
#include <cstdint>
#include <format>
#include <functional>
#include <iomanip>
#include <iterator>
#include <memory>
#include <random>
#include <stdlib.h>
#include <string>
#include <string_view>
#include <thread>
#include <tuple>
#include <type_traits>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

/* ---> Streams <--- */
#include <fstream>
#include <iostream>
#include <istream>
#include <ostream>
#include <sstream>

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
/// A Genesis KeyCode
typedef uint16 KeyCode;

/* ---> Utility Macros <--- */
#define GE_BIT(x) (1 << x)

// Combines certain values to hashes together
inline void hash_combine(std::size_t& seed) {}
template <typename T, typename... Rest>
inline void hash_combine(std::size_t& seed, const T& v, Rest... rest) {
	std::hash<T> hasher;
	seed ^= hasher(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	hash_combine(seed, rest...);
}

// Makes a class hashable (fields have to start with t.)
#define GE_MakeHashable(type, ...)                        \
	namespace std {                                       \
		template <>                                       \
		struct hash<type> {                               \
			std::size_t operator()(const type& t) const { \
				std::size_t ret = 0;                      \
				hash_combine(ret, __VA_ARGS__);           \
				return ret;                               \
			}                                             \
		};                                                \
	}

// Bind a event function
#define GE_BindEventFunction(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

// Memory
namespace ge {
	namespace core {
		template <typename T>
		using Scope = std::unique_ptr<T>;
		template <typename T, typename... Args>
		constexpr Scope<T> CreateScope(Args&&... args) {
			return std::make_unique<T>(std::forward<Args>(args)...);
		}

		template <typename T>
		using Ref = std::shared_ptr<T>;
		template <typename T, typename... Args>
		constexpr Ref<T> CreateRef(Args&&... args) {
			return std::make_shared<T>(std::forward<Args>(args)...);
		}
	}
}

// Returns the smaller values of the two
// WARNING: Macro based, can produced errors
#define GE_Min(left, right) left > right ? right : left
// Returns the greater values of the two
// WARNING: Macro based, can produced errors
#define GE_Max(left, right) left < right ? right : left
// Returns max if the value is bigger than max, min if the value is less than min, value if the value is between min and max
// WARNING: Macro based, can produced errors
#define GE_Clamp(value, min, max) = (value > max) ? max : (value < min) ? min \
	                                                                    : value

#define GE_MacroCombine(a, b) a##b

#if GE_PROFILE
#	define GE_ProfileBeginSession(name, filepath) ::ge::core::Instrumentor::get().beginSession(name, filepath)
#	define GE_ProfileEndSession() ::ge::core::Instrumentor::get().endSession()
#	define GE_ProfileScope(name) ::ge::core::InstrumentationTimer GE_MacroCombine(timer, __LINE__)(name)
#	define GE_ProfileFunction() GE_ProfileScope(__FUNCSIG__)
#else
#	define GE_ProfileBeginSession(name, filepath)
#	define GE_ProfileEndSession()
#	define GE_ProfileScope(name)
#	define GE_ProfileFunction()
#endif

#define GE_String_ToLower(data) std::transform(data.begin(), data.end(), data.begin(), ::tolower)
#define GE_String_ToUpper(data) std::transform(data.begin(), data.end(), data.begin(), ::toupper)
