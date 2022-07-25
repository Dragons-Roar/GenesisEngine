#include <GenesisCore/Formatter.hpp>

namespace ge {
	namespace core {
		const NumberSuffix NumberSuffix::K(1000, 'k');
		const NumberSuffix NumberSuffix::M(1000000, 'M');
		const NumberSuffix NumberSuffix::G(1000000000, 'G');
		const NumberSuffix NumberSuffix::T(1000000000000, 'T');

		const std::array<const NumberSuffix*, 4> NumberSuffix::suffixes = {
			&NumberSuffix::K,
			&NumberSuffix::M,
			&NumberSuffix::G,
			&NumberSuffix::T
		};

		Formatter::Formatter(uint8 decimalPlaces, uint8 forcedDecimalPlaces, 
			bool forceDecimalPlacesInts, bool splitThousands, bool bigNumbers):
				decimalPlaces(decimalPlaces), forcedDecimalPlaces(forcedDecimalPlaces),
				forceDecimalPlacesInts(forceDecimalPlacesInts), splitThousands(splitThousands),
				bigNumbers(bigNumbers) {
		}

		String Formatter::formatUint32(uint32 i) {
			std::ostringstream out;

			if(bigNumbers) {
				String s = std::to_string(i);
				uint32 places = s.length();

				for(const NumberSuffix* suff : NumberSuffix::suffixes) {

				}
			}
			return String();
		}
	}
}
