#pragma once
#include "./Defines.hpp"
#include "./GenesisBase.hpp"

namespace ge {
	namespace core {
		/// <summary>
		/// A UUID (Universally Unique IDentifier) in a 8-4-4-4-12 format
		/// </summary>
		class UUID: public GClass {
		public:
			typedef struct {
				uint64 a, b;
			} Handle;

			UUID();
			UUID(Handle handle);
			UUID(uint64 a, uint64 b);

			static const UUID nil;

			static UUID fromString(String str);
			String formatTrimmed() const;
			String format() const;

			Handle getHandle() { return handle; }

			const String toString() const override;

			bool operator==(const UUID& a) const;
			bool operator!=(const UUID& a) const;
			bool operator>=(const UUID& a) const;
			bool operator<=(const UUID& a) const;
			bool operator>(const UUID& a) const;
			bool operator<(const UUID& a) const;

			virtual ~UUID();
			Handle handle;
		private:
			#ifndef GE_DIST
			// This string is used to view in a variables tab by your IDE while debugging to clearly see the uuid's value
			String d_uuidString;
			#endif
		};
	}
}

GE_MakeHashable(ge::core::UUID, t.handle.a, t.handle.b);
