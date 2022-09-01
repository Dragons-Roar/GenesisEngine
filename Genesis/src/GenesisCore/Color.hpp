#pragma once
#include "GenesisCore/Defines.hpp"
#include "GenesisCore/Logger.hpp"
#include <glm/glm.hpp>

#define GE_RGBA(r, g, b, a) ((uint8) (255.f * a)) | (((uint8) (255.f * b)) << 8) | (((uint8) (255.f * g)) << 16) | (((uint8) (255.f * r)) << 24)
#define GE_RGB(r, g, b) (255) | (((uint8) (255.f * b)) << 8) | (((uint8) (255.f * g)) << 16) | (((uint8) (255.f * r)) << 24)

namespace ge {
	namespace core {
		class Color {
		public:
			/**
			 * @brief Construct a new Color object
			 *
			 * @param r The red channel (0 - 255)
			 * @param g The green channel (0 - 255)
			 * @param b The blue channel (0 - 255)
			 * @param a The alpha channel (0 - 255)
			 */
			Color(uint8 r, uint8 g, uint8 b, uint8 a = 255): r(r / 255.f), g(g / 255.f), b(b / 255.f), a(a / 255.f) {}
			/**
			 * @brief Construct a new Color object
			 *
			 * @param v The vector (rgb)
			 */
			Color(const glm::vec3& v): Color(v.r, v.g, v.b, 1.f) {}
			/**
			 * @brief Construct a new Color object
			 *
			 * @param v The vector (rgba)
			 */
			Color(const glm::vec4& v): Color(v.r, v.g, v.b, v.a) {}
			/**
			 * @brief Construct a new Color object
			 *
			 * @param rgba The hex color
			 */
			Color(uint32 rgba): Color((uint8) ((rgba & 0xFF000000) >> 24), (uint8) ((rgba & 0x00FF0000) >> 16), (uint8) ((rgba & 0x0000FF00) >> 8), (uint8) rgba & 0x000000FF) {}

			inline float32 getR() const { return r; }
			inline float32 getG() const { return g; }
			inline float32 getB() const { return b; }
			inline float32 getA() const { return a; }

			inline uint32 getRGB() const { return GE_RGB(r, g, b); }
			inline uint32 getRGBA() const { return GE_RGBA(r, g, b, a); }

			inline glm::vec3 getRGBVec() const { return glm::vec3(r, g, b); }
			inline glm::vec4 getRGBAVec() const { return glm::vec4(r, g, b, a); }

			const String format() const {
				std::stringstream ss;
				ss << "#" << std::hex << std::setfill('0') << std::setw(2) << static_cast<uint16>(255.f * r) << static_cast<uint16>(255.f * g) << static_cast<uint16>(255.f * b) << static_cast<uint16>(255.f * a);
				return ss.str();
			}

		private:
			float32 r, g, b, a;
		};
	}
}
