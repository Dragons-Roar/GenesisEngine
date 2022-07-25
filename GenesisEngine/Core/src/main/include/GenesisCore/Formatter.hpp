#pragma once
#include "./Defines.hpp"
#include "./String.hpp"

namespace ge {
	namespace core {
		class NumberSuffix {
		public:
			static const NumberSuffix K;
			static const NumberSuffix M;
			static const NumberSuffix G;
			static const NumberSuffix T;

			static const std::array<const NumberSuffix*, 4> suffixes;
			static const std::array<const NumberSuffix*, 4> suffixesAscending;

		public:
			NumberSuffix(uint32 multiplier, char suffix): multiplier(multiplier), suffix(suffix) { }

			inline uint32 getMultiplier() const { return multiplier; }
			inline char getSuffix() const { return suffix; }

		private:
			uint32 multiplier;
			char suffix;
		};

		class Formatter {
		public:
			Formatter(uint8 decimalPlaces = 2, uint8 forcedDecimalPlaces = 2, bool forceDecimalPlacesInts = true, bool splitThousands = true, bool bigNumbers = false);

			String formatUint32(uint32 i);

		private:
			uint8 decimalPlaces;
			uint8 forcedDecimalPlaces;
			bool forceDecimalPlacesInts;
			bool splitThousands;
			bool bigNumbers;
		};
	}
}
