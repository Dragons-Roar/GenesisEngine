#pragma once
#include "./Defines.hpp"
#include "./GenesisBase.hpp"

#define GE_NumberSuffix_SuffixCount 4

namespace ge {
	namespace core {
		class Formatter: public GClass {
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

			const String toString() const override {
				std::stringstream ss;
				ss << "ge::core::Formatter{decimalPlaces:" << decimalPlaces << ",forceDecimalPlaces" << forceDecimalPlaces << ",splitThousands:" << splitThousands << "}";
				return ss.str();
			}

		private:
			uint8 decimalPlaces;
			bool forceDecimalPlaces;
			bool splitThousands;
		};
	}
}
