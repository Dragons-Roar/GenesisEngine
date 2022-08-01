#include <GenesisCore/UUID.hpp>

namespace ge {
	namespace core {
		const UUID UUID::nil = UUID(0, 0);

		static std::random_device randomDevice;
		static std::mt19937_64 engine(randomDevice());
		static std::uniform_int_distribution<uint64_t> randomDist;

		UUID::UUID(): UUID(randomDist(engine), randomDist(engine)) {
			#ifndef GE_DIST
			d_uuidString = format();
			#endif
		}
		UUID::UUID(Handle handle): handle(handle) {
			#ifndef GE_DIST
			d_uuidString = format();
			#endif
		}
		UUID::UUID(uint64 a, uint64 b): handle{ a, b } {
			#ifndef GE_DIST
			d_uuidString = format();
			#endif
		}

		UUID::~UUID() {
		}

		UUID UUID::fromString(String str) {
			UUID uuid;

			str.erase(std::remove(str.begin(), str.end(), '-'), str.end());

			uuid.handle.a = std::stoull(str.substr(0, 16), nullptr, 16);
			uuid.handle.b = std::stoull(str.substr(16), nullptr, 16);

			#ifndef GE_DIST
			uuid.d_uuidString = uuid.format();
			#endif

			return uuid;
		}
		String UUID::formatTrimmed() const {
			std::stringstream ss;
			ss << std::setfill('0') << std::setw(16) << std::hex << handle.a << std::setfill('0') << std::setw(16) << std::hex << handle.b;
			return ss.str();
		}
		String UUID::format() const {
			std::stringstream ss;
			ss << std::setfill('0') << std::setw(16) << std::hex << handle.a << std::setfill('0') << std::setw(16) << std::hex << handle.b;
			String str = ss.str();
			str.insert(8, 1, '-');
			str.insert(13, 1, '-');
			str.insert(18, 1, '-');
			str.insert(23, 1, '-');
			return str;
		}

		const String UUID::toString() const {
			std::stringstream ss;
			ss << "UUID{" << handle.a << ", " << handle.b << "}";
			return ss.str();
		}

		bool UUID::operator==(const UUID& a) const {
			return (handle.a == a.handle.a && handle.b == a.handle.b);
		}
		bool UUID::operator!=(const UUID& a) const {
			return (handle.a != a.handle.a || handle.b != a.handle.b);
		}
		bool UUID::operator>=(const UUID& a) const {
			return handle.a + handle.b >= a.handle.a + a.handle.b;
		}
		bool UUID::operator<=(const UUID& a) const {
			return handle.a + handle.b <= a.handle.a + a.handle.b;
		}
		bool UUID::operator>(const UUID& a) const {
			return handle.a + handle.b > a.handle.a + a.handle.b;
		}
		bool UUID::operator<(const UUID& a) const {
			return handle.a + handle.b < a.handle.a + a.handle.b;
		}
	}
}
