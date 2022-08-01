#pragma once
#include "./Defines.hpp"
#include "./GClass.hpp"

namespace ge {
	namespace core {
		/// <summary>
		/// A UUID (Universally Unique IDentifier) in a 8-4-4-4-12 format
		/// </summary>
		class UUID: public GClass {
		public:
			UUID();
			UUID(uint64 a, uint64 b);

			static const UUID nil;

			static UUID fromString(String str);
			String formatTrimmed() const;
			String format() const;

			const String toString() const override;

			bool operator==(const UUID& a) const;
			bool operator!=(const UUID& a) const;
			bool operator>=(const UUID& a) const;
			bool operator<=(const UUID& a) const;
			bool operator>(const UUID& a) const;
			bool operator<(const UUID& a) const;

			friend std::ostream& operator<<(std::ostream& out, const UUID& u);
			friend std::istream& operator>>(std::istream& in, UUID& u);

			virtual ~UUID();
			std::array<uint64, 2> handle;
		private:
			#ifndef GE_DIST
			// This string is used to view in a variables tab by your IDE while debugging to clearly see the uuid's value
			String uuidString;
			#endif
		};
	}
}

GE_MakeHashable(ge::core::UUID, t.handle[0], t.handle[1]);
