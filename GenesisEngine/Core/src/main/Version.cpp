#include <GenesisCore/Version.hpp>
#include <GenesisCore/List.hpp>

namespace ge {
	namespace core {
		Version::Version(const String& str) {
			build = 0;
			if(str.contains('+')) {
				std::cout << str.substring(str.find('+') + 1) << std::endl;
				build = str.substring(str.find('+') + 1).toUint32();
			}

			List<uint32> list;
			str.substring(0, str.find('+')).splitNum(list, ',');
			
			switch(list.size()) {
				case 3: patch = list[2];
				case 2: minor = list[1];
				case 1: major = list[0];
			}
		}

		String Version::format(bool build) const {
			std::stringstream ss;
			ss << major << "." << minor << "." << patch;
			if(build) ss << "+" << this->build;
			return ss.str();
		}

		bool Version::operator>(const Version& v) const {
			if(major == v.major) {
				if(minor == v.minor) {
					if(patch == v.patch) {
						return build > v.build;
					} else {
						return patch > v.patch;
					}
				} else {
					return minor > v.minor;
				}
			} else {
				return major > v.major;
			}
		}
		bool Version::operator<(const Version& v) const {
			if(major == v.major) {
				if(minor == v.minor) {
					if(patch == v.patch) {
						return build < v.build;
					} else {
						return patch < v.patch;
					}
				} else {
					return minor < v.minor;
				}
			} else {
				return major < v.major;
			}
		}
		bool Version::operator>=(const Version& v) const {
			return operator==(v) || operator>(v);
		}
		bool Version::operator<=(const Version& v) const {
			return operator==(v) || operator<(v);
		}
		bool Version::operator==(const Version& v) const {
			return major == v.major && minor == v.minor && patch == v.patch && build == v.build;
		}
		bool Version::operator!=(const Version& v) const {
			return major != v.major || minor != v.minor || patch != v.patch || build != v.build;
		}

		bool Version::isCompatible(const Version& v) {
			return major == v.major && minor == v.minor;
		}
	}
}
