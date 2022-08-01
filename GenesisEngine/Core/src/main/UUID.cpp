#include <GenesisCore/UUID.hpp>

namespace ge {
	namespace core {
		const UUID UUID::nil = UUID(0, 0);

		static std::random_device randomDevice;
		static std::mt19937_64 engine(randomDevice());
		static std::uniform_int_distribution<uint64_t> randomDist;

		UUID::UUID(): UUID(randomDist(engine), randomDist(engine)) {
		}
		UUID::UUID(uint64 a, uint64 b) {
			handle[0] = a; handle[1] = b;
			#ifndef GE_DIST
			uuidString = format();
			#endif
		}

		UUID::~UUID() {
		}

		UUID UUID::fromString(String str) {
			UUID uuid;

			str.erase(std::remove(str.begin(), str.end(), '-'), str.end());

			uuid.handle[0] = std::stoull(str.substr(0, 16), nullptr, 16);
			uuid.handle[1] = std::stoull(str.substr(16), nullptr, 16);

			#ifndef GE_DIST
			uuid.uuidString = uuid.format();
			#endif

			return uuid;
		}
		String UUID::formatTrimmed() const {
			std::stringstream ss;
			ss << std::setfill('0') << std::setw(16) << std::hex << handle[0] << std::setfill('0') << std::setw(16) << std::hex << handle[1];
			return ss.str();
		}
		String UUID::format() const {
			std::stringstream ss;
			ss << std::setfill('0') << std::setw(16) << std::hex << handle[0] << std::setfill('0') << std::setw(16) << std::hex << handle[1];
			String str = ss.str();
			str.insert(8, 1, '-');
			str.insert(13, 1, '-');
			str.insert(18, 1, '-');
			str.insert(23, 1, '-');
			return str;
		}

		const String UUID::toString() const {
			std::stringstream ss;
			ss << "UUID{" << handle[0] << ", " << handle[1] << "}";
			return ss.str();
		}

		bool UUID::operator==(const UUID& a) const {
			for(uint8 i = 0; i < handle.size(); ++i) {
				if(handle[i] != a.handle[i]) return false;
			}
			return true;
		}
		bool UUID::operator!=(const UUID& a) const {
			uint8 unequal = 0;
			for(uint8 i = 0; i < handle.size(); ++i) {
				if(handle[i] != a.handle[i]) return true;
			}
			return false;
		}
		bool UUID::operator>=(const UUID& a) const {
			return handle[0] + handle[1] >= a.handle[0] + a.handle[1];
		}
		bool UUID::operator<=(const UUID& a) const {
			return handle[0] + handle[1] <= a.handle[0] + a.handle[1];
		}
		bool UUID::operator>(const UUID& a) const {
			return handle[0] + handle[1] > a.handle[0] + a.handle[1];
		}
		bool UUID::operator<(const UUID& a) const {
			return handle[0] + handle[1] < a.handle[0] + a.handle[1];
		}

		std::ostream& operator<<(std::ostream& out, const UUID& u) {
			return out << u.format();
		}
		std::istream& operator>>(std::istream& in, UUID& u) {
			String s;
			in >> s;
			u = UUID::fromString(s);
			return in;
		}
	}
}
