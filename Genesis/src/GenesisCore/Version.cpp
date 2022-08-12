#include "GenesisCore/Version.hpp"
#include "GenesisCore/Datatypes.hpp"
#include "GenesisCore/List.hpp"
#include "GenesisCore/Utils.hpp"

namespace ge {
	namespace core {
		Version::Version(const String& str) {
			build = 0;
			if(str.contains('+')) {
				build = UInt32::parse(str.substr(str.find('+') + 1));
			}

			List<String> list;
			Utils::splitString(list, str.substr(0, str.find('+')), '.');
			
			switch(list.size()) {
				case 3: patch = UInt32::parse(list[2]);
				case 2: minor = UInt32::parse(list[1]);
				case 1: major = UInt32::parse(list[0]);
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

		const String Version::toString() const {
			std::stringstream ss;
			ss << "Version{major:" << major << ",minor:" << minor << ",patch:" << patch << ",build:" << build << "}";
			return ss.str();
		}
	}
}
