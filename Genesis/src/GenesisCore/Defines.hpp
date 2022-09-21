#pragma once
#include "GenesisCore/Config.hpp"
#include "GenesisCore/GenesisConfig.hpp"
#include "GenesisCore/debug/Instrumentation.hpp"

/*
 * This file includes the core defines
 * This file is not meant to be used in applications!
 * For applications, include<GenesisCore / Genesis.hpp>
 */

/* ---> C++ Standard <--- */
#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <cstdint>
#include <format>
#include <functional>
#include <iomanip>
#include <iosfwd>
#include <iterator>
#include <memory>
#include <mutex>
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

/* Required by Boost/Stacktrace */
#include <boost/stacktrace/stacktrace_fwd.hpp>

/* ---> GLM <--- */
#include <glm/vec3.hpp>
#include <glm/packing.hpp>

/// @brief A 8 Bit sized unsigned integer
typedef uint8_t uint8;
/// @brief A 16 Bit sized unsigned integer
typedef uint16_t uint16;
/// @brief A 32 Bit sized unsigned integer
typedef uint32_t uint32;
/// @brief A 64 Bit sized unsigned integer
typedef uint64_t uint64;
/// @brief A 8 Bit sized integer
typedef int8_t int8;
/// @brief A 16 Bit sized integer
typedef int16_t int16;
/// @brief A 32 Bit sized integer
typedef int32_t int32;
/// @brief A 64 Bit sized integer
typedef int64_t int64;
/// @brief A 32 Bit sized floating point number
typedef float float32;
/// @brief A 64 Bit sized floating point number
typedef double float64;
/// @brief A standard std::string
typedef std::string String;
/// @brief A Genesis KeyCode
typedef uint16 KeyCode;

/// @brief Used for storing voxel/block ids
typedef uint16 Voxel;
/// @brief Used for storing meta data of voxels/blocks
typedef uint16 Meta;

constexpr float32 GE_VOXEL_SIZE = 1.f;

/// @brief The render distance in chunks around the player
constexpr uint8 GE_RENDER_DISTANCE = 4;

/// @brief A position of a voxel relative to the origin of the current chunk
typedef glm::vec<3, uint8> VoxelChunkPos;
/// @brief A position of a voxel relative to the world origin
typedef glm::vec<3, int32> VoxelWorldPos;
/// @brief The position of a chunk in a world
class ChunkPos {
public:
	int16 x, y;

	ChunkPos(): x(0), y(0) { }
	ChunkPos(int16 x, int16 y): x(x), y(y) { }

	bool operator==(const ChunkPos& b) const {
		return b.x == x && b.y == y;
	}
	bool operator!=(const ChunkPos& b) const {
		return b.x != x || b.y != y;
	}

	operator glm::vec2() const {
		return glm::vec2(x, y);
	}
	operator glm::vec3() const {
		return glm::vec3(x, 1.f, y);
	}
};

/// @brief The size of a chunk axis (x = y = z)
constexpr uint32 GE_CHUNK_SIZE = 32;
/// @brief The size of a chunk axis (x = y = z) in a float
constexpr float32 GE_CHUNK_SIZE_F = 32.f;
/// @brief The count of voxels contained in a chunk
constexpr uint32 GE_CHUNK_VOLUME = GE_CHUNK_SIZE * GE_CHUNK_SIZE * GE_CHUNK_SIZE;
/// @brief The height of the world / a chunk column, mesaured in chunks
constexpr uint32 GE_WORLD_HEIGHT = 20;
/// @brief The height of the world / a chunk column, measured in blocks
constexpr uint32 GE_WORLD_HEIGHT_BLOCKS = GE_WORLD_HEIGHT * GE_CHUNK_SIZE;
/// @brief The max width and depth of a world in chunks
constexpr uint32 GE_MAX_WORLD_SIZE = 9999;

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
#define GE_Clamp(value, min, max) (value > max) ? max : (value < min) ? min \
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

namespace boost {
	namespace stacktrace {
		template <class CharT, class TraitsT, class Allocator>
		std::basic_ostream<CharT, TraitsT>& do_stream_st(std::basic_ostream<CharT, TraitsT>& os, const basic_stacktrace<Allocator>& bt) {
			const std::streamsize w = os.width();
			const std::size_t frames = bt.size();
			for(std::size_t i = 0; i < frames; ++i) {
				String name = bt[i].name();
				// Internal STD functions should not be printed
				if(name.find("std::") == 0) {
					continue;
				}
				// If the main function is reached in the call stack, the stack for this app is over
				if(name.find("main") != std::string::npos) {
					break;
				}

				os << "\tat ";
				os << name;
				os << '\n';
			}

			return os;
		}

		template <class CharT, class TraitsT, class Allocator>
		std::basic_ostream<CharT, TraitsT>& do_stream_st(std::basic_ostream<CharT, TraitsT>& os, const basic_stacktrace<Allocator>& bt);

		template <class CharT, class TraitsT>
		std::basic_ostream<CharT, TraitsT>& operator<<(std::basic_ostream<CharT, TraitsT>& os, const stacktrace& bt) {
			return do_stream_st(os, bt);
		}
	}
}

GE_MakeHashable(ChunkPos, t.x, t.y);
