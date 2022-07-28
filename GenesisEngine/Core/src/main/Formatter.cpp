#include <GenesisCore/Formatter.hpp>

namespace ge {
	namespace core {
		/* ---> NumberSuffix <--- */
		const NumberSuffix NumberSuffix::K(1000, 'k');
		const NumberSuffix NumberSuffix::M(1000000, 'M');
		const NumberSuffix NumberSuffix::G(1000000000, 'G');
		const NumberSuffix NumberSuffix::T(1000000000000, 'T');

		std::array<const NumberSuffix*, GE_NumberSuffix_SuffixCount> NumberSuffix::suffixes = {
			nullptr
		};

		void NumberSuffix::init() {
			suffixes[0] = &NumberSuffix::K;
			suffixes[1] = &NumberSuffix::M;
			suffixes[2] = &NumberSuffix::G;
			suffixes[3] = &NumberSuffix::T;
		}

		/* ---> Formatter <--- */
		Formatter::Formatter(uint8 decimalPlaces, bool forceDecimalPlaces, bool splitThousands):
				decimalPlaces(decimalPlaces), forceDecimalPlaces(forceDecimalPlaces), splitThousands(splitThousands) {
		}

		void Formatter::init() {
			NumberSuffix::init();
		}
	}
}
