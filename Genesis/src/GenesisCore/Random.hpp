#pragma once
#include "GenesisCore/Defines.hpp"
#include "GenesisCore/GenesisBase.hpp"

namespace ge {
	namespace core {
		class Random: public GClass {
		public:
			Random(uint32 seed);

			/// <summary>
			/// Gets a pseudo random number
			/// </summary>
			/// <typeparam name="T">The datatype of the number</typeparam>
			/// <param name="max">The max value (inclusive)</param>
			/// <returns>A nubmer between 0 (inclusive) and the max value (inclusive)</returns>
			template <typename T>
			T get(T max) {
				static_assert(!std::is_same<float32, T>(), "Type can't be a float32!");
				static_assert(!std::is_same<float64, T>(), "Type can't be a float64!");
				return rand() % (max + 1);
			}
			/// <summary>
			/// Gets a pseudo random number
			/// </summary>
			/// <typeparam name="T">The datatype of the number</typeparam>
			/// <param name="min">The min value (inclusive)</param>
			/// <param name="max">The max value (inclusive)</param>
			/// <returns>The random number between the two values</returns>
			template <typename T>
			T get(T min, T max) {
				static_assert(!std::is_same<float32, T>(), "Type can't be a float32!");
				static_assert(!std::is_same<float64, T>(), "Type can't be a float64!");
				return rand() % (max - min + 1) + min;
			}

			/// <summary>
			/// Returns true if a specifc percentage has been hit
			/// </summary>
			/// <param name="perc">The percentage (between 0 and 1)</param>
			/// <returns>True: hit</returns>
			bool perc(float32 perc);

			/// <summary>
			/// Returns a random float64 between 0 and 1
			/// </summary>
			/// <returns>The number</returns>
			float64 random();

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::Random{seed:" << seed << "}";
				return ss.str();
			}

		private:
			uint32 seed;

			std::random_device rd;
			std::default_random_engine dre;
			std::uniform_real_distribution<float64> floatDist;
		};
	}
}
