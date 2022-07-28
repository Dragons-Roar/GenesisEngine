#pragma once
#include "./Defines.hpp"

#define GE_NumberSuffix_SuffixCount 4

namespace ge {
	namespace core {
		class NumberSuffix {
		public:
			static const NumberSuffix K;
			static const NumberSuffix M;
			static const NumberSuffix G;
			static const NumberSuffix T;

			static inline const NumberSuffix* getSuffix(uint8 id) { return suffixes[id]; }

		private:
			static std::array<const NumberSuffix*, GE_NumberSuffix_SuffixCount> suffixes;

		public:
			NumberSuffix(uint32 multiplier, char suffix): multiplier(multiplier), suffix(suffix) { }

			static void init();

			inline uint32 getMultiplier() const { return multiplier; }
			inline char getSuffix() const { return suffix; }

		private:
			uint32 multiplier;
			char suffix;
		};

		class Formatter {
		public:
			Formatter(uint8 decimalPlaces = 2, bool forceDecimalPlaces = true, bool splitThousands = true);

			template <typename T>
			String format(T i) {
				std::ostringstream out;
				if(splitThousands) {
					out.imbue(std::locale(""));
				}
				if(forceDecimalPlaces) {
					out << std::fixed << std::setprecision(decimalPlaces);
					out << std::setfill('0');
				}
				out << i;
				return out.str();
			}

			static void init();

		private:
			uint8 decimalPlaces;
			bool forceDecimalPlaces;
			bool splitThousands;
		};
	}
}
